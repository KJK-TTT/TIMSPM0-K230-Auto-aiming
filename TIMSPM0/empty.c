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
 
#include "ti_msp_dl_config.h"
#include "board.h"
#include "misc_bsp.h"
#include "motor.h"
#include "oled.h"
#include "bmp.h"
#include "servo.h"
#include "task.h"

uint8_t set_laps = 1;          // 默认一圈
uint8_t is_task_start = 0;     // 启动标志

void key_process(void)
{
    static uint8_t key_val = 0, key_down = 0, key_old = 0;
    key_val = key_read();
    key_down = key_val & (key_val ^ key_old); 
    key_old = key_val;

    if (key_down & 0x01) { // key1：切换任务（0~2）
        buzzer_on(200);
        if (++TASK_INDEX > 2) TASK_INDEX = 0;
    }
    else if (key_down & 0x02) { // key2：配置任务参数
        buzzer_on(200);
        switch (TASK_INDEX) {
            case 0:  // 任务1配置：设置圈数
                if (++set_laps > 5) set_laps = 1;
            break;
            case 1:  // 任务2配置
                
                break;
            case 2:
                
                break;
        }
    }
    else if (key_down & 0x04) { // key3：启动任务
        buzzer_on(200);
        is_task_start = 1;
    }
}

void task_process(void)
{
    if (is_task_start) {
        switch (TASK_INDEX) {
        case 0:
            task1(); break;
        case 1:
            task2(); break;
        case 2:
            task3(); break;
        }
    }
}


void disp_process(void)
{
    switch (TASK_INDEX) {
        case 0:
            OLED_ShowString(20, 24, (uint8_t *)"Task 1", 16, 1);
            OLED_ShowString(20, 40, (uint8_t *)"set_laps: ", 16, 1);
            OLED_ShowNum(90, 40, set_laps, 1, 16, 1); 
            break;

        case 1:
            OLED_ShowString(20, 24, (uint8_t *)"Task 2", 16, 1);
            OLED_ShowString(20, 40, (uint8_t *)"is_aimed:", 16, 1);
            OLED_ShowNum(90, 40, is_aimed, 1, 16, 1); 
            break;

        case 2:
            OLED_ShowString(20, 24, (uint8_t *)"Task 3", 16, 1);
            OLED_ShowString(20, 40, (uint8_t *)"is_aimed:", 16, 1);
            OLED_ShowNum(92, 40, is_aimed, 1, 16, 1); 
            break;
    }

    OLED_Refresh();
}


void sweep_servo(void)
{
    // 从 80° 到 90°
    for (int angle = 80; angle <= 90; angle++) {
        set_angle(angle, 103);
        delay_ms(1000);
    }

    // 从 90° 回到 80°
    for (int angle = 89; angle >= 80; angle--) {
        set_angle(angle, 103);
        delay_ms(1000);
    }
}

int main(void)
{
    SYSCFG_DL_init();

    NVIC_ClearPendingIRQ(Encoder1_INT_IRQN);
    NVIC_ClearPendingIRQ(Encoder2_INT_IRQN);
    NVIC_ClearPendingIRQ(TIMA0_IC_INST_INT_IRQN);
    NVIC_ClearPendingIRQ(TIMA1_IT_INST_INT_IRQN);
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN); 
    NVIC_ClearPendingIRQ(UART_2_INST_INT_IRQN);
    
    NVIC_EnableIRQ(Encoder1_INT_IRQN);
	NVIC_EnableIRQ(Encoder2_INT_IRQN);
	NVIC_EnableIRQ(TIMA0_IC_INST_INT_IRQN);
    NVIC_EnableIRQ(TIMA1_IT_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_2_INST_INT_IRQN);

    OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
    OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
    OLED_Clear();

    OLED_ShowString(0,0,(uint8_t *)"init success!",16,1);
    OLED_Refresh();

    speed_pid_init(); // motor pid
    turn_pid_init();  // motor pid

    system_init(); // servo pid
    
    // set_angle(80,100);
    // set_angle(80,100); // (255,147)
    // set_angle(93,100); // (255,148)

    // set_angle(90,97);
    // set_angle(90,105);
    //laser_on();
    // laser_off();

    buzzer_on(200);
    DL_GPIO_setPins(LED_PORT,  LED_PIN_22_PIN);
    lc_printf("system init success!\n");
    ek_printf("bluetooth init!\r\n");

    while (1) {
        key_process();
        task_process();
        disp_process();
        is_aimed ? laser_on() : laser_off();

        // sweep_servo(); // 测试舵机

        // ek_printf("E1_ALL:%d, E2_ALL:%d\r\n", encoder1_cnt_all,encoder2_cnt_all);
        // ek_printf("{pid:%.2f,%.2f,%.2f\n}", speed_pid.target,speed_pid.actual,speed_pid.out);
    }
}
