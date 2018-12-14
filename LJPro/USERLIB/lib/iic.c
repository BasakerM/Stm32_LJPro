#include "iic.h"

void iic_delay_us(unsigned short us)
{
	unsigned short k = 0;
	while(--us)
	{
		k = 500;
		while(--k);
	}
}

void iic_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(GPIO_RCC_IIC,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_PIN_IIC_SCL|GPIO_PIN_IIC_SDA;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOX_IIC,&GPIO_InitStruct);
}

void iic_sda_in(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_PIN_IIC_SDA;
	GPIO_Init(GPIOX_IIC,&GPIO_InitStruct);
}

void iic_sda_out(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_PIN_IIC_SDA;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOX_IIC,&GPIO_InitStruct);
}

void iic_start(void)
{
	IIC_SCL_L;
	iic_delay_us(5);
	iic_sda_out();
	IIC_SDA_H;
	iic_delay_us(5);
	IIC_SCL_H;
	iic_delay_us(5);
	IIC_SDA_L;
	iic_delay_us(5);
	IIC_SCL_L;
	iic_delay_us(5);
}

void iic_stop(void)
{
	IIC_SCL_L;
	iic_delay_us(5);
	iic_sda_out();
	IIC_SDA_L;
	iic_delay_us(5);
	IIC_SCL_H;
	iic_delay_us(5);
	IIC_SDA_H;
	iic_delay_us(5);
	IIC_SCL_L;
	iic_delay_us(5);
}

unsigned char iic_wait_ack(void)
{
	unsigned short time = 0;
	IIC_SCL_L;
	iic_delay_us(5);
	iic_sda_out();
	IIC_SDA_H;
	iic_sda_in();
	iic_delay_us(5);
	IIC_SCL_H;
	iic_delay_us(5);
	while(IIC_SDA_R)
	{
		//time++;
		if(time > 65000) return 0;
	}
	iic_delay_us(5);
	IIC_SCL_L;
	iic_delay_us(5);
	return 1;
}

void iic_ack(void)
{
	IIC_SCL_L;
	iic_delay_us(5);
	iic_sda_out();
	IIC_SDA_L;
	iic_delay_us(5);
	IIC_SCL_H;
	iic_delay_us(5);
	IIC_SCL_L;
	iic_delay_us(5);
}

void iic_nack(void)
{
	IIC_SCL_L;
	iic_delay_us(5);
	iic_sda_out();
	IIC_SDA_H;
	iic_delay_us(5);
	IIC_SCL_H;
	iic_delay_us(5);
	IIC_SCL_L;
	iic_delay_us(5);
}

void iic_write_byte(unsigned char data)
{
	IIC_SCL_L;
	iic_delay_us(5);
	iic_sda_out();
	for(int i = 0;i < 8;i++)
	{
		if(data&0x80)
			IIC_SDA_H;
		else
			IIC_SDA_L;
		data <<= 1;
		iic_delay_us(5);
		IIC_SCL_H;
		iic_delay_us(5);
		IIC_SCL_L;
		iic_delay_us(5);
	}
}

unsigned char iic_read_byte(void)
{
	unsigned char data = 0x00;
	IIC_SCL_L;
	iic_delay_us(5);
	iic_sda_out();
	IIC_SDA_H;
	iic_sda_in();
	iic_delay_us(5);
	for(int i = 0;i < 8;i++)
	{
		IIC_SCL_H;
		iic_delay_us(5);
		data = (data<<1) | IIC_SDA_R;
		iic_delay_us(5);
		IIC_SCL_L;
		iic_delay_us(5);
	}
	return data;
}
