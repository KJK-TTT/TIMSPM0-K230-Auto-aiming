#include "task.h"

/* ************ Task 1: 静态条件下追踪 ************ */
STEP_PID_TypeDef step_x_pid = {0};
STEP_PID_TypeDef step_y_pid = {0};

void step_pid_all_init(void)
{
    step_pid_init(&step_x_pid, 7.0f, 0.00f, 0.05f);
    step_pid_init(&step_y_pid, 7.0f, 0.00f, 0.05f);
}

uint8_t is_aiming = 0; // 激光瞄准标志位

void gimbal_step_pid_control(void)
{
    static uint8_t miss_counter = 0;
    const uint8_t miss_limit = 5;

    bool has_target = target_detected &&
                      !(dx_center_signed == 999 && dy_center_signed == 999);

    if (!has_target)
    {
        if (miss_counter < miss_limit)
        {
            miss_counter++;
        }
        else
        {
            step_motor_stop(0); // X轴停止
            step_motor_stop(1); // Y轴停止
            step_x_pid.int_error = 0;
            step_y_pid.int_error = 0;
        }
        //        is_aiming = 0;
        return;
    }
    miss_counter = 0;

    float error_x = dx_center_signed + OFFSET_CENTER_X;
    float error_y = dy_center_signed + OFFSET_CENTER_Y;

    float output_x = step_pid_calc(&step_x_pid, error_x);
    float output_y = step_pid_calc(&step_y_pid, error_y);

    if (fabs(error_x) < 5)
        output_x = 0;
    if (fabs(error_y) < 5)
        output_y = 0;

    is_aiming = (fabs(error_x) <= 5 && fabs(error_y) <= 5);

    if (!step_motor_x.running)
    {
        uint8_t dir_x = (output_x > 0) ? 1 : 0;
        uint16_t steps_x = (uint16_t)fabs(output_x);
        if (steps_x >= 1)
            step_motor_start(0, dir_x, steps_x);
    }

    if (!step_motor_y.running)
    {
        uint8_t dir_y = (output_y > 0) ? 0 : 1;
        uint16_t steps_y = (uint16_t)fabs(output_y);
        if (steps_y >= 1)
            step_motor_start(1, dir_y, steps_y);
    }

    u0_rx_ok_flag = 0;
}

/* ************ Task 2: 动态条件下追踪 ************ */
PID_Typedef left_motor_pid; 
PID_Typedef right_motor_pid;
PID_Typedef turn_pid;
Gray_TypeDef gray_sensor;

// 初始期望速度(实时编码值)
int target_base_speed = 10; 

// 目标偏航角
float straight_target_yaw = 0;

// Yaw 前馈系数
#define KFF_YAW 0.45f

void encoder_motor_pid_init(void)
{
    pid_init(&left_motor_pid, 0.9f, 0.016f, 0.0f, 80, -80, 1000);  // 0.9f, 0.016f, 0.0f, 80, -80, 1000
    pid_init(&right_motor_pid, 0.9f, 0.016f, 0.0f, 80, -80, 1000); // 0.9f, 0.016f, 0.0f, 80, -80, 1000
    pid_init(&turn_pid, 2.00f, 0.0f, 60.5f, 80, -80, 800);         // 8.5f, 0.0f, 60.5f, 80, -80, 800
}

void encoder_motor_pid(float Yaw)
{
    // 读取灰度
    gray_read(&gray_sensor);

    if (gray_sensor.left4 &&
        gray_sensor.left3 &&
        gray_sensor.left2 &&
        gray_sensor.left1 &&
        gray_sensor.right1 &&
        gray_sensor.right2 &&
        gray_sensor.right3 &&
        gray_sensor.right4)
    {
        // 全部传感器无信号，停止小车
        Set_Motor_PWM(0, 0);
        return;
    }
	
	// 计算灰度误差
    float line_error = calculate_tracking_error(&gray_sensor);

    // 灰度 PID 输出
    float turn_gray = pid_calculate(&turn_pid, 0.0f, line_error, 0.4f);

    //  Yaw 前馈输出
    float yaw_error = straight_target_yaw - Yaw;
    if (yaw_error > 180)
        yaw_error -= 360;
    if (yaw_error < -180)
        yaw_error += 360;

    float yaw_ff = yaw_error * KFF_YAW;

    // 组合转向输出
    float turn_total = turn_gray + yaw_ff;

    // 左右轮目标速度
    float target_left_speed = target_base_speed - turn_total;
    float target_right_speed = target_base_speed + turn_total;

    //  编码器 PID 调整
    int pwm_L = pid_calculate(&left_motor_pid, target_left_speed, (float)encoder1_cnt, 0.6f);
    int pwm_R = pid_calculate(&right_motor_pid, target_right_speed, (float)encoder2_cnt, 0.6f);

    // 输出 PWM
    Set_Motor_PWM(pwm_L, pwm_R);
}

/* ************ 任务调度 ************ */
volatile static uint8_t is_task1;
static uint8_t task1_time;
volatile static uint8_t is_task2;
static uint8_t task2_time;

volatile static uint8_t is_lcd_running;
static uint8_t lcd_time;

void task1(void)
{
    if (is_task1)
    {
        is_task1 = 0;
        gimbal_step_pid_control();
    }
}

void task2(void)
{
    if (is_task2)
    {
        is_task2 = 0;
        encoder_motor_pid(Yaw);
    }
}

volatile static uint8_t is_buzzer_on;
static uint8_t buzzer_time;
static uint8_t last_aiming = 0;
void alert_task(void)
{
    // --- 激光控制 ---
    if (is_aiming)
        laser_on();
    else
        laser_off();
	
	// --- 蜂鸣器控制 ---
    if (is_aiming && !last_aiming)
    {
        is_buzzer_on = 1; // 响 200ms
        buzzer_time = 0;
    }
    last_aiming = is_aiming;

    if (is_buzzer_on)
        buzzer_on();
    else
        buzzer_off();
}

void lcd_task(void)
{
    if (is_lcd_running)
    {
        lcd_process(); 
        is_lcd_running = 0;
    }
}

void task_process(void)
{
    // lcd/laser/buzzer
    lcd_task();
    alert_task();
    // 静态/动态task
    if (task_index == 1 && is_task1_running)
    {
        task1();
    }
    else if (task_index == 2 && is_task2_running)
    {
		// 重设pid参数
        step_pid_init(&step_x_pid, 7.0f, 0.00f, 0.55f);
        step_pid_init(&step_y_pid, 7.0f, 0.00f, 0.55f);
        task1();
        task2();
    }
}

void TIMA0_IT_INST_IRQHandler(void) // 1ms定时器中断
{
    if (DL_TimerA_getPendingInterrupt(TIMA0_IT_INST) == DL_TIMER_IIDX_ZERO)
    {
        DL_TimerA_clearInterruptStatus(TIMA0_IT_INST, DL_TIMER_INTERRUPT_ZERO_EVENT);
        if (++task1_time >= 20)
        {
            task1_time = 0;
            is_task1 = 1;
        }
        if (++task2_time >= 10)
        {
            task2_time = 0;
            is_task2 = 1;
        }
        if (++lcd_time >= 100)
        {
            lcd_time = 0;
            is_lcd_running = 1;
        }

        if (is_buzzer_on)
        {
            if (++buzzer_time >= 200)
            {
                buzzer_time = 0;
                is_buzzer_on = 0;
            }
        }
    }
}
