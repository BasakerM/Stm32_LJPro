#ifndef _function_h
#define _function_h

#include <stm32f10x.h>
#include "driver.h"

enum exe_status{exeing = 0,success = 1,fail = 2};

//具体操作
void bottle_door_user(unsigned char* a_flag,unsigned char* c_flag,enum door_status oc);
void bottle_door_manage(unsigned char* a_flag,unsigned char* c_flag,enum door_status oc);
void metal_door_user(unsigned char* a_flag,unsigned char* c_flag,enum door_status oc);
void metal_door_manage(unsigned char* a_flag,unsigned char* c_flag,enum door_status oc);
void metal_weight(unsigned char* a_flag,unsigned char* c_flag);
void paper_door_user(unsigned char* a_flag,unsigned char* c_flag,enum door_status oc);
void paper_door_manage(unsigned char* a_flag,unsigned char* c_flag,enum door_status oc);
void paper_weight(unsigned char* a_flag,unsigned char* c_flag);
//设备功能
void bottle_function(unsigned char* a_flag,unsigned char* c_flag);
void metal_function(unsigned char* a_flag,unsigned char* c_flag);
void paper_function(unsigned char* a_flag,unsigned char* c_flag);
//基础功能
enum exe_status door_ctrl_user(enum door_device door,enum door_status oc,float sec);
void usart_ack(unsigned char* buff,unsigned char a_flag,unsigned char c_flag);
void usart_buff_init(unsigned char* buff,unsigned char a_flag,unsigned char c_flag);
void function_init(void);
unsigned short crc(unsigned char* buff,unsigned char len);

#endif
