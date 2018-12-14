#include "at24cx.h"

void at24cx_delay()
{
	unsigned short time = 8000;
	while(--time);
}

void at24cx_init(void)
{
	iic_init();
}

void at24cx_write_byte(unsigned char addr,unsigned char data)
{
	iic_start();
	iic_write_byte(AT24CX_ADDR_W);
	iic_wait_ack();
	iic_write_byte(0x00);
	iic_wait_ack();
	iic_write_byte(addr);
	iic_wait_ack();
	iic_write_byte(data);
	iic_wait_ack();
	iic_stop();
	at24cx_delay();
}

unsigned char at24cx_read_byte(unsigned char addr)
{
	unsigned char data = 0x00;
	iic_start();
	iic_write_byte(AT24CX_ADDR_W);
	iic_wait_ack();
	iic_write_byte(0x00);
	iic_wait_ack();
	iic_write_byte(addr);
	iic_wait_ack();
	iic_start();
	iic_write_byte(AT24CX_ADDR_R);
	iic_wait_ack();
	data = iic_read_byte();
	iic_nack();
	iic_stop();
	at24cx_delay();
	return data;
}
