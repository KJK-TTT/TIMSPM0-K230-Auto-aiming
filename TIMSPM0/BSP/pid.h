#ifndef __PID_H__
#define __PID_H__

#include "board.h"

typedef struct 
{
    float target;      // 目标速度
    float actual;      // 实际速度
    float out;         // PID输出值
	
    float kp;          // 比例系数
    float ki;          // 积分系数
    float kd;          // 微分系数
	
    float error;       // 当前误差
    float last_error;  // 上次误差
    float int_error;   // 误差积分
    float last_actual; // 上次实际值
    float max_out;     // 输出限幅上限
    float min_out;     // 输出限幅下限
    float max_integral;// 积分限幅
    float filter_coefficient;   // 滤波系数(0-1)
    float last_filtered_val;   // 上次滤波后的值
} PID_Typedef;

void speed_pid_init(void);
void turn_pid_init(void);
int speed_pid_task(float target_speed, float left_encoder, float right_encoder);
int turn_pid_task(float error);

extern PID_Typedef  speed_pid;//速度环
extern PID_Typedef  turn_pid; //转向环

///////////////////////////////////////////////////////////////////

typedef struct {
    float kp;           // 比例系数
    float ki;           // 积分系数
    float kd;           // 微分系数
    float int_error;    // 积分累计值
    float last_error;   // 上一次误差值
} PID_TypeDef;

extern PID_TypeDef servo_x_pid;  // X轴 PID
extern PID_TypeDef servo_y_pid;  // Y轴 PID

void PID_Init(PID_TypeDef *pid, float kp, float ki, float kd);
float PID_Calculate(PID_TypeDef *pid, float target, float actual);
float servo_x_pid_task(uint16_t target_x, uint16_t actual_x);
float servo_y_pid_task(uint16_t target_y, uint16_t actual_y);




#endif // __PID_H__