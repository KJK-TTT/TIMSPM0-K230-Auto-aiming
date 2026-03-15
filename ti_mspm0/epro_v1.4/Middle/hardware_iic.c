#include "hardware_iic.h"

unsigned char IIC_ReadByte(unsigned char Salve_Adress, unsigned char Reg_Address)
{
	return hardware_IIC_ReadByte(Salve_Adress, Reg_Address);
}
unsigned char IIC_ReadBytes(unsigned char Salve_Adress, unsigned char Reg_Address, unsigned char *Result, unsigned char len)
{
	return hardware_IIC_ReadBytes(Salve_Adress, Reg_Address, Result, len);
}
unsigned char IIC_WriteByte(unsigned char Salve_Adress, unsigned char Reg_Address, unsigned char data)
{
	return hardware_IIC_WirteByte(Salve_Adress, Reg_Address, data);
}
unsigned char IIC_WriteBytes(unsigned char Salve_Adress, unsigned char Reg_Address, unsigned char *data, unsigned char len)
{
	return hardware_IIC_WirteBytes(Salve_Adress, Reg_Address, data, len);
}
unsigned char Ping(void)
{
	unsigned char dat;
	dat = IIC_ReadByte(GW_GRAY_ADDR_DEF, GW_GRAY_PING);
	if (dat == GW_GRAY_PING_OK)
	{
		return 0;
	}
	else
		return 1;
}
unsigned char IIC_Get_Digtal(void)
{
	unsigned char dat;
	dat = IIC_ReadByte(GW_GRAY_ADDR_DEF, GW_GRAY_DIGITAL_MODE);
	return dat;
}

unsigned char IIC_Get_Anolog(unsigned char *Result, unsigned char len)
{
	if (IIC_ReadBytes(GW_GRAY_ADDR_DEF, GW_GRAY_ANALOG_BASE_, Result, len))
		return 1;
	else
		return 0;
}
unsigned char IIC_Get_Single_Anolog(unsigned char Channel)
{
	unsigned char dat;
	IIC_ReadBytes(GW_GRAY_ADDR_DEF, GW_GRAY_ANALOG(Channel), &dat, 1);
	return dat;
}
uint8_t IIC_write_buff[10] = {0}; // IIC写数据用的buff
unsigned char IIC_Get_Normalize(unsigned char *Result, unsigned char len)
{
	/*归一化*/
	/*归一化的意思是，使所有探头，在同一个白色或者黑色下，数据是一致的*/
	/*这个与校准是有关的，他是通过校准数据给模拟量进行软件处理归一化的*/
	IIC_write_buff[0] = GW_GRAY_ANALOG_NORMALIZE; // 归一化使能寄存器，掉电不存储
	IIC_write_buff[1] = 0xff;					  // 全通道开启
	IIC_WriteBytes(GW_GRAY_ADDR_DEF, GW_GRAY_ANALOG_NORMALIZE, &IIC_write_buff[1] /*命令+数据*/, 2 /*写入两个数据*/);
	delay_ms(10);																							   // 设置完，需要等上一会。stm8的运算速度没stm32快，等一下，让传感器把数据刷新一下。
	IIC_ReadBytes(GW_GRAY_ADDR_DEF, GW_GRAY_ANALOG_MODE, Result /*打开归一化后读到的数据存在Normalize里*/, 8); // 跟上面连续通道模拟量读取一样
	IIC_write_buff[0] = GW_GRAY_ANALOG_NORMALIZE;
	IIC_write_buff[1] = 0x00;																						  // 全通道关闭
	IIC_WriteBytes(GW_GRAY_ADDR_DEF, GW_GRAY_ANALOG_NORMALIZE, &IIC_write_buff[1] /*命令+数据*/, 2 /*写入两个数据*/); // 为了while(1)循环继续，当然是要关掉归一化的。
	return 1;
}
// 广播重置地址所需的数字
uint8_t reset_magic_number[8] = {
	0xB8, 0xD0, 0xCE, 0xAA,
	0xBF, 0xC6, 0xBC, 0xBC};
/**
 * @brief 写入数据到I2C设备
 * @param I2Cx I2C外设实例
 * @param data 待写入数据指针
 * @param length 数据长度
 * @return 实际成功写入的字节数
 * @note 基于硬件I2C实现
 */
uint8_t i2c_write(uint8_t *data, uint8_t length)
{
	// 假设使用0x00作为临时寄存器地址(广播重置不需要具体地址)
	if (hardware_IIC_WirteBytes(0x00, 0x00, data, length))
	{
		return length;
	}
	return 0;
}

/**
 * @brief I2C 设备重置函数
 * @note 通过向广播地址(0x00)发送特定的数据来重置I2C设备
 */
void i2c_reset(void)
{
	// 发送重置魔术字
	i2c_write((uint8_t *)reset_magic_number, 8);
}
