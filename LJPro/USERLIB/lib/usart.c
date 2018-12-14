#include "usart.h"

void usart_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//GPIO初始化结构体
	RCC_APB2PeriphClockCmd(USART_RCC_M,ENABLE);	//初始化USART_M时钟和GPIO
	RCC_APB1PeriphClockCmd(USART_RCC_S,ENABLE);	//初始化USART_S时钟和GPIO
	USART_DeInit(USART_M);	//复位USART_M
	USART_DeInit(USART_S);	//复位USART_S
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出模式
	GPIO_InitStructure.GPIO_Pin = USART_PIN_TX_M;	//USART_M发送引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//引脚输出频率
	GPIO_Init(USART_GPIO_M,&GPIO_InitStructure);	//初始化GPIO
	GPIO_InitStructure.GPIO_Pin = USART_PIN_TX_S;	//USART_S发送引脚
	GPIO_Init(USART_GPIO_S,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入模式
	GPIO_InitStructure.GPIO_Pin = USART_PIN_RX_M;	//USART_M接收引脚
	GPIO_Init(USART_GPIO_M,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = USART_PIN_RX_S;	//USART_S接收引脚
	GPIO_Init(USART_GPIO_S,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStruct;	//串口初始化结构体
	USART_InitStruct.USART_BaudRate = BAUD;	//波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//无硬件流
	USART_InitStruct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;	//收发模式
	USART_InitStruct.USART_Parity = USART_Parity_Even;	//偶校验
	//USART_InitStruct.USART_Parity = USART_Parity_No;	//无奇偶校验
	USART_InitStruct.USART_StopBits = USART_StopBits_1;	//1停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_9b;	//9数据位
	USART_Init(USART_M,&USART_InitStruct);	//初始化USART_M
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;	//8数据位
	USART_InitStruct.USART_Parity = USART_Parity_No;	//无奇偶校验
	USART_Init(USART_S,&USART_InitStruct);	//初始化USART_S
	
	USART_Cmd(USART_M,ENABLE);	//使能USART_M
	USART_Cmd(USART_S,ENABLE);	//使能USART_S
	
	USART_ClearFlag(USART_M,USART_FLAG_TC);	//在硬件复位后手动清除发送完成状态标志,否则如果在接收数据前发送数据的话会导致第一个字节被覆盖
	USART_ClearFlag(USART_S,USART_FLAG_TC);
}

void usart_send(USART_TypeDef* USARTx,unsigned char* dat,unsigned char len)
{
	while(len--)
	{
		USART_SendData(USARTx,*dat++);
		while(!USART_GetFlagStatus(USARTx,USART_FLAG_TC));
	}
}

void usart_send_str(USART_TypeDef* USARTx,char* str)
{
	while(*str != '\0')
	{
		USART_SendData(USARTx,*str++);
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);
	}
}

//void USART1_IRQHandler(void)
//{
//	if(USART_GetITStatus(USART1,USART_IT_RXNE))
//		USART_SendData(USART1,USART_ReceiveData(USART_M));
//}
