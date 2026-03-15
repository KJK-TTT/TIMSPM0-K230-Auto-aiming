/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
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

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for TIMG12_PWM */
#define TIMG12_PWM_INST                                                   TIMG12
#define TIMG12_PWM_INST_IRQHandler                             TIMG12_IRQHandler
#define TIMG12_PWM_INST_INT_IRQN                               (TIMG12_INT_IRQn)
#define TIMG12_PWM_INST_CLK_FREQ                                        16000000
/* GPIO defines for channel 0 */
#define GPIO_TIMG12_PWM_C0_PORT                                            GPIOB
#define GPIO_TIMG12_PWM_C0_PIN                                    DL_GPIO_PIN_20
#define GPIO_TIMG12_PWM_C0_IOMUX                                 (IOMUX_PINCM48)
#define GPIO_TIMG12_PWM_C0_IOMUX_FUNC               IOMUX_PINCM48_PF_TIMG12_CCP0
#define GPIO_TIMG12_PWM_C0_IDX                               DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_TIMG12_PWM_C1_PORT                                            GPIOB
#define GPIO_TIMG12_PWM_C1_PIN                                    DL_GPIO_PIN_24
#define GPIO_TIMG12_PWM_C1_IOMUX                                 (IOMUX_PINCM52)
#define GPIO_TIMG12_PWM_C1_IOMUX_FUNC               IOMUX_PINCM52_PF_TIMG12_CCP1
#define GPIO_TIMG12_PWM_C1_IDX                               DL_TIMER_CC_1_INDEX

/* Defines for TIMG0_PWM */
#define TIMG0_PWM_INST                                                     TIMG0
#define TIMG0_PWM_INST_IRQHandler                               TIMG0_IRQHandler
#define TIMG0_PWM_INST_INT_IRQN                                 (TIMG0_INT_IRQn)
#define TIMG0_PWM_INST_CLK_FREQ                                          2000000
/* GPIO defines for channel 0 */
#define GPIO_TIMG0_PWM_C0_PORT                                             GPIOA
#define GPIO_TIMG0_PWM_C0_PIN                                     DL_GPIO_PIN_12
#define GPIO_TIMG0_PWM_C0_IOMUX                                  (IOMUX_PINCM34)
#define GPIO_TIMG0_PWM_C0_IOMUX_FUNC                 IOMUX_PINCM34_PF_TIMG0_CCP0
#define GPIO_TIMG0_PWM_C0_IDX                                DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_TIMG0_PWM_C1_PORT                                             GPIOA
#define GPIO_TIMG0_PWM_C1_PIN                                     DL_GPIO_PIN_13
#define GPIO_TIMG0_PWM_C1_IOMUX                                  (IOMUX_PINCM35)
#define GPIO_TIMG0_PWM_C1_IOMUX_FUNC                 IOMUX_PINCM35_PF_TIMG0_CCP1
#define GPIO_TIMG0_PWM_C1_IDX                                DL_TIMER_CC_1_INDEX



/* Defines for TIMA1_IT */
#define TIMA1_IT_INST                                                    (TIMA1)
#define TIMA1_IT_INST_IRQHandler                                TIMA1_IRQHandler
#define TIMA1_IT_INST_INT_IRQN                                  (TIMA1_INT_IRQn)
#define TIMA1_IT_INST_LOAD_VALUE                                        (31999U)
/* Defines for TIMA0_IT */
#define TIMA0_IT_INST                                                    (TIMA0)
#define TIMA0_IT_INST_IRQHandler                                TIMA0_IRQHandler
#define TIMA0_IT_INST_INT_IRQN                                  (TIMA0_INT_IRQn)
#define TIMA0_IT_INST_LOAD_VALUE                                        (31999U)
/* Defines for TIMG6_IT */
#define TIMG6_IT_INST                                                    (TIMG6)
#define TIMG6_IT_INST_IRQHandler                                TIMG6_IRQHandler
#define TIMG6_IT_INST_INT_IRQN                                  (TIMG6_INT_IRQn)
#define TIMG6_IT_INST_LOAD_VALUE                                        (19999U)




/* Defines for I2C_0 */
#define I2C_0_INST                                                          I2C1
#define I2C_0_INST_IRQHandler                                    I2C1_IRQHandler
#define I2C_0_INST_INT_IRQN                                        I2C1_INT_IRQn
#define I2C_0_BUS_SPEED_HZ                                                100000
#define GPIO_I2C_0_SDA_PORT                                                GPIOA
#define GPIO_I2C_0_SDA_PIN                                        DL_GPIO_PIN_30
#define GPIO_I2C_0_IOMUX_SDA                                      (IOMUX_PINCM5)
#define GPIO_I2C_0_IOMUX_SDA_FUNC                       IOMUX_PINCM5_PF_I2C1_SDA
#define GPIO_I2C_0_SCL_PORT                                                GPIOA
#define GPIO_I2C_0_SCL_PIN                                        DL_GPIO_PIN_17
#define GPIO_I2C_0_IOMUX_SCL                                     (IOMUX_PINCM39)
#define GPIO_I2C_0_IOMUX_SCL_FUNC                      IOMUX_PINCM39_PF_I2C1_SCL


