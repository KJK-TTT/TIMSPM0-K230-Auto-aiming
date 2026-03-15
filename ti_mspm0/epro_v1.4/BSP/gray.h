#ifndef __GRAY_H_
#define __GRAY_H_

#include "board.h"
#include "hardware_iic.h"
#include "IIC.h"

// 灰度传感器数值结构体
typedef struct
{
	uint8_t left4;
	uint8_t left3;
    uint8_t left2;
    uint8_t left1;
    uint8_t right1;
    uint8_t right2;
	uint8_t right3;
	uint8_t right4;
} Gray_TypeDef;

void gray_read(Gray_TypeDef *gray);
float calculate_tracking_error(Gray_TypeDef *gray);

#endif /* __GRAY_H_ */
