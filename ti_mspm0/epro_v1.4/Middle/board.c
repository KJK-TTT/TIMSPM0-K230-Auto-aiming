#include "board.h"

static void uart0_sendChar(uint8_t dat)
{
    // 当串口0忙的时候等待，不忙的时候再发送传进来的字符
    while (DL_UART_isBusy(UART_0_INST) == true)
        ;

    // 发送单个字符
    DL_UART_Main_transmitData(UART_0_INST, dat);
}

static void uart1_sendChar(uint8_t dat)
{
    // 当串口0忙的时候等待，不忙的时候再发送传进来的字符
    while (DL_UART_isBusy(UART_1_INST) == true)
        ;

    // 发送单个字符
    DL_UART_Main_transmitData(UART_1_INST, dat);
}

static void uart3_sendChar(uint8_t dat)
{
    // 当串口0忙的时候等待，不忙的时候再发送传进来的字符
    while (DL_UART_isBusy(UART_3_INST) == true)
        ;

    // 发送单个字符
    DL_UART_Main_transmitData(UART_3_INST, dat);
}

static void uart0_sendString(char *str)
{
    // 当前字符串地址不在结尾 并且 字符串首地址不为空
    while (*str != 0 && str != 0)
    {
        // 发送字符串首地址中的字符，并且在发送完成之后首地址自增
        uart0_sendChar(*str++);
    }
}

static void uart1_sendString(char *str)
{
    // 当前字符串地址不在结尾 并且 字符串首地址不为空
    while (*str != 0 && str != 0)
    {
        // 发送字符串首地址中的字符，并且在发送完成之后首地址自增
        uart1_sendChar(*str++);
    }
}

static void uart3_sendString(char *str)
{
    // 当前字符串地址不在结尾 并且 字符串首地址不为空
    while (*str != 0 && str != 0)
    {
        // 发送字符串首地址中的字符，并且在发送完成之后首地址自增
        uart3_sendChar(*str++);
    }
}

int lc_printf(char *format, ...)
{
    va_list args;
    va_start(args, format);

    // 创建一个足够大的缓冲区来存储格式化后的字符串
    char buffer[512] = {0};
    int len = vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);

    // 发送格式化后的字符串
    uart0_sendString(buffer);

    return len;
}

int ek_printf(char *format, ...)
{
    va_list args;
    va_start(args, format);

    // 创建一个足够大的缓冲区来存储格式化后的字符串
    char buffer[512] = {0};
    int len = vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);

    // 发送格式化后的字符串
    uart1_sendString(buffer);

    return len;
}

int lcd_printf(char *format, ...)
{
    va_list args;
    va_start(args, format);

    // 创建一个足够大的缓冲区来存储格式化后的字符串
    char buffer[512] = {0};
    int len = vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);

    // 发送格式化后的字符串
    uart3_sendString(buffer);

    return len;
}

/* ================ 延时函数封装 =================== */
volatile unsigned int delay_times = 0;
void delay_ms(unsigned int ms)
{
    delay_times = ms;
    while (delay_times != 0)
        ;
}
// 滴答定时器中断服务函数
void SysTick_Handler(void)
{
    if (delay_times != 0)
    {
        delay_times--;
    }
}

void delay_us(int __us) { delay_cycles((CPUCLK_FREQ / 1000 / 1000) * __us); }
// void delay_ms(int __ms) { delay_cycles( (CPUCLK_FREQ / 1000)*__ms); }

void delay_1us(int __us) { delay_cycles((CPUCLK_FREQ / 1000 / 1000) * __us); }
void delay_1ms(int __ms) { delay_cycles((CPUCLK_FREQ / 1000) * __ms); }
