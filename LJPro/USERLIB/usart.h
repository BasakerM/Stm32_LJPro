#ifndef _usart_h
#define _usart_h

#include <stm32f10x.h>

#define USART_BAUD_M 9600
#define USART_DATABIT_M USART_WordLength_8b
#define USART_STOPBIT_M USART_StopBits_1
#define USART_PARITY_M USART_Parity_No

#define USART_RCC_M RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA
#define USART_GPIO_M GPIOA
#define USART_PIN_TX_M GPIO_Pin_9
#define USART_PIN_RX_M GPIO_Pin_10
#define USART_M USART1 //调用USART的函数时使用该宏

void usart_init(void);
void usart_rec_byte(USART_TypeDef* USARTx,unsigned char* dat);
void usart_send(USART_TypeDef* USARTx,unsigned char* dat,unsigned char len);
void usart_send_str(USART_TypeDef* USARTx,unsigned char* str);

#endif
