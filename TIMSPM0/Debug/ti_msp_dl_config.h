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



#define CPUCLK_FREQ                                                     80000000



/* Defines for TIMG0_PWM */
#define TIMG0_PWM_INST                                                     TIMG0
#define TIMG0_PWM_INST_IRQHandler                               TIMG0_IRQHandler
#define TIMG0_PWM_INST_INT_IRQN                                 (TIMG0_INT_IRQn)
#define TIMG0_PWM_INST_CLK_FREQ                                          2500000
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

/* Defines for TIMG8_PWM */
#define TIMG8_PWM_INST                                                     TIMG8
#define TIMG8_PWM_INST_IRQHandler                               TIMG8_IRQHandler
#define TIMG8_PWM_INST_INT_IRQN                                 (TIMG8_INT_IRQn)
#define TIMG8_PWM_INST_CLK_FREQ                                            50000
/* GPIO defines for channel 0 */
#define GPIO_TIMG8_PWM_C0_PORT                                             GPIOA
#define GPIO_TIMG8_PWM_C0_PIN                                      DL_GPIO_PIN_7
#define GPIO_TIMG8_PWM_C0_IOMUX                                  (IOMUX_PINCM14)
#define GPIO_TIMG8_PWM_C0_IOMUX_FUNC                 IOMUX_PINCM14_PF_TIMG8_CCP0
#define GPIO_TIMG8_PWM_C0_IDX                                DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_TIMG8_PWM_C1_PORT                                             GPIOA
#define GPIO_TIMG8_PWM_C1_PIN                                     DL_GPIO_PIN_27
#define GPIO_TIMG8_PWM_C1_IOMUX                                  (IOMUX_PINCM60)
#define GPIO_TIMG8_PWM_C1_IOMUX_FUNC                 IOMUX_PINCM60_PF_TIMG8_CCP1
#define GPIO_TIMG8_PWM_C1_IDX                                DL_TIMER_CC_1_INDEX



/* Defines for TIMA0_IC */
#define TIMA0_IC_INST                                                    (TIMA0)
#define TIMA0_IC_INST_IRQHandler                                TIMA0_IRQHandler
#define TIMA0_IC_INST_INT_IRQN                                  (TIMA0_INT_IRQn)
#define TIMA0_IC_INST_LOAD_VALUE                                        (24999U)
/* Defines for TIMA1_IT */
#define TIMA1_IT_INST                                                    (TIMA1)
#define TIMA1_IT_INST_IRQHandler                                TIMA1_IRQHandler
#define TIMA1_IT_INST_INT_IRQN                                  (TIMA1_INT_IRQn)
#define TIMA1_IT_INST_LOAD_VALUE                                         (1249U)



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
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_4_MHZ_9600_BAUD                                         (26)
#define UART_0_FBRD_4_MHZ_9600_BAUD                                          (3)
/* Defines for UART_1 */
#define UART_1_INST                                                        UART1
#define UART_1_INST_FREQUENCY                                            4000000
#define UART_1_INST_IRQHandler                                  UART1_IRQHandler
#define UART_1_INST_INT_IRQN                                      UART1_INT_IRQn
#define GPIO_UART_1_TX_PORT                                                GPIOA
#define GPIO_UART_1_TX_PIN                                        DL_GPIO_PIN_17
#define GPIO_UART_1_IOMUX_TX                                     (IOMUX_PINCM39)
#define GPIO_UART_1_IOMUX_TX_FUNC                      IOMUX_PINCM39_PF_UART1_TX
#define UART_1_BAUD_RATE                                                  (9600)
#define UART_1_IBRD_4_MHZ_9600_BAUD                                         (26)
#define UART_1_FBRD_4_MHZ_9600_BAUD                                          (3)
/* Defines for UART_2 */
#define UART_2_INST                                                        UART2
#define UART_2_INST_FREQUENCY                                            4000000
#define UART_2_INST_IRQHandler                                  UART2_IRQHandler
#define UART_2_INST_INT_IRQN                                      UART2_INT_IRQn
#define GPIO_UART_2_RX_PORT                                                GPIOA
#define GPIO_UART_2_RX_PIN                                        DL_GPIO_PIN_22
#define GPIO_UART_2_IOMUX_RX                                     (IOMUX_PINCM47)
#define GPIO_UART_2_IOMUX_RX_FUNC                      IOMUX_PINCM47_PF_UART2_RX
#define UART_2_BAUD_RATE                                                  (9600)
#define UART_2_IBRD_4_MHZ_9600_BAUD                                         (26)
#define UART_2_FBRD_4_MHZ_9600_BAUD                                          (3)




