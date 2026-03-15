#ifndef __COM_K230_H__
#define __COM_K230_H__

#include "board.h"

// 外部变量声明
extern volatile uint8_t u0_rx_ok_flag;
extern int16_t dx_center_signed;
extern int16_t dy_center_signed;
extern uint8_t target_detected;

// 函数声明
void k230_pack_data(uint8_t com_data);

#endif
