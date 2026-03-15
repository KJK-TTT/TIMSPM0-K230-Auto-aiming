#ifndef __BOARD_H__
#define __BOARD_H__

#include "ti_msp_dl_config.h"
#include "ti/driverlib/m0p/dl_core.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <stdint.h>

#ifndef u8
#define u8 uint8_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u32
#define u32 uint32_t
#endif

#ifndef u64
#define u64 uint64_t
#endif

/* 使用可变参数是实现的类printf函数 */
int lc_printf(char *format, ...);
int ek_printf(char *format, ...);
int lcd_printf(char *format, ...);

/* 延时函数 */
void delay_us(int __us);
// void delay_ms(int __ms);
void delay_ms(unsigned int ms);

void delay_1us(int __us);
void delay_1ms(int __ms);

#endif