/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_FREQUENCY                                            4000000
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_4_MHZ_115200_BAUD                                        (2)
#define UART_0_FBRD_4_MHZ_115200_BAUD                                       (11)
/* Defines for UART_1 */
#define UART_1_INST                                                        UART1
#define UART_1_INST_FREQUENCY                                            4000000
#define UART_1_INST_IRQHandler                                  UART1_IRQHandler
#define UART_1_INST_INT_IRQN                                      UART1_INT_IRQn
#define GPIO_UART_1_RX_PORT                                                GPIOB
#define GPIO_UART_1_TX_PORT                                                GPIOB
#define GPIO_UART_1_RX_PIN                                         DL_GPIO_PIN_5
#define GPIO_UART_1_TX_PIN                                         DL_GPIO_PIN_4
#define GPIO_UART_1_IOMUX_RX                                     (IOMUX_PINCM18)
#define GPIO_UART_1_IOMUX_TX                                     (IOMUX_PINCM17)
#define GPIO_UART_1_IOMUX_RX_FUNC                      IOMUX_PINCM18_PF_UART1_RX
#define GPIO_UART_1_IOMUX_TX_FUNC                      IOMUX_PINCM17_PF_UART1_TX
#define UART_1_BAUD_RATE                                                  (9600)
#define UART_1_IBRD_4_MHZ_9600_BAUD                                         (26)
#define UART_1_FBRD_4_MHZ_9600_BAUD                                          (3)
/* Defines for UART_3 */
#define UART_3_INST                                                        UART3
#define UART_3_INST_FREQUENCY                                            4000000
#define UART_3_INST_IRQHandler                                  UART3_IRQHandler
#define UART_3_INST_INT_IRQN                                      UART3_INT_IRQn
#define GPIO_UART_3_RX_PORT                                                GPIOA
#define GPIO_UART_3_TX_PORT                                                GPIOA
#define GPIO_UART_3_RX_PIN                                        DL_GPIO_PIN_25
#define GPIO_UART_3_TX_PIN                                        DL_GPIO_PIN_26
#define GPIO_UART_3_IOMUX_RX                                     (IOMUX_PINCM55)
#define GPIO_UART_3_IOMUX_TX                                     (IOMUX_PINCM59)
#define GPIO_UART_3_IOMUX_RX_FUNC                      IOMUX_PINCM55_PF_UART3_RX
#define GPIO_UART_3_IOMUX_TX_FUNC                      IOMUX_PINCM59_PF_UART3_TX
#define UART_3_BAUD_RATE                                                  (9600)
#define UART_3_IBRD_4_MHZ_9600_BAUD                                         (26)
#define UART_3_FBRD_4_MHZ_9600_BAUD                                          (3)
/* Defines for UART_2 */
#define UART_2_INST                                                        UART2
#define UART_2_INST_FREQUENCY                                           32000000
#define UART_2_INST_IRQHandler                                  UART2_IRQHandler
#define UART_2_INST_INT_IRQN                                      UART2_INT_IRQn
#define GPIO_UART_2_RX_PORT                                                GPIOB
#define GPIO_UART_2_TX_PORT                                                GPIOB
#define GPIO_UART_2_RX_PIN                                        DL_GPIO_PIN_16
#define GPIO_UART_2_TX_PIN                                        DL_GPIO_PIN_15
#define GPIO_UART_2_IOMUX_RX                                     (IOMUX_PINCM33)
#define GPIO_UART_2_IOMUX_TX                                     (IOMUX_PINCM32)
#define GPIO_UART_2_IOMUX_RX_FUNC                      IOMUX_PINCM33_PF_UART2_RX
#define GPIO_UART_2_IOMUX_TX_FUNC                      IOMUX_PINCM32_PF_UART2_TX
#define UART_2_BAUD_RATE                                                  (9600)
#define UART_2_IBRD_32_MHZ_9600_BAUD                                       (208)
#define UART_2_FBRD_32_MHZ_9600_BAUD                                        (21)





/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOB)

/* Defines for PIN_22: GPIOB.22 with pinCMx 50 on package pin 21 */
#define LED_PIN_22_PIN                                          (DL_GPIO_PIN_22)
#define LED_PIN_22_IOMUX                                         (IOMUX_PINCM50)
/* Port definition for Pin Group Buzzer */
#define Buzzer_PORT                                                      (GPIOB)

/* Defines for PIN_7: GPIOB.7 with pinCMx 24 on package pin 59 */
#define Buzzer_PIN_7_PIN                                         (DL_GPIO_PIN_7)
#define Buzzer_PIN_7_IOMUX                                       (IOMUX_PINCM24)
/* Port definition for Pin Group Laser */
#define Laser_PORT                                                       (GPIOB)

