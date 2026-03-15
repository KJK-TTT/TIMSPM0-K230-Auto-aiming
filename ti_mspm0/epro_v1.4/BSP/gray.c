#include "gray.h"

uint8_t Digtal; // 8路灰度循迹传感器的数字信号

#define LOST_LINE_MAX_COUNT 5 // 连续丢线最大允许帧数

static float last_error = 0;        // 上一次误差
static uint8_t lost_line_count = 0; // 连续丢线计数

/**
 * @brief 读取灰度传感器（0=黑，1=白）
 */
void gray_read(Gray_TypeDef *gray)
{
    Digtal = IIC_Get_Digtal(); // 采集8路灰度循迹传感器
	
	// 取出每一位
    gray->left4 = (Digtal >> 0) & 0x01;
    gray->left3 = (Digtal >> 1) & 0x01;
    gray->left2 = (Digtal >> 2) & 0x01;
    gray->left1 = (Digtal >> 3) & 0x01;
    gray->right1 = (Digtal >> 4) & 0x01;
    gray->right2 = (Digtal >> 5) & 0x01;
    gray->right3 = (Digtal >> 6) & 0x01;
    gray->right4 = (Digtal >> 7) & 0x01;
	
	// test
    // ek_printf("Digital %d-%d-%d-%d-%d-%d-%d-%d\r\n",
    //           gray->left4,
    //           gray->left3,
    //           gray->left2,
    //           gray->left1,
    //           gray->right1,
    //           gray->right2,
    //           gray->right3,
    //           gray->right4);
}

/**
 * @brief 计算循线时的误差
 */
float calculate_tracking_error(Gray_TypeDef *gray)
{
    // 黑线数量（值=0）
    uint8_t black_count =
        (gray->left4 == 0) + (gray->left3 == 0) +
        (gray->left2 == 0) + (gray->left1 == 0) +
        (gray->right1 == 0) + (gray->right2 == 0) +
        (gray->right3 == 0) + (gray->right4 == 0);

    // 完全丢线
    if (black_count == 0)
    {
        lost_line_count++;

        // 连续 5 次都丢线：强制置 0 停止
        if (lost_line_count > LOST_LINE_MAX_COUNT)
        {
            last_error = 0;
        }
        return last_error;
    }
    lost_line_count = 0;

    // 加权平均误差
    float error_sum = 0; // 加权和
    if (gray->left4 == 0)
        error_sum += -4;
    if (gray->left3 == 0)
        error_sum += -3;
    if (gray->left2 == 0)
        error_sum += -2;
    if (gray->left1 == 0)
        error_sum += -1;
    if (gray->right1 == 0)
        error_sum += +1;
    if (gray->right2 == 0)
        error_sum += +2;
    if (gray->right3 == 0)
        error_sum += +3;
    if (gray->right4 == 0)
        error_sum += +4;

    float error = error_sum / black_count;
    last_error = error;
    return error;
}
