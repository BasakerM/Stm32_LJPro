#include "drive.h"

//
//	对用户门的操作
//
void door_user(unsigned char a_flag,enum door_io io)
{
	switch(a_flag)	//处理流程
	{
		case 0xA2: break;	//瓶子
		case 0xA3: break;	//金属
		case 0xA4: break;	//纸类
	}
}

//
//	对管理员门的操作
//
void door_manage(unsigned char a_flag,enum door_io io)
{
	switch(a_flag)	//处理流程
	{
		case 0xA2: break;	//瓶子
		case 0xA3: break;	//金属
		case 0xA4: break;	//纸类
	}
}

//
//
//
unsigned short weigh_get(unsigned char a_flag)
{
	switch(a_flag)	//处理流程
	{
		case 0xA3: break;	//金属
		case 0xA4: break;	//纸类
	}
	return 0;
}
