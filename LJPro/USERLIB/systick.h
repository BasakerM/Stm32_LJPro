#ifndef _systick_h
#define _systick_h

#include "stm32f10x.h"

void systick_init(void);
void timeout_start(float sec);
void timeout_end(void);
unsigned char timeout_status_get(void);
/*void systick_ms(unsigned long time);
void systick_us(unsigned long time);
void timeout_open(void);
void timeout_close(void);
unsigned long timeout_get(void);
void timeout_clear(void);*/

#endif
