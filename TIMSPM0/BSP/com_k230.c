#include "com_k230.h"

// ======================= 配置区域 ========================
#define K230_FRAME_LEN 8 // 帧长

// 接收标志和数据
uint8_t u0_rx_ok_flag = 0;
char u0_rx_data = 0;

// 坐标解析结果（全局变量）
uint16_t center_x, center_y;
uint16_t lost;

// ======================= 帧解析函数 ========================
void pack_data(uint8_t com_data)
{
    static uint8_t rx_counter = 0;
    static uint8_t rx_buffer[K230_FRAME_LEN] = {0};
    static uint8_t rx_state = 0;

    switch (rx_state) {
        case 0:
            if (com_data == 0x2C) {
                rx_buffer[rx_counter++] = com_data;
                rx_state = 1;
            }
            break;

        case 1:
            if (com_data == 0x12) {
                rx_buffer[rx_counter++] = com_data;
                rx_state = 2;
            } else {
                rx_counter = 0;
                rx_state = 0;
            }
            break;

        case 2:
            rx_buffer[rx_counter++] = com_data;

            if (rx_counter >= K230_FRAME_LEN) {
                if (rx_buffer[K230_FRAME_LEN - 1] == 0x5B) { // 帧尾校验
                    center_x    = (rx_buffer[2]  << 8) | rx_buffer[3];
                    center_y    = (rx_buffer[4]  << 8) | rx_buffer[5];
                    lost        =  rx_buffer[6];

                    u0_rx_ok_flag = 1;

                //    ek_printf("center: (%d, %d), lost: %d\r\n", center_x, center_y, lost);

                }
                // 不管校验是否通过，都要重置
                rx_counter = 0;
                rx_state = 0;
            }
            break;

        default:
            rx_state = 0;
            rx_counter = 0;
            break;
    }
}

// ======================= 中断接收解析 ========================
void UART0_IRQHandler(void)
{
    if (DL_UART_getPendingInterrupt(UART_0_INST)) {
        u0_rx_data = DL_UART_Main_receiveData(UART_0_INST);
        pack_data((uint8_t)u0_rx_data);  // 每接收一个字节就处理
    }
}
