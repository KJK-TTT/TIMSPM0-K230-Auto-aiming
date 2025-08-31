#include "servo.h"

double pulse_1;
double pulse_2;

void angle_to_pulse(double angle_1, double angle_2)
{
    pulse_1 = ((angle_1) * (2000.0 / 270.0) + 500.0) / 20.0;
    pulse_2 = ((angle_2) * (2000.0 / 180.0) + 500.0) / 20.0;
}

void set_angle(double angle_1, double angle_2)
{
    // 限制角度范围
    if (angle_1 < 0) angle_1 = 0;
    if (angle_1 > 270) angle_1 = 270;
    if (angle_2 < 0) angle_2 = 0;
    if (angle_2 > 180) angle_2 = 180;

    angle_to_pulse(angle_1, angle_2);

    // 设置 PWM 占空比 GPIO_TIMG8_PWM_C0_IDX
    DL_TimerG_setCaptureCompareValue(TIMG8_PWM_INST, (uint32_t)pulse_1, GPIO_TIMG8_PWM_C0_IDX); // servo 
    DL_TimerG_setCaptureCompareValue(TIMG8_PWM_INST, (uint32_t)pulse_2, GPIO_TIMG8_PWM_C1_IDX); // servo 
}


// test
// set_angle(0,90);
//  delay_ms(500);
// set_angle(90,90);
// delay_ms(500);
// set_angle(180,90);
// delay_ms(500);
// set_angle(90,90);
// delay_ms(500);

// set_angle(90,0);
// delay_ms(500);
// set_angle(90,90);
// delay_ms(500);
// set_angle(90,180);
// delay_ms(500);
// set_angle(90,90);
// delay_ms(500);