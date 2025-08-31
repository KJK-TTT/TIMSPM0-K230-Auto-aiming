#include "gray.h"


void gray_read(Gray_TypeDef *gray)
{
    gray->left3  = (DL_GPIO_readPins(GRAY_PORT, GRAY_LEFT3_PIN))  ? 0 : 1;
    gray->left2  = (DL_GPIO_readPins(GRAY_PORT, GRAY_LEFT2_PIN))  ? 0 : 1;
    gray->left1  = (DL_GPIO_readPins(GRAY_PORT, GRAY_LEFT1_PIN))  ? 0 : 1;
    gray->middle = (DL_GPIO_readPins(GRAY_PORT, GRAY_MIDDLE_PIN)) ? 0 : 1;
    gray->right1 = (DL_GPIO_readPins(GRAY_PORT, GRAY_RIGHT1_PIN)) ? 0 : 1;
    gray->right2 = (DL_GPIO_readPins(GRAY_PORT, GRAY_RIGHT2_PIN)) ? 0 : 1;
    gray->right3 = (DL_GPIO_readPins(GRAY_PORT, GRAY_RIGHT3_PIN)) ? 0 : 1;
}

float calculate_tracking_error(Gray_TypeDef *gray)
{
    float error = 0.0f;
    uint8_t sensor_sum = 0;

    if (gray->left3  == 1) { error -= 3.0f; sensor_sum++; }
    if (gray->left2  == 1) { error -= 2.0f; sensor_sum++; }
    if (gray->left1  == 1) { error -= 1.0f; sensor_sum++; }
    if (gray->middle == 1) { error += 0.0f; sensor_sum++; }
    if (gray->right1 == 1) { error += 1.0f; sensor_sum++; }
    if (gray->right2 == 1) { error += 2.0f; sensor_sum++; }
    if (gray->right3 == 1) { error += 3.0f; sensor_sum++; }

    if (sensor_sum == 0)  {
        return error;
    }

    error /= sensor_sum;
    return error;
}

bool is_turn(Gray_TypeDef *gray)
{
    if ( (gray->left3  == 0 && gray->left2  == 0 && gray->left1  == 0) || \
         (gray->right3 == 0 && gray->right2 == 0 && gray->right1 == 0)) {
        
        return true;
    }
    else {
        return false;
    }
}
