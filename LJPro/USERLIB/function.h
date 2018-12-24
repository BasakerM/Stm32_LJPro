#ifndef _function_h
#define _function_h

#include <stm32f10x.h>
#include "driver.h"

#define REC_BUFF_INDEX_ADDR 0
#define REC_BUFF_INDEX_CODE 1
#define REC_BUFF_INDEX_DAT0 2
#define REC_BUFF_INDEX_DAT1 3

//功能流程
void bottle_opendoor(enum enum_event* e_flag,unsigned char* buff);
void bottle_put(enum enum_event* e_flag,unsigned char* buff);
void bottle_scanfcode(enum enum_event* e_flag,unsigned char* buff);
void bottle_ack(enum enum_event* e_flag,unsigned char* buff);
void bottle_recycle(enum enum_event* e_flag,unsigned char* buff);
void bottle_fail(enum enum_event* e_flag,unsigned char* buff);
void bottle_closedoor(enum enum_event* e_flag,unsigned char* buff);
//结构
void event_exe(enum enum_event* e_flag,unsigned char* buff);
enum enum_event event_select(enum enum_event e_flag,unsigned char c_flag);
unsigned char optin_code_get(unsigned char code);
void bottle_function(unsigned char* buff);
void metal_function(unsigned char* buff);
void paper_function(unsigned char* buff);
//基础功能
void function_init(void);
void usart_ack(unsigned char* buff,unsigned char a_flag,unsigned char c_flag,unsigned char dat1,unsigned char dat2);
unsigned short crc(unsigned char* buff,unsigned char len);

#endif
