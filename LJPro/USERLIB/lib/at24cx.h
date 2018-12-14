#ifndef _at24cx_h
#define _at24cx_h

#include <stm32f10x.h>
#include "iic.h"

#define AT24CX_ADDR_W 0xA0
#define AT24CX_ADDR_R 0xA1

void at24cx_init(void);
void at24cx_write_byte(unsigned char addr,unsigned char data);
unsigned char at24cx_read_byte(unsigned char addr);

#endif
