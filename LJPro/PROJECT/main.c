#include "function.h"

//该处的宏用于select函数中的预编译,若为瓶子部分的主控板则注释第二个宏
#define BOTTLE
#define METAL_PAPER

unsigned char usart_getdat(USART_TypeDef* USARTx,unsigned char* usart_dat);
void usart_parsedat(unsigned char usart_dat,unsigned char* buff);
void select(unsigned char* buff);

unsigned char usart_rec_buff[4] = {0x00};
unsigned char usart_dat_rec = 0x00;
unsigned char addr_flag = 0x00;	//地址标志
unsigned char code_flag = 0x00;	//操作码标志
unsigned char dat0_flag = 0x00;	//数据包
unsigned char dat1_flag = 0x00;	//数据包

int main()
{
	function_init();
	
	while(1)
	{
		//以下串口方式未使用循环,最深为三层嵌套判断,只占用极少的 cpu 时间
		if(usart_getdat(USART_M,&usart_dat_rec))	//检测并接收串口数据
			usart_parsedat(usart_dat_rec,usart_rec_buff);	//解析串口数据,若接收到规定的数据包则提取目标地址及操作码
		//进入选择
		select(usart_rec_buff);
	}
}

//
//	根据目标地址选择动作
//	a_flag : 目标地址
//	c_flag : 操作码
//
void select(unsigned char* buff)
{
	switch(buff[0])
	{
	#ifdef BOTTLE
		case 0xA2: bottle_function(buff); break;	//瓶子
	#endif
	#ifdef METAL_PAPER	
		case 0xA3: metal_function(buff); break;	//金属
		case 0xA4: paper_function(buff); break;	//纸类
	#endif
	}
	/**/
}

unsigned char crc_buff[6] = {0x08,0xA1,0x00,0x00,0x00,0x00};	//用于计算crc的数据缓冲区
unsigned short crc_result = 0x0000;	//crc的计算结果
unsigned char datapack_index = 0;	//数据包的下标
//
//	解析来自串口的数据,只提取规定的协议
//	使用该方法尽量减少接收和解析串口数据时对cpu的占用时间
//	解析完成后将给出数据包的目标地址和操作码
//	usart_dat : 当前接收到的串口数据
//	a_flag : 用于存储目标地址的变量
//	c_flag : 用于存储操作码的变量
//
void usart_parsedat(unsigned char usart_dat,unsigned char* buff)
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
					datapack_index++;
				}
				else datapack_index = 0; break;	//判断获取操作码
		case 6: if(usart_dat == 0x00 || usart_dat == 0xff)
				{
					crc_buff[4] = usart_dat;
					datapack_index++; 
				}
				else datapack_index = 0; break;	//确认数据包
		case 7: if(usart_dat == 0x00 || usart_dat == 0xff)
				{
					crc_buff[5] = usart_dat;
					crc_result = crc(crc_buff,6);
					datapack_index++; 
				}
				else datapack_index = 0; break;	//确认数据包
		case 8: if(usart_dat == (crc_result>>8)) datapack_index++;	//确认CRC，否则清除
				else { crc_result = 0x0000; datapack_index = 0; } break;
		case 9: if(usart_dat == (crc_result&0x00ff))	//确认CRC，否则清除
				{
					buff[0] = crc_buff[2];	//获取目标地址
					buff[1] = crc_buff[3];	//获取操作码
					buff[2] = crc_buff[4];	//获取数据包
					buff[3] = crc_buff[5];	//获取数据包
					datapack_index = 0;
				}
				else { crc_result = 0x0000; datapack_index = 0; } break;
	}
}

//
//	接收串口数据
//	USARTx : 串口号
//	usart_dat : 用于存储该次串口数据的变量
//	return : 若有串口数据则返回 1 ,否则返回 0
//
unsigned char usart_getdat(USART_TypeDef* USARTx,unsigned char* usart_dat)
{
	if(USART_GetFlagStatus(USARTx,USART_FLAG_RXNE))
	{
		*usart_dat = USART_ReceiveData(USARTx);
		return 1;
	}
	return 0;
}
