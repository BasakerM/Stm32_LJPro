#ifndef _function_h
#define _function_h

#include <stm32f10x.h>
#include "driver.h"

//功能流程
void bottle_opendoor(enum enum_event* e_flag,unsigned char c_flag);
//结构
void event_exe(enum enum_event* e_flag,unsigned char c_flag);
enum enum_event event_select(enum enum_event e_flag,unsigned char c_flag);
void bottle_function(unsigned char c_flag);
void metal_function(unsigned char c_flag);
void paper_function(unsigned char c_flag);
//基础功能
void function_init(void);
void usart_ack(unsigned char* buff,unsigned char a_flag,unsigned char c_flag,unsigned char dat1,unsigned char dat2);
unsigned short crc(unsigned char* buff,unsigned char len);

#endif
