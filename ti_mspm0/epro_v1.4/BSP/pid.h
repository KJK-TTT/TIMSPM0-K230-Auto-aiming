#ifndef __PID_H__
#define __PID_H__

#include "board.h"

typedef struct
{
    float kp;         // 比例系数
    float ki;         // 积分系数
    float kd;         // 微分系数
    float int_error;  // 积分累计值
    float last_error; // 上一次误差值
} STEP_PID_TypeDef;

void step_pid_init(STEP_PID_TypeDef *pid, float kp, float ki, float kd);
float step_pid_calc(STEP_PID_TypeDef *pid, float error);

/* **************************************************** */
typedef struct
{
    float target; // 目标值（速度或误差）
    float actual; // 实际值（速度或误差）
    float out;    // PID 输出值

    float kp; // 比例系数
    float ki; // 积分系数
    float kd; // 微分系数

    float error;        // 当前误差
    float last_error;   // 上次误差
    float int_error;    // 积分累计
    float max_out;      // 输出限幅上限
    float min_out;      // 输出限幅下限
    float max_integral; // 积分限幅
} PID_Typedef;

void pid_init(PID_Typedef *pid, float kp, float ki, float kd, float max_out, float min_out, float max_integral);
int pid_calculate(PID_Typedef *pid, float target, float actual, float filter_alpha);
void pid_reset(PID_Typedef *pid);

#endif
