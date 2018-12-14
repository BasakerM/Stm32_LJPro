#ifndef _usart_h
#define _usart_h

#include <stm32f10x.h>

#define BAUD 9600

#define USART_RCC_M RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA
#define USART_GPIO_M GPIOA
#define USART_PIN_TX_M GPIO_Pin_9
#define USART_PIN_RX_M GPIO_Pin_10
#define USART_M USART1

#define USART_RCC_S RCC_APB1Periph_USART2//|RCC_APB2Periph_GPIOA
#define USART_GPIO_S GPIOA
#define USART_PIN_TX_S GPIO_Pin_2
#define USART_PIN_RX_S GPIO_Pin_3
#define USART_S USART2

void usart_init(void);	//USART初始化函数
void usart_send(USART_TypeDef* USARTx,unsigned char* dat,unsigned char len);	//
void usart_send_str(USART_TypeDef* USARTx,char* str);	//发送字符串

#endif
