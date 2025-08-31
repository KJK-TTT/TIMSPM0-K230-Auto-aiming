#ifndef __MISC_BSP_H__
#define __MISC_BSP_H__

#include "board.h"

uint8_t key_read(void);
void buzzer_on(uint16_t time);

void laser_off(void);
void laser_on(void);


#endif
