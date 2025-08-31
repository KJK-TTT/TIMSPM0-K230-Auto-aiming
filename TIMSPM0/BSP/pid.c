#include "pid.h"

PID_Typedef  speed_pid;//速度环
PID_Typedef  turn_pid; //转向环

void speed_pid_init(void)
{
    speed_pid.target = 65.0f; // 初始目标速度60

    speed_pid.kp = 0.20f;  // 比例系数0.25f
    speed_pid.ki = 0.018f; // 积分系数0.018f;
    speed_pid.kd = 0.00f;  // 微分系数0.00f;

    speed_pid.max_out = 80;
    speed_pid.min_out = -80;

    speed_pid.max_integral = 800;

    speed_pid.int_error = 0;
    speed_pid.last_error = 0;
    speed_pid.last_actual = 0;
    speed_pid.filter_coefficient = 0.70f;
    speed_pid.last_filtered_val = 0;
}

void turn_pid_init(void)
{
   turn_pid.kp = 80.0f;  // 比例系数80.0f;
   turn_pid.ki = 0.00f;  // 积分系数0.0f;
   turn_pid.kd = 0.15f;  //  微分系数0.12f;

   turn_pid.max_out =  100;// 80
   turn_pid.min_out = -100;//-80
   
   turn_pid.error = 0;
   turn_pid.last_error = 0;
   turn_pid.int_error = 0;
}

int speed_pid_task(float target_speed, float enc1, float enc2)
{
    float actual_speed = (enc1 + enc2) / 2.0f;
    speed_pid.actual = actual_speed;
    // lc_printf("actual_speed:%f\n", actual_speed);
    
    float filtered_speed = speed_pid.filter_coefficient * actual_speed +
                           (1.0f - speed_pid.filter_coefficient) * speed_pid.last_filtered_val;
    speed_pid.last_filtered_val = filtered_speed;

    speed_pid.error = target_speed - filtered_speed;
    speed_pid.int_error += speed_pid.error;

    // 积分限幅
    if (speed_pid.int_error > speed_pid.max_integral)
        speed_pid.int_error = speed_pid.max_integral;
    else if (speed_pid.int_error < -speed_pid.max_integral)
        speed_pid.int_error = -speed_pid.max_integral;

    // PI 控制器输出（无微分）
    speed_pid.out = speed_pid.kp * speed_pid.error +
                    speed_pid.ki * speed_pid.int_error +
                    speed_pid.kd * (speed_pid.error - speed_pid.last_error);

    // 输出限幅
    if (speed_pid.out > speed_pid.max_out)
        speed_pid.out = speed_pid.max_out;
    else if (speed_pid.out < speed_pid.min_out)
        speed_pid.out = speed_pid.min_out;

    speed_pid.last_error = speed_pid.error;

    return (int)speed_pid.out;
}

int turn_pid_task(float error)
{
	turn_pid.error = error;
	
	turn_pid.out = turn_pid.kp * turn_pid.error + turn_pid.kd * (turn_pid.error - turn_pid.last_error);
	
	if (turn_pid.out > turn_pid.max_out)
			turn_pid.out = turn_pid.max_out;
	else if (turn_pid.out < turn_pid.min_out)
			turn_pid.out = turn_pid.min_out;
	
	turn_pid.last_error = turn_pid.error;
	
	return (int)turn_pid.out;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PID_TypeDef servo_x_pid = {0};
PID_TypeDef servo_y_pid = {0};

#define PID_INT_MAX 1000.0f
#define PID_INT_MIN -1000.0f

// 初始化 PID 参数
void PID_Init(PID_TypeDef *pid, float kp, float ki, float kd)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->int_error = 0;
    pid->last_error = 0;
}

float PID_Calculate(PID_TypeDef *pid, float target, float actual)
{
    float error = target - actual;

    pid->int_error += error;

    // 防止积分饱和
    if (pid->int_error > PID_INT_MAX) pid->int_error = PID_INT_MAX;
    if (pid->int_error < PID_INT_MIN) pid->int_error = PID_INT_MIN;

    float derivative = error - pid->last_error;
    pid->last_error = error;

    float output = pid->kp * error + pid->ki * pid->int_error + pid->kd * derivative;
    return output;
}

// 云台 PID 控制任务
float servo_x_pid_task(uint16_t target_x, uint16_t actual_x)
{
    return PID_Calculate(&servo_x_pid, (float)target_x, (float)actual_x);
}

float servo_y_pid_task(uint16_t target_y, uint16_t actual_y)
{
    return PID_Calculate(&servo_y_pid, (float)target_y, (float)actual_y);
}


