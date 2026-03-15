#include "com_k230.h"

// UART 接收缓冲区
volatile uint8_t u0_rx_ok_flag = 0;
char u0_rx_data = 0;

// 用于存储坐标值
int16_t dx_center_signed = 0;
int16_t dy_center_signed = 0;
uint8_t target_detected = 0;

/**
 * @brief 格式化坐标数据
 *
 * @param coord 坐标值
 * @return 格式化后的字符串
 */
char *format_coord(int coord)
{
    static char coord_str[6];                               // 用于存储格式化后的坐标，4个字符 + 终止符
    snprintf(coord_str, sizeof(coord_str), "%+04d", coord); // 格式化为 +123 或 -123 等
    return coord_str;
}

/**
 * @brief 快速 ASCII 坐标转 int
 * @param str 字符串指针，长度 4，格式 [+/-][0-9][0-9][0-9]
 * @return 转换后的 int 值
 */
static int16_t ascii4_to_int(const char *str)
{
    int sign = (str[0] == '-') ? -1 : 1;
    int val = (str[1] - '0') * 100 + (str[2] - '0') * 10 + (str[3] - '0');
    return sign * val;
}

/**
 * @brief 解析K230发来的数据包
 * 数据包格式: [+123-045*]
 */
void k230_pack_data(uint8_t com_data)
{
    static uint8_t rx_state = 0;   // 当前接收状态
    static uint8_t temp_buff[10];  // 临时缓存
    static uint8_t data_index = 0; // 缓存索引

    switch (rx_state)
    {
    case 0: // 等待起始符 '['
        if (com_data == '[')
        {
            rx_state = 1;
            data_index = 0;
        }
        break;

    case 1: // 接收坐标数据
        temp_buff[data_index++] = com_data;

        // 预期长度: x4 + y4 + '*' = 9
        if (data_index == 9)
        {
            if (temp_buff[8] == '*') // 检查结束符
            {
                // 解析 x 坐标
                dx_center_signed = ascii4_to_int((char *)&temp_buff[0]);
                // 解析 y 坐标
                dy_center_signed = ascii4_to_int((char *)&temp_buff[4]);

                // 标记解析完成
                u0_rx_ok_flag = 1;

                if (dx_center_signed == 999 && dy_center_signed == 999)
                {
                    target_detected = 0;
                }
                else
                {
                    target_detected = 1;
                }
                // test
                // ek_printf("K230: x=%d, y=%d ,target=%d\n", dx_center_signed, dy_center_signed, target_detected);
            }
            // 无论成功与否，重置状态等待下一个数据包
            rx_state = 0;
        }
        break;

    default:
        rx_state = 0;
        break;
    }
}

/**
 * @brief UART0 中断接收函数，处理K230数据包
 */
void UART0_IRQHandler(void)
{
    if (DL_UART_getPendingInterrupt(UART_0_INST))
    {
        u0_rx_data = DL_UART_Main_receiveData(UART_0_INST);
        DL_UART_clearInterruptStatus(UART_0_INST, DL_UART_INTERRUPT_RX);
        k230_pack_data(u0_rx_data);
    }
}