/* Defines for SPI_OLED */
#define SPI_OLED_INST                                                      SPI1
#define SPI_OLED_INST_IRQHandler                                SPI1_IRQHandler
#define SPI_OLED_INST_INT_IRQN                                    SPI1_INT_IRQn
#define GPIO_SPI_OLED_PICO_PORT                                           GPIOB
#define GPIO_SPI_OLED_PICO_PIN                                    DL_GPIO_PIN_8
#define GPIO_SPI_OLED_IOMUX_PICO                                (IOMUX_PINCM25)
#define GPIO_SPI_OLED_IOMUX_PICO_FUNC                IOMUX_PINCM25_PF_SPI1_PICO
#define GPIO_SPI_OLED_POCI_PORT                                           GPIOB
#define GPIO_SPI_OLED_POCI_PIN                                    DL_GPIO_PIN_7
#define GPIO_SPI_OLED_IOMUX_POCI                                (IOMUX_PINCM24)
#define GPIO_SPI_OLED_IOMUX_POCI_FUNC                IOMUX_PINCM24_PF_SPI1_POCI
/* GPIO configuration for SPI_OLED */
#define GPIO_SPI_OLED_SCLK_PORT                                           GPIOB
#define GPIO_SPI_OLED_SCLK_PIN                                    DL_GPIO_PIN_9
#define GPIO_SPI_OLED_IOMUX_SCLK                                (IOMUX_PINCM26)
#define GPIO_SPI_OLED_IOMUX_SCLK_FUNC                IOMUX_PINCM26_PF_SPI1_SCLK



/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOB)

/* Defines for PIN_22: GPIOB.22 with pinCMx 50 on package pin 21 */
#define LED_PIN_22_PIN                                          (DL_GPIO_PIN_22)
#define LED_PIN_22_IOMUX                                         (IOMUX_PINCM50)
/* Port definition for Pin Group BUZZER */
#define BUZZER_PORT                                                      (GPIOA)

/* Defines for PIN: GPIOA.15 with pinCMx 37 on package pin 8 */
#define BUZZER_PIN_PIN                                          (DL_GPIO_PIN_15)
#define BUZZER_PIN_IOMUX                                         (IOMUX_PINCM37)
/* Port definition for Pin Group UV */
#define UV_PORT                                                          (GPIOA)

/* Defines for PIN_0: GPIOA.0 with pinCMx 1 on package pin 33 */
#define UV_PIN_0_PIN                                             (DL_GPIO_PIN_0)
#define UV_PIN_0_IOMUX                                            (IOMUX_PINCM1)
/* Port definition for Pin Group OLED */
#define OLED_PORT                                                        (GPIOB)

/* Defines for RES: GPIOB.10 with pinCMx 27 on package pin 62 */
#define OLED_RES_PIN                                            (DL_GPIO_PIN_10)
#define OLED_RES_IOMUX                                           (IOMUX_PINCM27)
/* Defines for DC: GPIOB.11 with pinCMx 28 on package pin 63 */
#define OLED_DC_PIN                                             (DL_GPIO_PIN_11)
#define OLED_DC_IOMUX                                            (IOMUX_PINCM28)
/* Defines for CS: GPIOB.14 with pinCMx 31 on package pin 2 */
#define OLED_CS_PIN                                             (DL_GPIO_PIN_14)
#define OLED_CS_IOMUX                                            (IOMUX_PINCM31)
/* Port definition for Pin Group SW */
#define SW_PORT                                                          (GPIOB)

/* Defines for S1: GPIOB.25 with pinCMx 56 on package pin 27 */
#define SW_S1_PIN                                               (DL_GPIO_PIN_25)
#define SW_S1_IOMUX                                              (IOMUX_PINCM56)
/* Defines for S2: GPIOB.18 with pinCMx 44 on package pin 15 */
#define SW_S2_PIN                                               (DL_GPIO_PIN_18)
#define SW_S2_IOMUX                                              (IOMUX_PINCM44)
/* Defines for S3: GPIOB.13 with pinCMx 30 on package pin 1 */
#define SW_S3_PIN                                               (DL_GPIO_PIN_13)
#define SW_S3_IOMUX                                              (IOMUX_PINCM30)
/* Port definition for Pin Group TB6612_1 */
#define TB6612_1_PORT                                                    (GPIOB)

/* Defines for TB1_AIN2: GPIOB.15 with pinCMx 32 on package pin 3 */
#define TB6612_1_TB1_AIN2_PIN                                   (DL_GPIO_PIN_15)
#define TB6612_1_TB1_AIN2_IOMUX                                  (IOMUX_PINCM32)
/* Defines for TB1_AIN1: GPIOB.16 with pinCMx 33 on package pin 4 */
#define TB6612_1_TB1_AIN1_PIN                                   (DL_GPIO_PIN_16)
#define TB6612_1_TB1_AIN1_IOMUX                                  (IOMUX_PINCM33)
/* Defines for TB1_BIN1: GPIOB.2 with pinCMx 15 on package pin 50 */
#define TB6612_1_TB1_BIN1_PIN                                    (DL_GPIO_PIN_2)
#define TB6612_1_TB1_BIN1_IOMUX                                  (IOMUX_PINCM15)
/* Defines for TB1_BIN2: GPIOB.3 with pinCMx 16 on package pin 51 */
#define TB6612_1_TB1_BIN2_PIN                                    (DL_GPIO_PIN_3)
#define TB6612_1_TB1_BIN2_IOMUX                                  (IOMUX_PINCM16)
/* Port definition for Pin Group Encoder1 */
#define Encoder1_PORT                                                    (GPIOB)

