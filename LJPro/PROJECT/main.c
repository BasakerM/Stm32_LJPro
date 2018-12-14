#include "usart.h"

unsigned char flow_flag = 0;

#define PACK_HEAD 0x19
unsigned char usart_GetDat(USART_TypeDef* USARTx,unsigned char* usart_buff)
{
	if(USART_GetFlagStatus(USARTx,USART_FLAG_RXNE))
	{
		*usart_buff = USART_ReceiveData(USARTx);
		flow_flag = 1;
	}
	return 0;
	/*unsigned char usart_dat = 0;
	unsigned char usart_flag = 0;
	unsigned char usart_buff_index = 2;
	unsigned char usart_dat_len = 0;
	if(USART_GetFlagStatus(USARTx,USART_FLAG_RXNE))
	{
		usart_dat = USART_ReceiveData(USARTx);
		if(usart_dat == PACK_HEAD) timeout_open();
		else return 0;
		while(1)
		{
			if(USART_GetFlagStatus(USARTx,USART_FLAG_RXNE))
			{
				usart_dat = USART_ReceiveData(USARTx);
				timeout_clear();
				switch(usart_flag)
				{
					case 0: if(usart_dat == PACK_HEAD) usart_flag++; else return 0; break;
					case 1: usart_dat_len = usart_dat; usart_buff[usart_buff_index++] = usart_dat; usart_flag++; break;
					case 2: usart_buff[usart_buff_index++] = usart_dat; break;
				}
			}
			if(timeout_get() > 5) { timeout_close(); return 0; }
			if(usart_buff_index != 2 && usart_buff_index == usart_dat_len+2) break;
		}
		timeout_close();
		unsigned short c = crc(&usart_buff[2],usart_dat_len-2);
		if((c>>8 == usart_buff[usart_dat_len]) && ((c&0x00ff) == usart_buff[usart_dat_len+1])) return usart_dat_len;
	}
	return 0;*/
}

int main()
{
	usart_init();

	unsigned char ch = 0x00;
	while(1)
	{
		switch(flow_flag)
		{
			case 0: break;//usart_GetDat(USART_M,&ch); break;
			case 1: usart_send(USART_M,&ch,1); flow_flag = 0; break;
		}
	}
}
