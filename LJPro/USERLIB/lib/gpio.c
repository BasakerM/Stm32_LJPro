#include "gpio.h"

void gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//³õÊ¼»¯½á¹¹Ìå
	RCC_APB2PeriphClockCmd(GPIO_RCC,ENABLE);	//³õÊ¼»¯Ê±ÖÓ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//ÍÆÍìÊä³öÄ£Ê½
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOX,&GPIO_InitStructure);	//³õÊ¼»¯GPIO
	GPIO_SetBits(GPIOX,GPIO_PIN);	//½«PINÖÃ¸ß
}
