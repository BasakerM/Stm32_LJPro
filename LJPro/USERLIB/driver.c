#include "driver.h"

void driver_init(void)
{
	led_init();
	exti_init();
	systick_init();
	motor_init();
}

//
//	电机控制
//	device : 电机类型(在deiver.h中定义有枚举)
//	mrun : 控制类型(在deiver.h中定义有枚举)
//
void motor_ctrl(enum motor_device device,enum motor_run mrun)
{
	if(device == motor_metal)	//金属推杆电机
	{
		switch(mrun)
		{
			case run_z: MOTOR_METAL_OUT1(HIGH); MOTOR_METAL_OUT2(LOW); break;	//正转
			case run_f: MOTOR_METAL_OUT1(LOW); MOTOR_METAL_OUT2(HIGH); break;	//反转
			case run_s: MOTOR_METAL_OUT1(LOW); MOTOR_METAL_OUT2(LOW); break;	//停止
		}
	}
	if(device == motor_paper)	//纸类推杆电机
	{
		switch(mrun)
		{
			case run_z: MOTOR_PAPER_OUT1(HIGH); MOTOR_PAPER_OUT2(LOW); break;	//正转
			case run_f: MOTOR_PAPER_OUT1(LOW); MOTOR_PAPER_OUT2(HIGH); break;	//反转
			case run_s: MOTOR_PAPER_OUT1(LOW); MOTOR_PAPER_OUT2(LOW); break;	//停止
		}
	}
	if(device == motor_bottle_k)	//瓶子开门电机
	{
		switch(mrun)
		{
			case run_z: MOTOR_BOTTLE_K_OUT1(HIGH); MOTOR_BOTTLE_K_OUT2(LOW); break;	//正转
			case run_f: MOTOR_BOTTLE_K_OUT1(LOW); MOTOR_BOTTLE_K_OUT2(HIGH); break;	//反转
			case run_s: MOTOR_BOTTLE_K_OUT1(LOW); MOTOR_BOTTLE_K_OUT2(LOW); break;	//停止
		}
	}
}

//
//	获取瓶子用户门的状态
//
enum device_of exti_bottle_1 = off;	//瓶子光电1
enum device_of exti_bottle_2 = off;	//瓶子光电2
enum device_of exti_bottle_3 = off;	//瓶子光电3
enum device_of exti_bottle_4 = off;	//瓶子光电大门
enum device_of exti_bottle_5 = off;	//瓶子光电管理员门
enum door_oc door_bottle_k_getstatus(void)
{
	if(exti_bottle_1 == on || exti_bottle_2 == on)
		return open;
	else if (exti_bottle_3 == on)
		return close;
	else
		return ing;
}

//
//	初始化电机
//
void motor_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(MOTOR_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = MOTOR_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MOTOR_GPIO,&GPIO_InitStructure);

	MOTOR_METAL_OUT1(LOW);	//停止
	MOTOR_METAL_OUT2(LOW);
}

//
//	初始化板载的led
//
void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(LED_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LED_PIN_A;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO_A,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LED_PIN_B;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO_B,&GPIO_InitStructure);
	
	LED_A(OFF);
	LED_B(OFF);
}

//
//	外部中断初始化
//
void exti_init(void)
{	//初始化外部中断的GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(INTERRUPT_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = INTERRUPT_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(INTERRUPT_GPIO,&GPIO_InitStructure);
	
	//初始化外部中断
	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//中断线5为跳变沿触发
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource5);
	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	//中断线6为跳变沿触发
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource6);
	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
	EXTI_Init(&EXTI_InitStructure);
	//中断线7为跳变沿触发
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource7);
	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
	EXTI_Init(&EXTI_InitStructure);
	
	//配置中断优先级
	//中断线5-9为同一优先级
 	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//
//	中断线5-9的皆使用该中断函数
//
//unsigned long step = 0;
void EXTI9_5_IRQHandler()
{
	//瓶子开门光电1
	if(EXTI_GetITStatus(EXTI_Line5))	//判断中断线
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_5) == Bit_SET)
			{exti_bottle_1 = off; LED_A(OFF);}
		else
			{exti_bottle_1 = on; LED_A(ON);}
		EXTI_ClearITPendingBit(EXTI_Line5);	//清楚中断标志
	}
	//瓶子开门光电2
	if(EXTI_GetITStatus(EXTI_Line6))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_6) == Bit_SET)
			{exti_bottle_2 = off; LED_B(OFF);}
		else
			{exti_bottle_2 = on; LED_B(ON);}
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
	//瓶子开门光电3
	if(EXTI_GetITStatus(EXTI_Line7))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_7) == Bit_SET)
			{exti_bottle_3 = off; LED_A(OFF);LED_B(OFF);}
		else
			{exti_bottle_3 = on; LED_A(ON);LED_B(ON);}
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
}
