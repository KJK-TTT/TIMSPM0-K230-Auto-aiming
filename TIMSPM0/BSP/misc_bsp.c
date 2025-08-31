#include "misc_bsp.h"

uint8_t key_read(void)
{
    uint8_t key_value = 0;

    if (DL_GPIO_readPins(SW_PORT, SW_S1_PIN) == 0) key_value |= 0x01;  // bit0
    if (DL_GPIO_readPins(SW_PORT, SW_S2_PIN) == 0) key_value |= 0x02;  // bit1
    if (DL_GPIO_readPins(SW_PORT, SW_S3_PIN) == 0) key_value |= 0x04;  // bit2

    return key_value;
}

void buzzer_on(uint16_t time)
{
    DL_GPIO_writePins(BUZZER_PORT,  BUZZER_PIN_PIN);
	delay_ms(time);
    DL_GPIO_clearPins(BUZZER_PORT, BUZZER_PIN_PIN);
}


void laser_on(void)
{
   DL_GPIO_writePins(UV_PORT, UV_PIN_0_PIN);
}

void laser_off(void)
{
    DL_GPIO_clearPins(UV_PORT, UV_PIN_0_PIN);
}


