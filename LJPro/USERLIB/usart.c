#include "usart.h"

//
//	初始化 USART
//	相关参数在头文件中使用宏定义配置
//

void usart_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//GPIO结构体
	RCC_APB2PeriphClockCmd(USART_RCC_M,ENABLE);	//使能GPIO
	USART_DeInit(USART_M);	//失能USART
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//推挽输出
	GPIO_InitStructure.GPIO_Pin = USART_PIN_TX_M;	//USART发送引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_GPIO_M,&GPIO_InitStructure);	//初始化GPIO
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入
	GPIO_InitStructure.GPIO_Pin = USART_PIN_RX_M;	//USART接收引脚
	GPIO_Init(USART_GPIO_M,&GPIO_InitStructure);	//初始化GPIO
	
	USART_InitTypeDef USART_InitStruct;	//USART结构体
	USART_InitStruct.USART_BaudRate = USART_BAUD_M;	//波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//无硬件控制流
	USART_InitStruct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;	//发送接收模式
	USART_InitStruct.USART_Parity = USART_PARITY_M;	//校验位
	USART_InitStruct.USART_StopBits = USART_STOPBIT_M;	//停止位
	USART_InitStruct.USART_WordLength = USART_DATABIT_M;	//数据位
	USART_Init(USART_M,&USART_InitStruct);	//初始化串口
	
	USART_Cmd(USART_M,ENABLE);	//使能USART
	
	USART_ClearFlag(USART_M,USART_FLAG_TC);	//清除USART标志(详见手册)
}

//
//	由于串口的接收未使用中断方式,所以采用该方式判断串口是否有数据
//	以下的实现仅为示例,并非一个完整的函数
//	dat : 要接收的数据(一个字节)
//
void usart_rec_byte(USART_TypeDef* USARTx,unsigned char* dat)
{
	if(USART_GetFlagStatus(USARTx,USART_FLAG_RXNE))
	{
		*dat = USART_ReceiveData(USARTx);
	}
}

//
//	往 USART 发送指定长度的数据
//	dat : 数据缓冲区
//	len : 要发送的数据长度
//
void usart_send(USART_TypeDef* USARTx,unsigned char* dat,unsigned char len)
{
	while(len--)
	{
		USART_SendData(USARTx,*dat++);
		while(!USART_GetFlagStatus(USARTx,USART_FLAG_TC));
	}
}

//
//	往 USART 发送字符串
//	str : 字符串缓冲区
//
void usart_send_str(USART_TypeDef* USARTx,unsigned char* str)
{
	while(*str != '\0')
	{
		USART_SendData(USARTx,*str++);
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);
	}
}
