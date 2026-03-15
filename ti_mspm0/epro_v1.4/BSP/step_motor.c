#include "step_motor.h"

StepMotorTypeDef step_motor_x = {0};
StepMotorTypeDef step_motor_y = {0};

/**
 * @brief 启动步进电机
 * @param motor 0=X轴, 1=Y轴
 * @param dir   方向 (0=反转, 1=正转)
 * @param steps 目标步数
 */
void step_motor_start(uint8_t motor, uint8_t dir, uint16_t steps)
{
    StepMotorTypeDef *m = (motor == 0) ? &step_motor_x : &step_motor_y;

    m->running = 1;
    m->steps_left = steps;
    m->dir = dir;
    m->motor = motor;

    if (motor == 0)
    {
        // ---- X轴 ----
        if (dir)
            DL_GPIO_setPins(Step_Motor_PORT, Step_Motor_Step_Motor_X_DIR_PIN);
        else
            DL_GPIO_clearPins(Step_Motor_PORT, Step_Motor_Step_Motor_X_DIR_PIN);

        DL_GPIO_clearPins(Step_Motor_PORT, Step_Motor_Step_Motor_X_EN_PIN); // enable
        // DL_TimerG_setCaptureCompareValue(TIMG12_PWM_INST, 8000, DL_TIMER_CC_0_INDEX); // 启动 X轴 50% PWM
        DL_TimerG_startCounter(TIMG12_PWM_INST); // 启动 X轴 PWM
    }
    else
    {
        // ---- Y轴 ----
        if (dir)
            DL_GPIO_setPins(Step_Motor_PORT, Step_Motor_Step_Motor_Y_DIR_PIN);
        else
            DL_GPIO_clearPins(Step_Motor_PORT, Step_Motor_Step_Motor_Y_DIR_PIN);

        DL_GPIO_clearPins(Step_Motor_PORT, Step_Motor_Step_Motor_Y_EN_PIN); // enable
        // DL_TimerG_setCaptureCompareValue(TIMG12_PWM_INST, 8000, DL_TIMER_CC_1_INDEX); // 启动 Y轴 50% PWM
        DL_TimerG_startCounter(TIMG12_PWM_INST); // 启动 Y轴 PWM
    }
}

/**
 * @brief 停止电机
 * @param motor: 0=X轴, 1=Y轴
 */
void step_motor_stop(uint8_t motor)
{
    if (motor == 0)
    {
        // DL_TimerG_setCaptureCompareValue(TIMG12_PWM_INST, 0, DL_TIMER_CC_0_INDEX);
        DL_TimerG_stopCounter(TIMG12_PWM_INST);
        DL_GPIO_setPins(Step_Motor_PORT, Step_Motor_Step_Motor_X_EN_PIN); // disable
        step_motor_x.running = 0;
    }
    else
    {
        // DL_TimerG_setCaptureCompareValue(TIMG12_PWM_INST, 0, DL_TIMER_CC_1_INDEX);
        DL_TimerG_stopCounter(TIMG12_PWM_INST);
        DL_GPIO_setPins(Step_Motor_PORT, Step_Motor_Step_Motor_Y_EN_PIN); // disable
        step_motor_y.running = 0;
    }
}

/**
 * @brief 非阻塞实现 X 和 Y 步进电机走的步数
 */
void TIMA1_IT_INST_IRQHandler(void)
{
    if (DL_TimerA_getPendingInterrupt(TIMA1_IT_INST) == DL_TIMER_IIDX_ZERO)
    {
        DL_TimerA_clearInterruptStatus(TIMA1_IT_INST, DL_TIMER_INTERRUPT_ZERO_EVENT);

        // X轴步数统计
        if (step_motor_x.running && step_motor_x.steps_left > 0)
        {
            step_motor_x.steps_left--;
            if (step_motor_x.steps_left == 0)
            {
                step_motor_stop(0);
            }
        }

        // Y轴步数统计
        if (step_motor_y.running && step_motor_y.steps_left > 0)
        {
            step_motor_y.steps_left--;
            if (step_motor_y.steps_left == 0)
            {
                step_motor_stop(1);
            }
        }
    }
}
