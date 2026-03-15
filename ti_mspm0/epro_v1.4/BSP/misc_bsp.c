#include "misc_bsp.h"

// void buzzer_on(uint16_t time)
// {
// 	DL_GPIO_writePins(Buzzer_PORT, Buzzer_PIN_7_PIN);
// 	delay_ms(time);
// 	DL_GPIO_clearPins(Buzzer_PORT, Buzzer_PIN_7_PIN);
// }

void buzzer_on(void)
{
	DL_GPIO_writePins(Buzzer_PORT, Buzzer_PIN_7_PIN);
}

void buzzer_off(void)
{
	DL_GPIO_clearPins(Buzzer_PORT, Buzzer_PIN_7_PIN);
}

void buzzer(uint8_t is_buzzer_on)
{
	if (is_buzzer_on)
	{
		DL_GPIO_writePins(Buzzer_PORT, Buzzer_PIN_7_PIN);
	}
	else
	{
		DL_GPIO_clearPins(Buzzer_PORT, Buzzer_PIN_7_PIN);
	}
}

void laser_on(void)
{
	DL_GPIO_writePins(Laser_PORT, Laser_PIN_9_PIN);
}

void laser_off(void)
{
	DL_GPIO_clearPins(Laser_PORT, Laser_PIN_9_PIN);
}

void led_flash(void)
{
	DL_GPIO_clearPins(LED_PORT, LED_PIN_22_PIN); // led off
	delay_ms(500);
	DL_GPIO_setPins(LED_PORT, LED_PIN_22_PIN); // LED on
	delay_ms(500);
}
