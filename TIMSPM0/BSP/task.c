#include "task.h"

////////////////////////////////////////////////////////////////////////////////////

/* task1 */
Gray_TypeDef gray_sensor;	//灰度传感器数据

float last_yaw = 0.0f;
float yaw_sum = 0.0f;
uint8_t laps_count = 0;

extern uint8_t set_laps;

void update_laps_count(float current_yaw)
{
    float delta_yaw = current_yaw - last_yaw;

    // 处理跳变：179 -> -179 实际是 +2 度
    if (delta_yaw > 180.0f) {
        delta_yaw -= 360.0f;
    } else if (delta_yaw < -180.0f) {
        delta_yaw += 360.0f;
    }

    yaw_sum += delta_yaw;
    last_yaw = current_yaw;

    // 计算圈数
    if (fabs(yaw_sum) >= 360.0f) {
        yaw_sum = 0;
        laps_count++;
        // ek_printf(">> Laps: %d\r\n", laps_count);
    }
}

uint8_t is_buzzer_on;
void motor_pid_task(float target_speed)
{
    gray_read(&gray_sensor);
    float track_error = calculate_tracking_error(&gray_sensor);

    update_laps_count(Yaw);

    // 计算速度PI输出
    int speed_output = speed_pid_task(target_speed, encoder1_cnt, encoder2_cnt);

    // 计算转向PD输出，目标循迹误差为0
    int turn_output = turn_pid_task(track_error);

    int pwm_left  = speed_output - turn_output;
    int pwm_right = speed_output + turn_output;

    // 限幅
    if (pwm_left  >  100) pwm_left  =  100;
    if (pwm_left  < -100) pwm_left  = -100;
    if (pwm_right >  100) pwm_right =  100;
    if (pwm_right < -100) pwm_right = -100;

    // 控制电机停止或运行
    if (laps_count == set_laps) { // 到达设定圈数
        if (!is_buzzer_on) {
            is_buzzer_on = 1;
            buzzer_on(300);
        }
        Set_Motor_PWM(0, 0);
    }
    else {
        Set_Motor_PWM(pwm_left, pwm_right);
    }
}

////////////////////////////////////////////////////////////////////////////////////
/* task2 */

// 由K230反馈
extern uint16_t center_x, center_y;
extern uint16_t lost; // 中心是否丢失

#define IMAGE_CENTER_X 320  // 图像中心X坐标（根据图像宽度一半设置）
#define IMAGE_CENTER_Y 240  // 图像中心Y坐标（根据图像高度一半设置）

#define ANGLE_X_MIN 80.0f  //50.0f    
#define ANGLE_X_MAX 110.0f //120.0f
#define ANGLE_Y_MIN 90.0f
#define ANGLE_Y_MAX 100.0f

#define CENTER_X_THRESHOLD 10   // 容许误差（像素）
#define CENTER_Y_THRESHOLD 10

#define LASER_OFFSET_X 154  // 激光头与摄像头中心在x方向的偏移 154 202

// 云台初始角度（实际初始化时可5设置）
float servo_x_angle = 80.0f;
float servo_y_angle = 103.0f;

// 是否击中靶心的标志
bool is_aimed = false;

void system_init(void)
{
	PID_Init(&servo_x_pid, 0.08f, 0.000f, 0.00f);  // kp, ki, kd
	PID_Init(&servo_y_pid, 0.001f, 0.000f, 0.00f);
	// set_angle(angle_x, angle_y);
}

uint8_t is_lost;

void aiming_system_start(void)
{
    if (lost) {
        is_lost = 1; // 未识别到中点
    }
    else {
        is_lost = 0;
    }

    // 考虑激光在摄像头右侧，误差补偿
    float error_x = (float)(IMAGE_CENTER_X - center_x + LASER_OFFSET_X);
    float error_y = (float)(IMAGE_CENTER_Y - center_y);

    // 判断是否已经瞄准（误差在允许范围内）
    if (fabsf(error_x) <= CENTER_X_THRESHOLD)  {
        if (!is_aimed) {
            ek_printf("AIMED OK\r\n");
            ek_printf("center = (%d, %d)\r\n", center_x, center_y);
            is_aimed = true;
        }
        return;
    } else {
        if (is_aimed) {
            ek_printf("目标偏离，重新调整...\r\n");
        }
        is_aimed = false;
        ek_printf("Not Aimed \r\n");
        ek_printf("center = (%d, %d), error = (%.1f, %.1f)\r\n", center_x, center_y, error_x, error_y);
    }

    // PID 控制角度修正（期望：图像中心 ± 偏移）
    float delta_x = servo_x_pid_task(IMAGE_CENTER_X + LASER_OFFSET_X, center_x);
    float delta_y = servo_y_pid_task(IMAGE_CENTER_Y, center_y);

    // 积分调节
    servo_x_angle += delta_x * 0.10f;
    servo_y_angle += delta_y * 0.15f;

    // 限制角度范围
    if (servo_x_angle < ANGLE_X_MIN) servo_x_angle = ANGLE_X_MIN;
    if (servo_x_angle > ANGLE_X_MAX) servo_x_angle = ANGLE_X_MAX;
    if (servo_y_angle < ANGLE_Y_MIN) servo_y_angle = ANGLE_Y_MIN;
    if (servo_y_angle > ANGLE_Y_MAX) servo_y_angle = ANGLE_Y_MAX;

    // if (servo_x_angle == ANGLE_X_MAX) {
    //     is_aimed = true;
    // }
    // else {
    //     is_aimed = false;
    // }
    
    // 控制舵机
    set_angle(servo_x_angle, 102);
}

