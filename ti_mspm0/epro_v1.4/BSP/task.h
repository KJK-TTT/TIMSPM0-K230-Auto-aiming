#ifndef __TASK_H__
#define __TASK_H__

#include "board.h"
#include "com_k230.h"
#include "com_lcd.h"
#include "step_motor.h"
#include "encoder_motor.h"
#include "pid.h"
#include "gray.h"
#include "misc_bsp.h"
#include "com_jy61p.h"

#define OFFSET_CENTER_X -10 // x轴中心偏移量
#define OFFSET_CENTER_Y 3   // y轴中心偏移量

void step_pid_all_init(void);
void gimbal_step_pid_control(void);
extern uint8_t is_aiming; // 激光瞄准标志位
extern Gray_TypeDef gray_sensor;
void encoder_motor_pid_init(void);

void lcd_task(void);
void task_process(void);

#endif
