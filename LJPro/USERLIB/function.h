#ifndef _function_h
#define _function_h

#include <stm32f10x.h>
#include "driver.h"

enum exe_status{exeing = 0,success = 1,fail = 2};

//具体操作
void door_bottle_user(unsigned char* a_flag,unsigned char* c_flag,enum door_oc oc);
void door_bottle_manage(unsigned char* a_flag,unsigned char* c_flag,enum door_oc oc);
void door_metal_user(unsigned char* a_flag,unsigned char* c_flag,enum door_oc oc);
void door_metal_manage(unsigned char* a_flag,unsigned char* c_flag,enum door_oc oc);
void weight_metal(unsigned char* a_flag,unsigned char* c_flag);
void door_paper_user(unsigned char* a_flag,unsigned char* c_flag,enum door_oc oc);
void door_paper_manage(unsigned char* a_flag,unsigned char* c_flag,enum door_oc oc);
void weight_paper(unsigned char* a_flag,unsigned char* c_flag);
//设备功能
void bottle_function(unsigned char* a_flag,unsigned char* c_flag);
void metal_function(unsigned char* a_flag,unsigned char* c_flag);
void paper_function(unsigned char* a_flag,unsigned char* c_flag);
//基础功能
enum exe_status bottle_k_door(enum door_oc oc,unsigned char sec);
void usart_ack(unsigned char* buff,unsigned char a_flag,unsigned char c_flag);
void usart_buff_init(unsigned char* buff,unsigned char a_flag,unsigned char c_flag);
void function_init(void);
unsigned short crc(unsigned char* buff,unsigned char len);

#endif
