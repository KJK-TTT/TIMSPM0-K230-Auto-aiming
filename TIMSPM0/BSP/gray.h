#ifndef   __GRAY_H_
#define   __GRAY_H_

#include "board.h"

// 灰度传感器数值结构体
typedef struct {
    uint32_t left3;    
    uint32_t left2;    
    uint32_t left1;  
    uint32_t middle;    
    uint32_t right1;   
    uint32_t right2;   
	uint32_t right3;
} Gray_TypeDef;

void gray_read(Gray_TypeDef *gray);
float calculate_tracking_error(Gray_TypeDef* gray);

bool is_turn(Gray_TypeDef *gray);

#endif  /* __GRAY_H_ */
