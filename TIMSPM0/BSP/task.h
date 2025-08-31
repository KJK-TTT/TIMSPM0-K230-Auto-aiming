#ifndef __TASK_H__
#define __TASK_H__

#include "board.h"
#include "pid.h"
#include "motor.h"
#include "servo.h"
#include "gray.h"
#include "com_jy61p.h"
#include "misc_bsp.h"

void task1(void);
///////////////////////////////////////////////////////////////////
void system_init(void);
void task2(void);
void task3(void);

extern uint8_t  TASK_INDEX;
extern bool is_aimed;

#endif /* __TASK_H__ */
