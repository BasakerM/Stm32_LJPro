#ifndef _iic_h
#define _iic_h

#include <stm32f10x.h>

#define GPIO_RCC_IIC RCC_APB2Periph_GPIOA
#define GPIOX_IIC GPIOA
#define GPIO_PIN_IIC_SDA GPIO_Pin_0
#define GPIO_PIN_IIC_SCL GPIO_Pin_1

#define IIC_SDA_H GPIO_SetBits(GPIOX_IIC,GPIO_PIN_IIC_SDA)
#define IIC_SDA_L GPIO_ResetBits(GPIOX_IIC,GPIO_PIN_IIC_SDA)
#define IIC_SDA_R GPIO_ReadInputDataBit(GPIOX_IIC,GPIO_PIN_IIC_SDA)
#define IIC_SCL_H GPIO_SetBits(GPIOX_IIC,GPIO_PIN_IIC_SCL)
#define IIC_SCL_L GPIO_ResetBits(GPIOX_IIC,GPIO_PIN_IIC_SCL)

void iic_init(void);
void iic_sda_in(void);
void iic_sda_out(void);
void iic_start(void);
void iic_stop(void);
unsigned char iic_wait_ack(void);
void iic_ack(void);
void iic_nack(void);
void iic_write_byte(unsigned char data);
unsigned char iic_read_byte(void);

#endif
