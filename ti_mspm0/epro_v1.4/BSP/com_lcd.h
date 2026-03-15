#ifndef __COM_LCD_H__
#define __COM_LCD_H__

#include "board.h"
#include "com_k230.h"
#include "task.h"

void uart_lcd_pack_data(uint8_t com_data);
void lcd_process(void);

extern uint8_t task_index; // 任务索引
extern uint8_t is_task1_running;
extern uint8_t is_task2_running;

#endif
