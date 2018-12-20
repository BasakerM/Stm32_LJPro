#include "driver.h"

//
//	电机控制
//	device : 电机设备类型(在deiver.h中定义有枚举)
//	mrun : 电机运行模式类型(在deiver.h中定义有枚举)
//
void motor_ctrl(enum motor_device device,enum motor_status mrun)
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
	else if(device == motor_paper)	//纸类推杆电机
	{
		switch(mrun)
		{
			case run_z: MOTOR_PAPER_OUT1(HIGH); MOTOR_PAPER_OUT2(LOW); break;	//正转
			case run_f: MOTOR_PAPER_OUT1(LOW); MOTOR_PAPER_OUT2(HIGH); break;	//反转
			case run_s: MOTOR_PAPER_OUT1(LOW); MOTOR_PAPER_OUT2(LOW); break;	//停止
		}
	}
	else if(device == motor_bottle_k)	//瓶子开门电机
	{
		switch(mrun)
		{
			case run_z: MOTOR_BOTTLE_K_OUT1(HIGH); MOTOR_BOTTLE_K_OUT2(LOW); break;	//正转
			case run_f: MOTOR_BOTTLE_K_OUT1(LOW); MOTOR_BOTTLE_K_OUT2(HIGH); break;	//反转
			case run_s: MOTOR_BOTTLE_K_OUT1(LOW); MOTOR_BOTTLE_K_OUT2(LOW); break;	//停止
		}
	}
	else if(device == motor_bottle_p)	//瓶子皮带电机
	{
		switch(mrun)
		{
			case run_z:  break;	//正转
			case run_f:  break;	//反转
			case run_s:  break;	//停止
		}
	}
}

enum device_power exti_line0 = off;	//金属光电
enum device_power exti_line1 = off;	//纸类光电
enum device_power exti_line2 = off;	//瓶子光电1
enum device_power exti_line3 = off;	//瓶子光电2
enum device_power exti_line4 = off;	//瓶子光电3

enum device_power exti_line5 = off;	//瓶子限位器1
enum device_power exti_line6 = off;	//瓶子限位器2
enum device_power exti_line7 = off;	//瓶子限位器3

enum device_power exti_line10 = off;	//瓶子限位器4
enum device_power exti_line11 = off;	//瓶子限位器5--管理员门
enum device_power exti_line12 = off;	//金属限位器--管理员门
enum device_power exti_line13 = off;	//纸类限位器--管理员门
//
//	获取门的状态
//
enum door_status door_status_get(enum door_device door)
{
	switch(door)
	{	//金属用户门////////////////////////////////
		case door_metal_user: break;
		//金属管理员门
		case door_metal_manage: 
			if(exti_line12 == on)	//管理员门在限位器闭合(on)时为 close
				return close;
			else
				return open;
			break;

		//纸类用户门////////////////////////////////
		case door_paper_user: break;
		//纸类管理员门
		case door_paper_manage: 
			if(exti_line13 == on)
				return close;
			else
				return open;
			break;

		//瓶子用户门////////////////////////////////
		case door_bottle_user: 
			if(exti_line5 == on || exti_line6 == on)
				return open;
			else if (exti_line7 == on)
				return close;
			else
				return ing;
			break;
		//瓶子管理员门
		case door_bottle_manage: 
			if(exti_line11 == on)
				return close;
			else
				return open;
			break;
	}
}

//
//	映射门设备类型到电机设备类型的关系
//	给门的类型,返回对应的控制设备
//
enum motor_device door_to_motor(enum door_device door)
{
	switch(door)
	{
		case door_metal_user: return motor_metal;
		case door_metal_manage: return lock_metal;
		case door_paper_user: return motor_paper;
		case door_paper_manage: return lock_paper;
		case door_bottle_user: return motor_bottle_k;
		case door_bottle_manage: return lock_bottle;
	}
}

