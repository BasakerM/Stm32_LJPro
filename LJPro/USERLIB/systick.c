#include "systick.h"

//unsigned long Timing;
unsigned long usart_timeout;

void systick_init(void)
{
	SysTick_Config(SystemCoreClock/1000);//1ms中断一次
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;//关闭systick
}

void timeout_open(void)
{
	usart_timeout = 0;
	SysTick->CTRL |=SysTick_CTRL_ENABLE_Msk;//开启systick
}

void timeout_close(void)
{
	usart_timeout = 0;
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;//关闭systick
}

unsigned long timeout_get(void)
{
	return usart_timeout;
}

void timeout_clear(void)
{
	usart_timeout = 0;
}

//void systick_ms(unsigned long time)
//{
//	Timing=time*1000;
//	SysTick->CTRL |=SysTick_CTRL_ENABLE_Msk;
//	while(Timing!=0);
//}

//void systick_us(unsigned long time)
//{
//	Timing=time;
//	SysTick->CTRL |=SysTick_CTRL_ENABLE_Msk;
//	while(Timing!=0);
//}

void SysTick_Handler(void)
{
	usart_timeout++;
//	if(Timing!=0)
//		Timing--;
}
