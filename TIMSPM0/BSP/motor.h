#ifndef   __MOTOR_H__
#define   __MOTOR_H__

#include "board.h"

void Set_Motor_PWM(int pwmL, int pwmR);

extern int32_t Get_Encoder1_count,Get_Encoder2_count;
extern int32_t encoder1_cnt,encoder2_cnt; // 速度
extern int32_t encoder1_cnt_all,encoder2_cnt_all; 

#endif /* __MOTOR_H__ */
