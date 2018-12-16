#ifndef _drive_h
#define _drive_h

#include <stm32f10x.h>

enum door_io
{
	open = 0,close = 1
};

void door_user(unsigned char a_flag,enum door_io io);
void door_manage(unsigned char a_flag,enum door_io io);

#endif