///////////////////////////以下为 STM32 功能初始化部分/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为 STM32 功能初始化部分/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为 STM32 功能初始化部分/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为 STM32 功能初始化部分/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为 STM32 功能初始化部分/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为 STM32 功能初始化部分/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为 STM32 功能初始化部分/////////////////////////////////////////////////////////////////////////////////////
//
//	所有驱动初始化函数
//
void driver_init(void)
{
	led_init();
	exti_init();
	systick_init();
	motor_init();
}

//
//	初始化电机
//
void motor_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(MOTOR_RCC|MOTOR_PD_RCC,ENABLE);
	//开门,金属,电机
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = MOTOR_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MOTOR_GPIO,&GPIO_InitStructure);
	//皮带电机
	GPIO_InitStructure.GPIO_Pin = MOTOR_PD_PIN;
	GPIO_Init(MOTOR_PD_GPIO,&GPIO_InitStructure);

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
	
	LED_A(off);
	LED_B(off);
}

//
//	初始化外部中断
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
	//中断线0为跳变沿触发---金属光电
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource0);
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	//中断线1为跳变沿触发---纸类光电
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource1);
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
	EXTI_Init(&EXTI_InitStructure);
	//中断线2为跳变沿触发---瓶子光电1
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource2);
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
	EXTI_Init(&EXTI_InitStructure);
	//中断线3为跳变沿触发---瓶子光电2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource3);
	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
	EXTI_Init(&EXTI_InitStructure);
	//中断线4为跳变沿触发---瓶子光电3
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource4);
	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
	EXTI_Init(&EXTI_InitStructure);

	//中断线5为跳变沿触发---瓶子限位器1
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource5);
	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
	EXTI_Init(&EXTI_InitStructure);
	//中断线6为跳变沿触发---瓶子限位器2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource6);
	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
	EXTI_Init(&EXTI_InitStructure);
	//中断线7为跳变沿触发---瓶子限位器3
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource7);
	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
	EXTI_Init(&EXTI_InitStructure);

	//中断线10为跳变沿触发---瓶子限位器4
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource10);
	EXTI_InitStructure.EXTI_Line=EXTI_Line10;
	EXTI_Init(&EXTI_InitStructure);
	//中断线11为跳变沿触发---瓶子限位器5
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource11);
	EXTI_InitStructure.EXTI_Line=EXTI_Line11;
	EXTI_Init(&EXTI_InitStructure);
	//中断线12为跳变沿触发---金属限位器
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource12);
	EXTI_InitStructure.EXTI_Line=EXTI_Line12;
	EXTI_Init(&EXTI_InitStructure);
	//中断线13为跳变沿触发---纸类限位器
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource13);
	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
	EXTI_Init(&EXTI_InitStructure);
	
	//配置中断优先级
	//中断线0-4为同一优先级
 	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	//中断线5-9为同一优先级
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;
	NVIC_Init(&NVIC_InitStructure);
	//中断线10-15为同一优先级
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x05;
	NVIC_Init(&NVIC_InitStructure);
}

///////////////////////////以下为中断函数处理部分/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为中断函数处理部分/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为中断函数处理部分/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为中断函数处理部分/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为中断函数处理部分/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为中断函数处理部分/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为中断函数处理部分/////////////////////////////////////////////////////////////////////////////////////
//
//	中断线0使用该中断函数
//
void EXTI0_IRQHandler()
{	//金属光电
	if(EXTI_GetITStatus(EXTI_Line0))	//判断中断线
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_0) == Bit_SET)
			{exti_line0 = off; LED_A(off);}
		else
			{exti_line0 = on; LED_A(on);}
		EXTI_ClearITPendingBit(EXTI_Line0);	//清楚中断标志
	}
}

//
//	中断线1使用该中断函数
//
void EXTI1_IRQHandler()
{	//纸类光电
	if(EXTI_GetITStatus(EXTI_Line1))	//判断中断线
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_1) == Bit_SET)
			{exti_line1 = off; LED_A(off);}
		else
			{exti_line1 = on; LED_A(on);}
		EXTI_ClearITPendingBit(EXTI_Line1);	//清楚中断标志
	}
}

