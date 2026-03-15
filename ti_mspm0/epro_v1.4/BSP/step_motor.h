#ifndef __STEP_MOTOR_H__
#define __STEP_MOTOR_H__

#include "board.h"

typedef struct {
    uint8_t running;       // 电机是否在转
    uint16_t steps_left;   // 剩余步数
    uint8_t dir;           // 当前方向
    uint8_t motor;         // 0 = X轴, 1 = Y轴
} StepMotorTypeDef;

void step_motor_start(uint8_t motor, uint8_t dir, uint16_t steps);
void step_motor_stop(uint8_t motor);

extern StepMotorTypeDef step_motor_x;
extern StepMotorTypeDef step_motor_y;

#endif
