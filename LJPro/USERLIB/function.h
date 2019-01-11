#ifndef _function_h
#define _function_h

#include <stm32f10x.h>
#include "driver.h"

//该处的宏用于设备选择预编译,若为瓶子部分的主控板则注释第二个宏
#define BOTTLE
#define METAL_PAPER

#define OPEN_DOOR_DELAY 20
#define BOTTLE_PUT_DELAY 60
#define SCANF_CODE_DELAY 20
#define SCANF_CODE_ACK_DELAY 20
#define RECYCLE_DELAY 20
#define FAIL_DELAY 2
#define CLOSE_DOOR_DELAY 20

#define METAL_OPEN_DOOR_DELAY 3
#define METAL_PUT_DELAY 80
#define METAL_CLOSE_DOOR_DELAY 3

#define REC_BUFF_INDEX_ADDR 0
#define REC_BUFF_INDEX_CODE 1
#define REC_BUFF_INDEX_DAT0 2
#define REC_BUFF_INDEX_DAT1 3

enum enum_event
{
	event_none = 0,event_bottle_opendoor = 1,event_bottle_closedoor = 2,
	event_bottle_put = 3,event_bottle_scanfcode = 4,event_bottle_ack = 5,event_bottle_recycle = 6,event_bottle_fail = 7,
	event_bottle_openmanagedoor = 18,event_bottle_closemanagedoor = 19,
	event_metal_opendoor = 8,event_metal_closedoor = 9,event_metal_put = 10,event_metal_recycle = 11,event_metal_weigh = 12,
	event_metal_openmanagedoor = 20,event_metal_closemanagedoor = 21,
	event_paper_opendoor = 13,event_paper_closedoor = 14,event_paper_put = 15,event_paper_recycle = 16,event_paper_weigh = 17,
	event_paper_openmanagedoor = 22,event_paper_closemanagedoor = 23
};

//功能流程
void bottle_opendoor(enum enum_event* e_flag,unsigned char* buff);
void bottle_put(enum enum_event* e_flag,unsigned char* buff);
void bottle_scanfcode(enum enum_event* e_flag,unsigned char* buff);
void bottle_ack(enum enum_event* e_flag,unsigned char* buff);
void bottle_recycle(enum enum_event* e_flag,unsigned char* buff);
void bottle_fail(enum enum_event* e_flag,unsigned char* buff);
void bottle_closedoor(enum enum_event* e_flag,unsigned char* buff);
void metal_opendoor(enum enum_event* e_flag,unsigned char* buff);
void metal_put(enum enum_event* e_flag,unsigned char* buff);
void metal_closedoor(enum enum_event* e_flag,unsigned char* buff);
void paper_opendoor(enum enum_event* e_flag,unsigned char* buff);
void paper_put(enum enum_event* e_flag,unsigned char* buff);
void paper_closedoor(enum enum_event* e_flag,unsigned char* buff);
void paper_weigh(enum enum_event* e_flag,unsigned char* buff);
void metal_weigh(enum enum_event* e_flag,unsigned char* buff);
//结构
void event_select_bottle(enum enum_event* e_flag,unsigned char* buff);
void event_select_metal(enum enum_event* e_flag,unsigned char* buff);
void event_select_paper(enum enum_event* e_flag,unsigned char* buff);
void event_exe(enum enum_event* e_flag,unsigned char* buff);
void function(unsigned char* buff);
void clear_flag(unsigned char* buff);
unsigned char optin_code_get(unsigned char code);
void usart_ack(unsigned char* buff,unsigned char a_flag,unsigned char c_flag,unsigned char dat1,unsigned char dat2);
//基础功能
void function_init(void);
unsigned short crc(unsigned char* buff,unsigned char len);

#endif
