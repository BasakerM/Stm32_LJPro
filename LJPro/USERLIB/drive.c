#include "drive.h"
#include "usart.h"

//
//	对用户门的操作
//
void door_user(unsigned char* a_flag,unsigned char* c_flag,enum door_io io)
{
	switch(*a_flag)	//处理流程
	{
		case 0xA2: *a_flag = 0x00; *c_flag = 0x00; break;	//瓶子
		case 0xA3: *a_flag = 0x00; *c_flag = 0x00; break;	//金属
		case 0xA4: *a_flag = 0x00; *c_flag = 0x00; break;	//纸类
	}
}

//
//	对管理员门的操作
//
void door_manage(unsigned char* a_flag,unsigned char* c_flag,enum door_io io)
{
	switch(*a_flag)	//处理流程
	{
		case 0xA2: break;	//瓶子
		case 0xA3: break;	//金属
		case 0xA4: break;	//纸类
	}
}

//
//
//
void weigh_get(unsigned char* a_flag,unsigned char* c_flag)
{
	switch(*a_flag)	//处理流程
	{
		case 0xA3: break;	//金属
		case 0xA4: break;	//纸类
	}
}
