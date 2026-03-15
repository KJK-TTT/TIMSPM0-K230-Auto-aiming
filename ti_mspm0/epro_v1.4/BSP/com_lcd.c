#include "com_lcd.h"

#define UART_LCD_FRAME_LEN 7
volatile uint8_t u3_rx_ok_flag = 0;
char u3_rx_data = 0;
uint8_t lcd_cmd = 0; // 保存从LCD接收到的有效数据

/**
 * @brief 解析串口屏发来的数据包
 * 数据包格式: 0X55 com_data 0xFF 0x04 0xFF 0xFF 0xFF
 */
void uart_lcd_pack_data(uint8_t com_data)
{
    static uint8_t rx_counter = 0;
    static uint8_t rx_buffer[UART_LCD_FRAME_LEN] = {0};
    static uint8_t rx_state = 0;

    switch (rx_state)
    {
    case 0: // 等待帧头 0x55
        if (com_data == 0x55)
        {
            rx_buffer[0] = com_data;
            rx_counter = 1;
            rx_state = 1;
        }
        break;

    case 1: // 接收后续字节
        rx_buffer[rx_counter++] = com_data;

        // 判断是否接收满一帧
        if (rx_counter >= UART_LCD_FRAME_LEN)
        {
            rx_state = 0; // 回到初始状态
            rx_counter = 0;
            u3_rx_ok_flag = 1; // 标记接收完成

            // 提取第二字节为有效数据
            lcd_cmd = rx_buffer[1];

            // test
            // ek_printf("LCD cmd = 0x%02X\r\n", lcd_cmd);
        }
        break;

    default:
        rx_state = 0;
        rx_counter = 0;
        break;
    }
}

uint8_t is_task1_running;
uint8_t is_task2_running;
uint8_t is_reset;

uint8_t task_index = 1; // 任务索引

/**
 * @brief 收到LCD命令执行的操作
 */
static void lcd_send_cmd(void)
{
    switch (lcd_cmd)
    {
    case 0x00: // 复位
        lcd_cmd = 0xFF;
        is_reset = 1;
        is_task1_running = 0;
        is_task2_running = 0;
        is_aiming = 0;
        Set_Motor_PWM(0, 0);
        break;
    case 0x01: // 任务切换
        lcd_cmd = 0xFF;
        if (++task_index > 2)
            task_index = 1;
        break;
    case 0x02: // 确认执行
        lcd_cmd = 0xFF;
        switch (task_index)
        {
        case 1: // 执行task1
            is_task1_running = 1;
            is_task2_running = 0;
            break;
        case 2: // 执行task2
            is_task2_running = 1;
            is_task1_running = 0;
            break;
        }
        break;
    }
}
/**
 * @brief ui显示
 */
void lcd_disp(void)
{
    lcd_printf("n0.val=%d\xff\xff\xff", dx_center_signed + OFFSET_CENTER_X); // com_k230.c --> com_lcd.c
    lcd_printf("n1.val=%d\xff\xff\xff", dy_center_signed + OFFSET_CENTER_Y);

    switch (task_index)
    {
    case 1:
        if (is_task1_running)
        {
            lcd_printf("t23.txt=\"静态\"\xff\xff\xff");
            lcd_printf("t25.txt=\"task1\"\xff\xff\xff");
            lcd_printf("t17.txt=\"正在运行中...\"\xff\xff\xff");

            if (target_detected)
            { // 识别到矩形
                lcd_printf("t11.txt=\"识别成功\"\xff\xff\xff");
                if (is_aiming)
                {
                    lcd_printf("t14.txt=\"目标已锁定\"\xff\xff\xff");
                }
                else
                {
                    lcd_printf("t14.txt=\"正在追踪...\"\xff\xff\xff");
                }
            }
            else
            {
                lcd_printf("t11.txt=\"识别中...\"\xff\xff\xff");
                if (!is_aiming)
                {
                    lcd_printf("t14.txt=\"目标丢失\"\xff\xff\xff");
                }
            }
        }
        else
        {
            lcd_printf("t23.txt=\"静态\"\xff\xff\xff");
            lcd_printf("t25.txt=\"task1\"\xff\xff\xff");
            lcd_printf("t17.txt=\"初始化成功\"\xff\xff\xff");
            lcd_printf("t11.txt=\"未启动\"\xff\xff\xff");
            lcd_printf("t14.txt=\"未启动\"\xff\xff\xff");
        }
        break;
    case 2:
        if (is_task2_running)
        {
            lcd_printf("t23.txt=\"动态\"\xff\xff\xff");
            lcd_printf("t25.txt=\"task2\"\xff\xff\xff");
            lcd_printf("t17.txt=\"正在运行中...\"\xff\xff\xff");

            if (target_detected)
            { // 识别到矩形
                lcd_printf("t11.txt=\"识别成功\"\xff\xff\xff");
                if (is_aiming)
                {
                    lcd_printf("t14.txt=\"目标已锁定\"\xff\xff\xff");
                }
                else
                {
                    lcd_printf("t14.txt=\"正在追踪...\"\xff\xff\xff");
                }
            }
            else
            {
                lcd_printf("t11.txt=\"识别中...\"\xff\xff\xff");
                if (!is_aiming)
                {
                    lcd_printf("t14.txt=\"目标丢失\"\xff\xff\xff");
                }
            }
        }
        else
        {
            lcd_printf("t23.txt=\"动态\"\xff\xff\xff");
            lcd_printf("t25.txt=\"task2\"\xff\xff\xff");
            lcd_printf("t17.txt=\"初始化成功\"\xff\xff\xff");
            lcd_printf("t11.txt=\"未启动\"\xff\xff\xff");
            lcd_printf("t14.txt=\"未启动\"\xff\xff\xff");
        }
        break;
    default:
        break;
    }
}

/**
 * @brief lcd有关的任务
 */
void lcd_process(void)
{
    lcd_send_cmd();
    lcd_disp();
}

/**
 * @brief UART3 中断接收函数 处理LCD发出的数据包
 */
void UART3_IRQHandler(void)
{
    if (DL_UART_getPendingInterrupt(UART_3_INST))
    {
        u3_rx_data = DL_UART_Main_receiveData(UART_3_INST);
        // DL_GPIO_clearPins(LED_PORT,  LED_PIN_22_PIN); // test
        DL_UART_clearInterruptStatus(UART_3_INST, DL_UART_INTERRUPT_RX);
        uart_lcd_pack_data((uint8_t)u3_rx_data);
    }
}