/* Defines for PIN_9: GPIOB.9 with pinCMx 26 on package pin 61 */
#define Laser_PIN_9_PIN                                          (DL_GPIO_PIN_9)
#define Laser_PIN_9_IOMUX                                        (IOMUX_PINCM26)
/* Port definition for Pin Group Step_Motor */
#define Step_Motor_PORT                                                  (GPIOA)

/* Defines for Step_Motor_X_EN: GPIOA.16 with pinCMx 38 on package pin 9 */
#define Step_Motor_Step_Motor_X_EN_PIN                          (DL_GPIO_PIN_16)
#define Step_Motor_Step_Motor_X_EN_IOMUX                         (IOMUX_PINCM38)
/* Defines for Step_Motor_X_DIR: GPIOA.14 with pinCMx 36 on package pin 7 */
#define Step_Motor_Step_Motor_X_DIR_PIN                         (DL_GPIO_PIN_14)
#define Step_Motor_Step_Motor_X_DIR_IOMUX                        (IOMUX_PINCM36)
/* Defines for Step_Motor_Y_EN: GPIOA.22 with pinCMx 47 on package pin 18 */
#define Step_Motor_Step_Motor_Y_EN_PIN                          (DL_GPIO_PIN_22)
#define Step_Motor_Step_Motor_Y_EN_IOMUX                         (IOMUX_PINCM47)
/* Defines for Step_Motor_Y_DIR: GPIOA.24 with pinCMx 54 on package pin 25 */
#define Step_Motor_Step_Motor_Y_DIR_PIN                         (DL_GPIO_PIN_24)
#define Step_Motor_Step_Motor_Y_DIR_IOMUX                        (IOMUX_PINCM54)
/* Port definition for Pin Group Encoder */
#define Encoder_PORT                                                     (GPIOA)

/* Defines for E1_A: GPIOA.8 with pinCMx 19 on package pin 54 */
// pins affected by this interrupt request:["E1_A","E1_B","E2_A","E2_B"]
#define Encoder_INT_IRQN                                        (GPIOA_INT_IRQn)
#define Encoder_INT_IIDX                        (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define Encoder_E1_A_IIDX                                    (DL_GPIO_IIDX_DIO8)
#define Encoder_E1_A_PIN                                         (DL_GPIO_PIN_8)
#define Encoder_E1_A_IOMUX                                       (IOMUX_PINCM19)
/* Defines for E1_B: GPIOA.9 with pinCMx 20 on package pin 55 */
#define Encoder_E1_B_IIDX                                    (DL_GPIO_IIDX_DIO9)
#define Encoder_E1_B_PIN                                         (DL_GPIO_PIN_9)
#define Encoder_E1_B_IOMUX                                       (IOMUX_PINCM20)
/* Defines for E2_A: GPIOA.28 with pinCMx 3 on package pin 35 */
#define Encoder_E2_A_IIDX                                   (DL_GPIO_IIDX_DIO28)
#define Encoder_E2_A_PIN                                        (DL_GPIO_PIN_28)
#define Encoder_E2_A_IOMUX                                        (IOMUX_PINCM3)
/* Defines for E2_B: GPIOA.0 with pinCMx 1 on package pin 33 */
#define Encoder_E2_B_IIDX                                    (DL_GPIO_IIDX_DIO0)
#define Encoder_E2_B_PIN                                         (DL_GPIO_PIN_0)
#define Encoder_E2_B_IOMUX                                        (IOMUX_PINCM1)
/* Port definition for Pin Group TB6612 */
#define TB6612_PORT                                                      (GPIOB)

/* Defines for AIN1: GPIOB.8 with pinCMx 25 on package pin 60 */
#define TB6612_AIN1_PIN                                          (DL_GPIO_PIN_8)
#define TB6612_AIN1_IOMUX                                        (IOMUX_PINCM25)
/* Defines for AIN2: GPIOB.6 with pinCMx 23 on package pin 58 */
#define TB6612_AIN2_PIN                                          (DL_GPIO_PIN_6)
#define TB6612_AIN2_IOMUX                                        (IOMUX_PINCM23)
/* Defines for BIN1: GPIOB.23 with pinCMx 51 on package pin 22 */
#define TB6612_BIN1_PIN                                         (DL_GPIO_PIN_23)
#define TB6612_BIN1_IOMUX                                        (IOMUX_PINCM51)
/* Defines for BIN2: GPIOB.27 with pinCMx 58 on package pin 29 */
#define TB6612_BIN2_PIN                                         (DL_GPIO_PIN_27)
#define TB6612_BIN2_IOMUX                                        (IOMUX_PINCM58)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_TIMG12_PWM_init(void);
void SYSCFG_DL_TIMG0_PWM_init(void);
void SYSCFG_DL_TIMA1_IT_init(void);
void SYSCFG_DL_TIMA0_IT_init(void);
void SYSCFG_DL_TIMG6_IT_init(void);
void SYSCFG_DL_I2C_0_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_UART_1_init(void);
void SYSCFG_DL_UART_3_init(void);
void SYSCFG_DL_UART_2_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
