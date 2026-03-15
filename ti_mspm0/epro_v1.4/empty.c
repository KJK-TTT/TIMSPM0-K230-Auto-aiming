/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @brief    "基于MSPM0与K230的目标识别追踪系统"主控端软件设计
 * @version  v1.2
*/

#include "task.h"

int main(void)
{
	/* system config initialize */
    SYSCFG_DL_init();                             // system config init
    NVIC_ClearPendingIRQ(TIMA0_IT_INST_INT_IRQN); // task scheduling timer interrupt
    NVIC_ClearPendingIRQ(TIMA1_IT_INST_INT_IRQN); // step motor timer interrupt
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);   // K230 --> UART0 interrupt
    NVIC_ClearPendingIRQ(UART_2_INST_INT_IRQN);   // JY61P  --> UART2 interrupt
    NVIC_ClearPendingIRQ(UART_3_INST_INT_IRQN);   // LCD  --> UART3 interrupt
    NVIC_ClearPendingIRQ(Encoder_INT_IRQN);       // Encoder interrupt
    NVIC_ClearPendingIRQ(TIMG6_IT_INST_INT_IRQN); // Encoder timer interrupt

    NVIC_EnableIRQ(TIMA0_IT_INST_INT_IRQN); 	  // task scheduling timer interrupt
    NVIC_EnableIRQ(TIMA1_IT_INST_INT_IRQN); 	  // step motor timer interrupt
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);   	  // K230 --> UART0 interrupt
    NVIC_EnableIRQ(UART_2_INST_INT_IRQN);   	  // JY61P  --> UART3 interrupt
    NVIC_EnableIRQ(UART_3_INST_INT_IRQN);   	  // LCD  --> UART3 interrupt
    NVIC_EnableIRQ(Encoder_INT_IRQN);       	  // Encoder interrupt
    NVIC_EnableIRQ(TIMG6_IT_INST_INT_IRQN); 	  // Encoder timer interrupt
	
	/* system startup warnning */
	DL_GPIO_setPins(Buzzer_PORT, Buzzer_PIN_7_PIN);   // Buzzer on
    delay_ms(300);
    DL_GPIO_clearPins(Buzzer_PORT, Buzzer_PIN_7_PIN); // Buzzer off
    DL_GPIO_clearPins(LED_PORT, LED_PIN_22_PIN);      // LED off
    DL_GPIO_clearPins(Laser_PORT, Laser_PIN_9_PIN);   // Laser off
    
	/* pid param setting */
    step_pid_all_init();      // step motor pid init
    encoder_motor_pid_init(); // encoder motor pid init

    lc_printf("system init success!\n");           // K230      -- UART0
    ek_printf("bluetooth:system init success!\n"); // bluetooth -- UART1

    // step_motor_start(1, 1, 3000);
    // step_motor_start(0, 1, 3000);
    // Set_Motor_PWM(20, 20);

    while (1)
    {
        task_process();
        // ek_printf("E1:%d, E2:%d\r\n", encoder1_cnt,encoder2_cnt);
    }
}
