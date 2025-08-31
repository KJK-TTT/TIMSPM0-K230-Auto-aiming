#include "motor.h"

int32_t Get_Encoder1_count,Get_Encoder2_count; // 位置
int32_t encoder1_cnt,encoder2_cnt; // 速度
int32_t encoder1_cnt_all,encoder2_cnt_all; 

uint32_t gpio_interrup1,gpio_interrup2;

/**
 * @brief 设置左右电机的方向和 PWM 占空比
 *        正数表示正转，负数表示反转
 * 
 * @param pwmL 左电机 PWM 值
 * @param pwmR 右电机 PWM 值
 */
void Set_Motor_PWM(int pwmL, int pwmR)
{
    // ===== 左电机方向控制 =====
    if (pwmL > 0)
    {
        // 左电机正转（修正后）：AIN1 高，AIN2 低
        DL_GPIO_setPins(TB6612_1_PORT, TB6612_1_TB1_AIN1_PIN);
        DL_GPIO_clearPins(TB6612_1_PORT, TB6612_1_TB1_AIN2_PIN);
    }
    else
    {
        // 左电机反转（修正后）：AIN2 高，AIN1 低
        DL_GPIO_setPins(TB6612_1_PORT, TB6612_1_TB1_AIN2_PIN);
        DL_GPIO_clearPins(TB6612_1_PORT, TB6612_1_TB1_AIN1_PIN);
    }

    // 设置左电机 PWM 占空比（转速）
    DL_Timer_setCaptureCompareValue(TIMG0_PWM_INST, abs(pwmL), GPIO_TIMG0_PWM_C0_IDX);

    // ===== 右电机方向控制 =====
    if (pwmR > 0)
    {
        // 右电机正转（修正后）：BIN1 高，BIN2 低
        DL_GPIO_setPins(TB6612_1_PORT, TB6612_1_TB1_BIN1_PIN);
        DL_GPIO_clearPins(TB6612_1_PORT, TB6612_1_TB1_BIN2_PIN);
    }
    else
    {
        // 右电机反转（修正后）：BIN2 高，BIN1 低
        DL_GPIO_setPins(TB6612_1_PORT, TB6612_1_TB1_BIN2_PIN);
        DL_GPIO_clearPins(TB6612_1_PORT, TB6612_1_TB1_BIN1_PIN);
    }

    // 设置右电机 PWM 占空比（转速）
    DL_Timer_setCaptureCompareValue(TIMG0_PWM_INST, abs(pwmR), GPIO_TIMG0_PWM_C1_IDX);
}


void GROUP1_IRQHandler(void)
{
    // 获取中断状态
    gpio_interrup1 = DL_GPIO_getEnabledInterruptStatus(Encoder1_PORT, Encoder1_E1_A_PIN | Encoder1_E1_B_PIN);
    gpio_interrup2 = DL_GPIO_getEnabledInterruptStatus(Encoder2_PORT, Encoder2_E2_A_PIN | Encoder2_E2_B_PIN);

    // encoder1
    if ((gpio_interrup1 & Encoder1_E1_A_PIN) == Encoder1_E1_A_PIN)
    {
        if (!DL_GPIO_readPins(Encoder1_PORT, Encoder1_E1_B_PIN))
            Get_Encoder1_count--;
        else
            Get_Encoder1_count++;
    }
    else if ((gpio_interrup1 & Encoder1_E1_B_PIN) == Encoder1_E1_B_PIN)
    {
        if (!DL_GPIO_readPins(Encoder1_PORT, Encoder1_E1_A_PIN))
            Get_Encoder1_count++;
        else
            Get_Encoder1_count--;
    }

    // encoder2
    if ((gpio_interrup2 & Encoder2_E2_A_PIN) == Encoder2_E2_A_PIN)
    {
        if (!DL_GPIO_readPins(Encoder2_PORT, Encoder2_E2_B_PIN))
            Get_Encoder2_count--;
        else
            Get_Encoder2_count++;
    }
    else if ((gpio_interrup2 & Encoder2_E2_B_PIN) == Encoder2_E2_B_PIN)
    {
        if (!DL_GPIO_readPins(Encoder2_PORT, Encoder2_E2_A_PIN))
            Get_Encoder2_count++;
        else
            Get_Encoder2_count--;
    }
    // 清除中断标志
    DL_GPIO_clearInterruptStatus(Encoder1_PORT, Encoder1_E1_A_PIN | Encoder1_E1_B_PIN);
    DL_GPIO_clearInterruptStatus(Encoder2_PORT, Encoder2_E2_A_PIN | Encoder2_E2_B_PIN);
}

void TIMA0_IC_INST_IRQHandler(void)
{
    if (DL_TimerA_getPendingInterrupt(TIMA0_IC_INST) == DL_TIMER_IIDX_ZERO)
    {
        encoder1_cnt =  Get_Encoder1_count;
		encoder2_cnt = -Get_Encoder2_count;
        
        encoder1_cnt_all += encoder1_cnt;
        encoder2_cnt_all += encoder2_cnt;
        
        Get_Encoder1_count = 0;
        Get_Encoder2_count = 0;

        // 清除定时器中断标志
        DL_TimerA_clearInterruptStatus(TIMA0_IC_INST, DL_TIMER_INTERRUPT_ZERO_EVENT);
    }
}