/////////////////////////////////////////////////////////////////////////////
/* task3 */
#define ANGLE_X_MIN_0 40.0f  
#define ANGLE_X_MAX_0 200.0f 
#define ANGLE_Y_MIN_0 80.0f
#define ANGLE_Y_MAX_0 100.0f

#define CENTER_X_THRESHOLD_0 30   // 容许误差（像素）
#define CENTER_Y_THRESHOLD_0 20

#define LASER_OFFSET_X_0 154  // 激光头与摄像头中心在x方向的偏移154
#define LASER_OFFSET_Y_0 103  // 激光头与摄像头中心在Y方向的偏移85

static bool searching = false;
static bool scan_right = true;  // 扫描方向

#define SEARCH_STEP 0.5f      // 每次左右扫动的步进角度
#define SEARCH_DELAY 30       // 每步延迟(ms)，用于图像稳定
#define SERVO_Y_FIXED_ANGLE 102  // Y轴固定角度（只扫X）

void aiming_system_start_0(void)
{
    // 目标丢失判断
    if (lost) {     
        is_lost = 1;  // 没有识别到中点
    } else {
        is_lost = 0;
    }

    // ========== 1. 如果识别丢失，则主动左右步进搜索 ==========
    if (is_lost) {
        if (!searching) {
            ek_printf("🔍 中心点丢失，开始左右搜索...\r\n");
            searching = true;
        }

        // 左右扫描控制
        if (scan_right) {
            servo_x_angle += SEARCH_STEP;
            if (servo_x_angle >= ANGLE_X_MAX_0) {
                scan_right = false;
                servo_x_angle = ANGLE_X_MAX_0;
            }
        } else {
            servo_x_angle -= SEARCH_STEP;
            if (servo_x_angle <= ANGLE_X_MIN_0) {
                scan_right = true;
                servo_x_angle = ANGLE_X_MIN_0;
            }
        }

        // 限幅并设置舵机角度
        set_angle(servo_x_angle, SERVO_Y_FIXED_ANGLE);
        ek_printf("Scanning... X=%.2f\r\n", servo_x_angle);
        // delay_ms(SEARCH_DELAY); // 
        return;
    }

    // ========== 2. 一旦识别成功，停止搜索，转为PID修正 ==========
    if (searching) {
        // ek_printf("中心点识别成功，停止搜索，进入PID控制\r\n");
        searching = false;
    }

    float error_x = (float)(IMAGE_CENTER_X - center_x + LASER_OFFSET_X_0);
    float error_y = (float)(IMAGE_CENTER_Y - center_y + LASER_OFFSET_Y_0);

    if (fabsf(error_x) <= CENTER_X_THRESHOLD_0 ) {
        if (!is_aimed) {
            // ek_printf(" AIMED OK\r\n");
            // ek_printf("center = (%d, %d)\r\n", center_x, center_y);
            is_aimed = true;
        }
        return;
    } else {
        if (is_aimed) {
            // ek_printf(" 目标偏离，重新调整...\r\n");
        }
        is_aimed = false;
        // ek_printf("Not Aimed\r\n");
        // ek_printf("center = (%d, %d), error = (%.1f, %.1f)\r\n", center_x, center_y, error_x, error_y);
    }

    float delta_x = servo_x_pid_task(IMAGE_CENTER_X + LASER_OFFSET_X_0, center_x);
    float delta_y = servo_y_pid_task(IMAGE_CENTER_Y + LASER_OFFSET_Y_0, center_y);

    servo_x_angle += delta_x * 0.07f;
    servo_y_angle += delta_y * 0.02f;

    // 限制角度
    if (servo_x_angle < ANGLE_X_MIN_0) servo_x_angle = ANGLE_X_MIN_0;
    if (servo_x_angle > ANGLE_X_MAX_0) servo_x_angle = ANGLE_X_MAX_0;
    if (servo_y_angle < ANGLE_Y_MIN_0) servo_y_angle = ANGLE_Y_MIN_0;
    if (servo_y_angle > ANGLE_Y_MAX_0) servo_y_angle = ANGLE_Y_MAX_0;

    // 执行控制
    set_angle(servo_x_angle, 102);
}

/////////////////////////////////////////////////////////////////////////////

// 任务调度
uint8_t  TASK_INDEX;
static uint8_t is_task1;
static uint8_t task1_time;

static uint8_t is_task2;
static uint8_t task2_time;

static uint8_t is_task3;
static uint8_t task3_time;

void task1(void)
{
    if (is_task1) {
        is_task1 = 0;
        motor_pid_task(speed_pid.target);
    }
}

void task2(void)
{
    if (is_task2) {
        is_task2 = 0;
        aiming_system_start();
    }
}

void task3(void)
{
    if (is_task3) {
        is_task3 = 0;
        aiming_system_start_0();
    }
}

void TIMA1_IT_INST_IRQHandler(void)
{
    if (DL_TimerA_getPendingInterrupt(TIMA1_IT_INST) == DL_TIMER_IIDX_ZERO) {
		if (++task1_time >= 15) {
			task1_time = 0;
        	is_task1 = 1;
		}

		if (++task2_time >= 20) {
			task2_time = 0;
        	is_task2 = 1;
		}

        if (++task3_time >= 20) {
			task3_time = 0;
        	is_task3 = 1;
		}

        // 清除定时器中断标志
        DL_TimerA_clearInterruptStatus(TIMA1_IT_INST, DL_TIMER_INTERRUPT_ZERO_EVENT);
    }
}
////////////////////////////////////////////////////////////////////////////////////