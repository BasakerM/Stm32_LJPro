#ifndef _function_h
#define _function_h

#include <stm32f10x.h>
#include "usart.h"

enum door_io
{
	open = 0,close = 1
};
enum exe_status
{
	success = 0,fail = 1
};

void bottle_function(unsigned char* a_flag,unsigned char* c_flag);
void metal_function(unsigned char* a_flag,unsigned char* c_flag);
void paper_function(unsigned char* a_flag,unsigned char* c_flag);
void door_bottle_user(unsigned char* a_flag,unsigned char* c_flag,enum door_io io);
void door_bottle_manage(unsigned char* a_flag,unsigned char* c_flag,enum door_io io);
void door_metal_user(unsigned char* a_flag,unsigned char* c_flag,enum door_io io);
void door_metal_manage(unsigned char* a_flag,unsigned char* c_flag,enum door_io io);
void weight_metal(unsigned char* a_flag,unsigned char* c_flag);
void door_paper_user(unsigned char* a_flag,unsigned char* c_flag,enum door_io io);
void door_paper_manage(unsigned char* a_flag,unsigned char* c_flag,enum door_io io);
void weight_paper(unsigned char* a_flag,unsigned char* c_flag);
void usart_ack(unsigned char* buff,unsigned char a_flag,unsigned char c_flag);
void usart_buff_init(unsigned char* buff,unsigned char a_flag,unsigned char c_flag);
unsigned short crc(unsigned char* buff,unsigned char len);

#endif