//
//	中断线2使用该中断函数
//
void EXTI2_IRQHandler()
{	//瓶子光电1
	if(EXTI_GetITStatus(EXTI_Line2))	//判断中断线
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_2) == Bit_SET)
			{exti_line2 = off; LED_A(off);}
		else
			{exti_line2 = on; LED_A(on);}
		EXTI_ClearITPendingBit(EXTI_Line2);	//清楚中断标志
	}
}

//
//	中断线3使用该中断函数
//
void EXTI3_IRQHandler()
{	//瓶子光电2
	if(EXTI_GetITStatus(EXTI_Line3))	//判断中断线
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_3) == Bit_SET)
			{exti_line3 = off; LED_A(off);}
		else
			{exti_line3 = on; LED_A(on);}
		EXTI_ClearITPendingBit(EXTI_Line3);	//清楚中断标志
	}
}

//
//	中断线4使用该中断函数
//
void EXTI4_IRQHandler()
{	//瓶子光电3
	if(EXTI_GetITStatus(EXTI_Line4))	//判断中断线
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_4) == Bit_SET)
			{exti_line4 = off; LED_A(off);}
		else
			{exti_line4 = on; LED_A(on);}
		EXTI_ClearITPendingBit(EXTI_Line4);	//清楚中断标志
	}
}

//
//	中断线5-9的皆使用该中断函数
//
//unsigned long step = 0;
void EXTI9_5_IRQHandler()
{
	//瓶子限位器1
	if(EXTI_GetITStatus(EXTI_Line5))	//判断中断线
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_5) == Bit_SET)
			{exti_line5 = off; LED_A(off);}
		else
			{exti_line5 = on; LED_A(on);}
		EXTI_ClearITPendingBit(EXTI_Line5);	//清楚中断标志
	}
	//瓶子限位器2
	if(EXTI_GetITStatus(EXTI_Line6))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_6) == Bit_SET)
			{exti_line6 = off; LED_A(off);}
		else
			{exti_line6 = on; LED_A(on);}
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
	//瓶子限位器3
	if(EXTI_GetITStatus(EXTI_Line7))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_7) == Bit_SET)
			{exti_line7 = off; LED_A(off);}
		else
			{exti_line7 = on; LED_A(on);}
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
}

//
//	中断线5-9的皆使用该中断函数
//
//unsigned long step = 0;
void EXTI15_10_IRQHandler()
{
	//瓶子限位器4
	if(EXTI_GetITStatus(EXTI_Line10))	//判断中断线
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_10) == Bit_SET)
			{exti_line10 = off; LED_A(off);}
		else
			{exti_line10 = on; LED_A(on);}
		EXTI_ClearITPendingBit(EXTI_Line10);	//清楚中断标志
	}
	//瓶子限位器5
	if(EXTI_GetITStatus(EXTI_Line11))	//判断中断线
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_11) == Bit_SET)
			{exti_line11 = off; LED_A(off);}
		else
			{exti_line11 = on; LED_A(on);}
		EXTI_ClearITPendingBit(EXTI_Line11);	//清楚中断标志
	}
	//金属限位器
	if(EXTI_GetITStatus(EXTI_Line12))	//判断中断线
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_12) == Bit_SET)
			{exti_line12 = off; LED_A(off);}
		else
			{exti_line12 = on; LED_A(on);}
		EXTI_ClearITPendingBit(EXTI_Line12);	//清楚中断标志
	}
	//纸类限位器
	if(EXTI_GetITStatus(EXTI_Line13))	//判断中断线
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_13) == Bit_SET)
			{exti_line13 = off; LED_A(off);}
		else
			{exti_line13 = on; LED_A(on);}
		EXTI_ClearITPendingBit(EXTI_Line13);	//清楚中断标志
	}
}