/* Defines for E1_A: GPIOB.4 with pinCMx 17 on package pin 52 */
// pins affected by this interrupt request:["E1_A","E1_B"]
#define Encoder1_INT_IRQN                                       (GPIOB_INT_IRQn)
#define Encoder1_INT_IIDX                       (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define Encoder1_E1_A_IIDX                                   (DL_GPIO_IIDX_DIO4)
#define Encoder1_E1_A_PIN                                        (DL_GPIO_PIN_4)
#define Encoder1_E1_A_IOMUX                                      (IOMUX_PINCM17)
/* Defines for E1_B: GPIOB.5 with pinCMx 18 on package pin 53 */
#define Encoder1_E1_B_IIDX                                   (DL_GPIO_IIDX_DIO5)
#define Encoder1_E1_B_PIN                                        (DL_GPIO_PIN_5)
#define Encoder1_E1_B_IOMUX                                      (IOMUX_PINCM18)
/* Port definition for Pin Group Encoder2 */
#define Encoder2_PORT                                                    (GPIOA)

/* Defines for E2_A: GPIOA.8 with pinCMx 19 on package pin 54 */
// pins affected by this interrupt request:["E2_A","E2_B"]
#define Encoder2_INT_IRQN                                       (GPIOA_INT_IRQn)
#define Encoder2_INT_IIDX                       (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define Encoder2_E2_A_IIDX                                   (DL_GPIO_IIDX_DIO8)
#define Encoder2_E2_A_PIN                                        (DL_GPIO_PIN_8)
#define Encoder2_E2_A_IOMUX                                      (IOMUX_PINCM19)
/* Defines for E2_B: GPIOA.9 with pinCMx 20 on package pin 55 */
#define Encoder2_E2_B_IIDX                                   (DL_GPIO_IIDX_DIO9)
#define Encoder2_E2_B_PIN                                        (DL_GPIO_PIN_9)
#define Encoder2_E2_B_IOMUX                                      (IOMUX_PINCM20)
/* Port definition for Pin Group GRAY */
#define GRAY_PORT                                                        (GPIOA)

/* Defines for RIGHT2: GPIOA.28 with pinCMx 3 on package pin 35 */
#define GRAY_RIGHT2_PIN                                         (DL_GPIO_PIN_28)
#define GRAY_RIGHT2_IOMUX                                         (IOMUX_PINCM3)
/* Defines for RIGHT1: GPIOA.29 with pinCMx 4 on package pin 36 */
#define GRAY_RIGHT1_PIN                                         (DL_GPIO_PIN_29)
#define GRAY_RIGHT1_IOMUX                                         (IOMUX_PINCM4)
/* Defines for MIDDLE: GPIOA.30 with pinCMx 5 on package pin 37 */
#define GRAY_MIDDLE_PIN                                         (DL_GPIO_PIN_30)
#define GRAY_MIDDLE_IOMUX                                         (IOMUX_PINCM5)
/* Defines for LEFT1: GPIOA.16 with pinCMx 38 on package pin 9 */
#define GRAY_LEFT1_PIN                                          (DL_GPIO_PIN_16)
#define GRAY_LEFT1_IOMUX                                         (IOMUX_PINCM38)
/* Defines for LEFT2: GPIOA.14 with pinCMx 36 on package pin 7 */
#define GRAY_LEFT2_PIN                                          (DL_GPIO_PIN_14)
#define GRAY_LEFT2_IOMUX                                         (IOMUX_PINCM36)
/* Defines for RIGHT3: GPIOA.24 with pinCMx 54 on package pin 25 */
#define GRAY_RIGHT3_PIN                                         (DL_GPIO_PIN_24)
#define GRAY_RIGHT3_IOMUX                                        (IOMUX_PINCM54)
/* Defines for LEFT3: GPIOA.31 with pinCMx 6 on package pin 39 */
#define GRAY_LEFT3_PIN                                          (DL_GPIO_PIN_31)
#define GRAY_LEFT3_IOMUX                                          (IOMUX_PINCM6)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_TIMG0_PWM_init(void);
void SYSCFG_DL_TIMG8_PWM_init(void);
void SYSCFG_DL_TIMA0_IC_init(void);
void SYSCFG_DL_TIMA1_IT_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_UART_1_init(void);
void SYSCFG_DL_UART_2_init(void);
void SYSCFG_DL_SPI_OLED_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
