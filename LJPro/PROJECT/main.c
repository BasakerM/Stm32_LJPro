#include "usart.h"
#include "drive.h"

unsigned short crc(unsigned char* buff,unsigned char len);
char usart_getdat(USART_TypeDef* USARTx,char* usart_buff,unsigned char index);
unsigned char optin_code_get(unsigned char code);
void usart_parsedat(char* usart_dat,unsigned char* addr_flag,unsigned char* code_flag);
void flow(unsigned char* a_flag,unsigned char* c_flag);

char usart_Buff_Send[16] = 0x00;	//串口发送缓冲区
unsigned char usart_dat_rec = 0x00;
unsigned char addr_flag = 0x00;	//地址标志
unsigned char code_flag = 0x00;	//操作码标志

int main()
{
	usart_init();

	while(1)
	{
		if(usart_getdat(USART_M,&usart_dat_rec))	//检测并接收串口数据
			usart_parsedat(usart_dat_rec,&addr_flag,&code_flag);	//解析串口数据,若接收到规定的数据包则将操作码赋给flow_flag
		flow(addr_flag,code_flag);	//执行流程
	}
}

//
//	根据操作码选择动作
//
void flow(unsigned char* a_flag,unsigned char* c_flag)
{
	switch(*c_flag)
	{
		case 0x00: break;	//空闲状态
		case 0xB1: door_user(*a_flag,open); break;	//用户开门操作码
		case 0xB2: door_user(*a_flag,close); break;	//用户关门操作码
		case 0xB3: door_manage(*a_flag,open); break;	//管理员开门操作码
		case 0xB4: door_manage(*a_flag,close); break;	//管理员关门操作码
		case 0xD1: weigh_get(*a_flag) break;	//称重
	}
}

unsigned char crc_buff[6] = {0x08,0xA1,0x00,0x00,0x00,0x00};	//用于计算crc的数据缓冲区
unsigned short crc_result = 0x0000;	//crc的计算结果
unsigned char datapack_index = 0;	//数据包的下标
//
//	解析来自串口的数据,只提取规定的协议
//
void usart_parsedat(char* usart_dat,unsigned char* a_flag,unsigned char* c_flag)
{
	switch(datapack_index)
	{
		case 0: if(usart_dat == 0x19) datapack_index++; break;	//确认包头
		case 1: if(usart_dat == 0x19) datapack_index++; else datapack_index = 0; break;	//确认包头
		case 2: if(usart_dat == 0x08) datapack_index++; else datapack_index = 0; break;	//确认长度
		case 3: if(usart_dat == 0xA1) datapack_index++; else datapack_index = 0; break;	//确认源地址
		case 4: if(usart_dat == 0xA2 || usart_dat == 0xA3 || usart_dat == 0xA4)	//确认目标地址
				{
					crc_buff[2] = usart_dat;	//获取目标地址
					datapack_index++;
				}
				else datapack_index = 0; break;
		case 5: if(optin_code_get(usart_dat))
				{
					crc_buff[3] = usart_dat;	//获取操作码
					crc_result = crc(crc_buff,6);
					datapack_index++;
				}
				else datapack_index = 0; break;	//判断获取操作码
		case 6: if(usart_dat == 0x00) datapack_index++; else datapack_index = 0; break;	//确认数据包
		case 7: if(usart_dat == 0x00) datapack_index++; else datapack_index = 0; break;	//确认数据包
		case 8: if(usart_dat == (crc_result>>8)) datapack_index++;	//确认CRC，否则清除
				else { crc_result = 0x0000; datapack_index = 0; } break;
		case 9: if(usart_dat == (crc_result&0x00ff))	//确认CRC，否则清除
				{
					*a_flag = crc_buff[2];	//获取目标地址
					*c_flag = crc_buff[3];	//获取操作码
				}
				else { crc_result = 0x0000; datapack_index = 0; } break;
	}
}

//
//	查询操作码,若无规定的操作码则返回0x00
//
unsigned char optin_code_get(unsigned char code)
{
	switch(code)
	{
		case 0xB1: return 0xB1;
		case 0xB2: return 0xB2;
		case 0xB3: return 0xB3;
		case 0xB4: return 0xB4;
		case 0xC1: return 0xC1;
		case 0xC2: return 0xC2;
		case 0xC3: return 0xC3;
		case 0xC4: return 0xC4;
		case 0xD1: return 0xD1;
		default: return 0x00;
	}
}

//
//	接收串口数据存至接收缓冲区
//
char usart_getdat(USART_TypeDef* USARTx,char* usart_buff,unsigned char index)
{
	if(USART_GetFlagStatus(USARTx,USART_FLAG_RXNE))
	{
		usart_buff[index] = USART_ReceiveData(USARTx);
		return 1;
	}
	return 0;
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
