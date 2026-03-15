#include "encoder_motor.h"

int32_t Get_Encoder1_count, Get_Encoder2_count; // 位置
int32_t encoder1_cnt, encoder2_cnt;             // 速度
int32_t encoder1_cnt_all, encoder2_cnt_all;

/**
 * @brief 设置左右电机的方向和 PWM 占空比
 *        正数表示正转，负数表示反转
 *
 * @param pwmL 左电机 PWM 值
 * @param pwmR 右电机 PWM 值
 */
void Set_Motor_PWM(int pwmL, int pwmR)
{
    // ===== 左电机 =====
    if (pwmL >= 0)
    {
        // 正转：AIN1=1, AIN2=0
        DL_GPIO_setPins(TB6612_PORT, TB6612_AIN1_PIN);
        DL_GPIO_clearPins(TB6612_PORT, TB6612_AIN2_PIN);
    }
    else
    {
        // 反转：AIN1=0, AIN2=1
        DL_GPIO_setPins(TB6612_PORT, TB6612_AIN2_PIN);
        DL_GPIO_clearPins(TB6612_PORT, TB6612_AIN1_PIN);
    }

    DL_Timer_setCaptureCompareValue(TIMG0_PWM_INST, abs(pwmL), GPIO_TIMG0_PWM_C0_IDX);

    // ===== 右电机 =====
    if (pwmR >= 0)
    {
        DL_GPIO_setPins(TB6612_PORT, TB6612_BIN1_PIN);
        DL_GPIO_clearPins(TB6612_PORT, TB6612_BIN2_PIN);
    }
    else
    {
        DL_GPIO_setPins(TB6612_PORT, TB6612_BIN2_PIN);
        DL_GPIO_clearPins(TB6612_PORT, TB6612_BIN1_PIN);
    }

    DL_Timer_setCaptureCompareValue(TIMG0_PWM_INST, abs(pwmR), GPIO_TIMG0_PWM_C1_IDX);
}

/**
 * @brief 左右电机编码器触发的外部中断
 */
void GROUP1_IRQHandler(void)
{
    uint32_t gpio_status = DL_GPIO_getEnabledInterruptStatus(GPIOA, Encoder_E1_A_PIN | Encoder_E1_B_PIN | Encoder_E2_A_PIN | Encoder_E2_B_PIN);

    // 编码器 E1
    if (gpio_status & Encoder_E1_A_PIN)
    {
        if (!DL_GPIO_readPins(GPIOA, Encoder_E1_B_PIN))
            Get_Encoder1_count--;
        else
            Get_Encoder1_count++;
    }

    if (gpio_status & Encoder_E1_B_PIN)
    {
        if (!DL_GPIO_readPins(GPIOA, Encoder_E1_A_PIN))
            Get_Encoder1_count++;
        else
            Get_Encoder1_count--;
    }

    // 编码器 E2
    if (gpio_status & Encoder_E2_A_PIN)
    {
        if (!DL_GPIO_readPins(GPIOA, Encoder_E2_B_PIN))
            Get_Encoder2_count--;
        else
            Get_Encoder2_count++;
    }

    if (gpio_status & Encoder_E2_B_PIN)
    {
        if (!DL_GPIO_readPins(GPIOA, Encoder_E2_A_PIN))
            Get_Encoder2_count++;
        else
            Get_Encoder2_count--;
    }

    DL_GPIO_clearInterruptStatus(GPIOA, Encoder_E1_A_PIN | Encoder_E1_B_PIN | Encoder_E2_A_PIN | Encoder_E2_B_PIN);
}

/**
 * @brief 获取左右电机编码器的速度和位置
 */
void TIMG6_IT_INST_IRQHandler(void) // 20ms中断
{
    if (DL_TimerG_getPendingInterrupt(TIMG6_IT_INST) == DL_TIMER_IIDX_ZERO)
    {
        encoder1_cnt = Get_Encoder1_count;
        encoder2_cnt = -Get_Encoder2_count;

        encoder1_cnt_all += encoder1_cnt;
        encoder2_cnt_all += encoder2_cnt;

        Get_Encoder1_count = 0;
        Get_Encoder2_count = 0;

        DL_TimerG_clearInterruptStatus(TIMG6_IT_INST, DL_TIMER_INTERRUPT_ZERO_EVENT);
    }
}
