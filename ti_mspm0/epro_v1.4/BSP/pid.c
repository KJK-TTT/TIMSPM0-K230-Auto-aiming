#include "pid.h"

/**
 * @brief 步进电机PID初始化
 * @param pid pid结构体
 * @param kp  比例系数
 * @param ki  积分系数
 * @param kd  微分系数
 */
void step_pid_init(STEP_PID_TypeDef *pid, float kp, float ki, float kd)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->int_error = 0;
    pid->last_error = 0;
}

/**
 * @brief 步进电机PID计算
 * @param pid   pid结构体
 * @param error 与中心点的误差
 * @return 给到步进电机的步数
 */
float step_pid_calc(STEP_PID_TypeDef *pid, float error)
{
    // 计算积分项
    pid->int_error += error;

    // 积分限幅，防止积分饱和
    if (pid->int_error > 2000)
        pid->int_error = 2000;
    if (pid->int_error < -2000)
        pid->int_error = -2000;

    // 微分项
    float derivative = error - pid->last_error;

    // PID 输出
    float output = pid->kp * error + pid->ki * pid->int_error + pid->kd * derivative;

    pid->last_error = error;

    return output;
}

/* ************************************************************************************************************ */
/**
 * @brief PID初始化(用于左右编码器电机和灰度)
 * @param pid pid结构体
 * @param kp  比例系数
 * @param ki  积分系数
 * @param kd  微分系数
 * @param max_out  输出上线
 * @param min_out  输出下限
 * @param max_integral  积分上限
 */
void pid_init(PID_Typedef *pid, float kp, float ki, float kd, float max_out, float min_out, float max_integral)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->error = 0;
    pid->last_error = 0;
    pid->int_error = 0;
    pid->out = 0;
    pid->max_out = max_out;
    pid->min_out = min_out;
    pid->max_integral = max_integral;
}

/**
 * @brief PID输出计算(用于左右编码器电机和灰度)
 * @param pid    pid结构体
 * @param target 目标值
 * @param actual 实际值
 * @param filter_alpha 滤波系数(0 < α < 1)
 * @return PID输出(调控PWM)
 */
int pid_calculate(PID_Typedef *pid, float target, float actual, float filter_alpha)
{
    float error = target - actual;
    pid->int_error += error;

    // 积分限幅
    if (pid->int_error > pid->max_integral)
        pid->int_error = pid->max_integral;
    else if (pid->int_error < -pid->max_integral)
        pid->int_error = -pid->max_integral;

    // PID 计算
    float out = pid->kp * error + pid->ki * pid->int_error + pid->kd * (error - pid->last_error);

    // 输出限幅
    if (out > pid->max_out)
        out = pid->max_out;
    else if (out < pid->min_out)
        out = pid->min_out;

    // 低通滤波平滑输出
    out = filter_alpha * pid->out + (1.0f - filter_alpha) * out;

    pid->last_error = error;
    pid->out = out;

    return (int)out;
}

/**
 * @brief PID清0(用于左右编码器电机和灰度)
 * @param pid    pid结构体
 */
void pid_reset(PID_Typedef *pid)
{
    pid->error = 0;
    pid->last_error = 0;
    pid->int_error = 0;
    pid->out = 0;
}

/* ************************************************************************************* */
