#include "systick.h"

//unsigned long Timing;
//unsigned long usart_timeout;

void systick_init(void)
{
	SysTick_Config(SystemCoreClock/10);//100ms中断一次
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;//关闭滴答
}

//
//	设定超时时间,并开启超时
//	sec : 要超时的时间,单位是1sec,小数位一位,例如2.5s
//
//unsigned long time_out_count = 0;
unsigned long time_out = 0;
void time_out_start(float sec)
{
	if(sec > 0)
	{
		time_out = sec*10;
		SysTick->CTRL |=SysTick_CTRL_ENABLE_Msk;//开启滴答
	}
}

//
//	关闭超时
void time_out_end(void)
{
	time_out = 0;
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;//关闭滴答
}

//
//	获取超时的状态
//	超时后返回 1,未超时则返回0
//
unsigned char time_out_getstatus(void)
{
	if(time_out)	//未超时
	{
		return 0;
	}
	else	//超时
	{
		SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;//关闭滴答
		return 1;
	}
}

/*void timeout_open(void)
{
	usart_timeout = 0;
	SysTick->CTRL |=SysTick_CTRL_ENABLE_Msk;//开启滴答
}

void timeout_close(void)
{
	usart_timeout = 0;
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;//关闭滴答
}

unsigned long timeout_get(void)
{
	return usart_timeout;
}

void timeout_clear(void)
{
	usart_timeout = 0;
}*/

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
//	time_out_count++;
	if(time_out)
		time_out--;
//	usart_timeout++;
//	if(Timing!=0)
//		Timing--;
}
