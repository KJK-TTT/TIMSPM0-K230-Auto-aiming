#ifndef __MISC_BSP_H__
#define __MISC_BSP_H__

#include "board.h"

void buzzer_on(void);
void buzzer_off(void);
void buzzer(uint8_t is_buzzer_on);

void laser_off(void);
void laser_on(void);
void led_flash(void);

#endif
