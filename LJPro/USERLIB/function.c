#include "function.h"

//
//	瓶子部分的功能
//
void bottle_function(unsigned char* a_flag,unsigned char* c_flag)
{
	switch(*c_flag)
	{
		case 0xB1: door_bottle_user(a_flag,c_flag,open); break;	//用户开门操作码
		case 0xB2: door_bottle_user(a_flag,c_flag,close); break;	//用户关门操作码
		case 0xB3: door_bottle_manage(a_flag,c_flag,open); break;	//管理员开门操作码
		case 0xB4: door_bottle_manage(a_flag,c_flag,close); break;	//管理员关门操作码
	}
}

//
//	金属部分的功能
//

void metal_function(unsigned char* a_flag,unsigned char* c_flag)
{
	switch(*c_flag)
	{
		case 0xB1: door_metal_user(a_flag,c_flag,open); break;	//用户开门操作码
		case 0xB2: door_metal_user(a_flag,c_flag,open); break;	//用户关门操作码
		case 0xB3: door_metal_manage(a_flag,c_flag,open); break;	//管理员开门操作码
		case 0xB4: door_metal_manage(a_flag,c_flag,close); break;	//管理员关门操作码
		case 0xD1: weight_metal(a_flag,c_flag); break;	//称重
	}
}

//
//	纸类部分的功能
//

void paper_function(unsigned char* a_flag,unsigned char* c_flag)
{
	switch(*c_flag)
	{
		case 0xB1: door_paper_user(a_flag,c_flag,open); break;	//用户开门操作码
		case 0xB2: door_paper_user(a_flag,c_flag,open); break;	//用户关门操作码
		case 0xB3: door_paper_manage(a_flag,c_flag,open); break;	//管理员开门操作码
		case 0xB4: door_paper_manage(a_flag,c_flag,close); break;	//管理员关门操作码
		case 0xD1: weight_paper(a_flag,c_flag); break;	//称重
	}
}

unsigned char usart_Buff_Send[16] = {0x00};	//串口发送缓冲区

//
//	瓶子部分用户的门操作
//
void door_bottle_user(unsigned char* a_flag,unsigned char* c_flag,enum door_io io)
{
	usart_ack(usart_Buff_Send,*a_flag,*c_flag);	//发送应答
	*a_flag = 0x00; *c_flag = 0x00;
}

//
//	瓶子部分管理员的门操作
//
void door_bottle_manage(unsigned char* a_flag,unsigned char* c_flag,enum door_io io)
{
	usart_ack(usart_Buff_Send,*a_flag,*c_flag);	//发送应答
	*a_flag = 0x00; *c_flag = 0x00;
}

//
//	金属部分用户的门操作
//
void door_metal_user(unsigned char* a_flag,unsigned char* c_flag,enum door_io io)
{
	usart_ack(usart_Buff_Send,*a_flag,*c_flag);	//发送应答
	*a_flag = 0x00; *c_flag = 0x00;
}

//
//	金属部分管理员的门操作
//
void door_metal_manage(unsigned char* a_flag,unsigned char* c_flag,enum door_io io)
{
	usart_ack(usart_Buff_Send,*a_flag,*c_flag);	//发送应答
	*a_flag = 0x00; *c_flag = 0x00;
}

//
//	金属部分称重
//
void weight_metal(unsigned char* a_flag,unsigned char* c_flag)
{
	usart_ack(usart_Buff_Send,*a_flag,*c_flag);	//发送应答
	*a_flag = 0x00; *c_flag = 0x00;
}

//
//	纸类部分用户的门操作
//
void door_paper_user(unsigned char* a_flag,unsigned char* c_flag,enum door_io io)
{
	usart_ack(usart_Buff_Send,*a_flag,*c_flag);	//发送应答
	*a_flag = 0x00; *c_flag = 0x00;
}

//
//	纸类部分管理员的门操作
//
void door_paper_manage(unsigned char* a_flag,unsigned char* c_flag,enum door_io io)
{
	usart_ack(usart_Buff_Send,*a_flag,*c_flag);	//发送应答
	*a_flag = 0x00; *c_flag = 0x00;
}

//
//	纸类部分称重
//
void weight_paper(unsigned char* a_flag,unsigned char* c_flag)
{
	usart_ack(usart_Buff_Send,*a_flag,*c_flag);	//发送应答
	*a_flag = 0x00; *c_flag = 0x00;
}

//
//	往串口发送应答(该函数也用于发送数据包内容皆位0的指令,例如光电信号的反馈)
//	buff : 发送缓冲区
//	a_flag : 目标地址(值安卓发送至STM32的数据包中的目标地址,即本模块的地址)
//	c_flag : 操作码
//
void usart_ack(unsigned char* buff,unsigned char a_flag,unsigned char c_flag)
{
	usart_buff_init(buff,a_flag,c_flag);	//初始化发送缓冲区
	unsigned short crc_result = crc(&buff[2],6);
	buff[8] = crc_result>>8;
	buff[9] = (unsigned char)(crc_result&0x00ff);
	usart_send(USART_M,buff,10);
}

//
//	往串口发送指令(该函数用于发送数据包包含执行状态的指令，例如开门的执行结果反馈)
//	前三个参数表同上
//	stat : 执行状态(success , fail)(这是一个枚举，定义于 drive.h 中)
//
void usart_cmd(unsigned char* buff,unsigned char a_flag,unsigned char c_flag,enum exe_status stat)
{
	usart_buff_init(buff,a_flag,c_flag);	//初始化发送缓冲区
	unsigned short crc_result = crc(&buff[2],6);
	buff[8] = crc_result>>8;
	buff[9] = (unsigned char)(crc_result&0x00ff);
	usart_send(USART_M,buff,10);
}

//
//	串口数据缓冲区初始化
//	参数表同上
//
void usart_buff_init(unsigned char* buff,unsigned char a_flag,unsigned char c_flag)
{
	buff[0] = 0x19;
	buff[1] = 0x19;
	buff[2] = 0x08;
	buff[3] = a_flag;
	buff[4] = 0xA1;
	buff[5] = c_flag;
	buff[6] = 0x00;
	buff[7] = 0x00;
	buff[8] = 0x00;
	buff[9] = 0x00;
}

//
//	计算CRC
//	buff: 需要计算的数据缓冲区,从缓冲区的第一个元素开始到第 len 元素停止
//	len: 数据长度
//	return: 返回 CRC-CCITT (XModem) 类型的CRC校验码
//
unsigned short crc(unsigned char* buff,unsigned char len)
{
	unsigned short crcin = 0x0000;
	unsigned short crc = 0x1021;
	while(len--)
	{
		crcin = ((crcin&0xff00)^((*buff++)<<8))|(crcin&0x00ff);
		unsigned char bi = 8;
		while(bi--)
		{
			if((crcin & 0x8000) > 0){crcin <<= 1; crcin ^= crc;}
			else crcin <<= 1;
		}
	}
	return crcin;
}
