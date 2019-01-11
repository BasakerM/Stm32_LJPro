#include "driver.h"

//
//	控制硬件状态
//	ht : 硬件类型(在 deiver.h 中定义有枚举 enum enum_hardware_type)
//	hs : 硬件状态(在 deiver.h 中定义有枚举 enum enum_hardware_status)
//
void hardware_control_status(enum_hardware_type ht,enum_hardware_status hs)
{
	switch(ht)
	{
		//control motor
		case enum_ht_motor_0:
			switch(hs)
			{
				case enum_hs_forward: MOTOR_0_SET_A(SET_HIGH); MOTOR_0_SET_B(SET_LOW); break;	//向前
				case enum_hs_backward: MOTOR_0_SET_A(SET_LOW); MOTOR_0_SET_B(SET_HIGH); break;	//向后
				case enum_hs_stop: MOTOR_0_SET_A(SET_LOW); MOTOR_0_SET_B(SET_LOW); break;	//停止
			}
		break;
		case enum_ht_motor_1:
			switch(hs)
			{
				case enum_hs_forward: MOTOR_1_SET_A(SET_HIGH); MOTOR_1_SET_B(SET_LOW); break;
				case enum_hs_backward: MOTOR_1_SET_A(SET_LOW); MOTOR_1_SET_B(SET_HIGH); break;
				case enum_hs_stop: MOTOR_1_SET_A(SET_LOW); MOTOR_1_SET_B(SET_LOW); break;
			}
		break;
		case enum_ht_motor_2:
			switch(hs)
			{
				case enum_hs_forward: MOTOR_2_SET_A(SET_HIGH); MOTOR_2_SET_B(SET_LOW); break;
				case enum_hs_backward: MOTOR_2_SET_A(SET_LOW); MOTOR_2_SET_B(SET_HIGH); break;
				case enum_hs_stop: MOTOR_2_SET_A(SET_LOW); MOTOR_2_SET_B(SET_LOW); break;
			}
		break;
		case enum_ht_motor_3:
			switch(hs)
			{
				case enum_hs_forward: MOTOR_3_SET_A(SET_HIGH); MOTOR_3_SET_B(SET_LOW); break;
				case enum_hs_backward: MOTOR_3_SET_A(SET_LOW); MOTOR_3_SET_B(SET_HIGH); break;
				case enum_hs_stop: MOTOR_3_SET_A(SET_LOW); MOTOR_3_SET_B(SET_LOW); break;
			}
		break;
		//control relay
		case enum_ht_realy_0:
			switch(hs)
			{
				case enum_hs_open: RELAY_0_SET(SET_HIGH); break;	//打开
				case enum_hs_close: RELAY_0_SET(SET_LOW); break;	//关闭
			}
		break;
		case enum_ht_realy_1:
			switch(hs)
			{
				case enum_hs_open: RELAY_1_SET(SET_HIGH); break;
				case enum_hs_close: RELAY_1_SET(SET_LOW); break;
			}
		break;
		case enum_ht_realy_2:
			switch(hs)
			{
				case enum_hs_open: RELAY_2_SET(SET_HIGH); break;
				case enum_hs_close: RELAY_2_SET(SET_LOW); break;
			}
		break;
	}
}


enum_hardware_status signal_sensor_0_status = enum_hs_off;
enum_hardware_status signal_sensor_1_status = enum_hs_off;
enum_hardware_status signal_sensor_2_status = enum_hs_off;
enum_hardware_status signal_sensor_3_status = enum_hs_off;
enum_hardware_status signal_sensor_4_status = enum_hs_off;
enum_hardware_status signal_sensor_5_status = enum_hs_off;
enum_hardware_status signal_sensor_6_status = enum_hs_off;
enum_hardware_status signal_sensor_7_status = enum_hs_off;
enum_hardware_status signal_sensor_8_status = enum_hs_off;
enum_hardware_status signal_sensor_9_status = enum_hs_off;
enum_hardware_status signal_sensor_10_status = enum_hs_off;
enum_hardware_status signal_sensor_11_status = enum_hs_off;
enum_hardware_status signal_sensor_12_status = enum_hs_off;
enum_hardware_status signal_sensor_13_status = enum_hs_off;
enum_hardware_status signal_sensor_14_status = enum_hs_off;
enum_hardware_status signal_sensor_15_status = enum_hs_off;
//
//	获取硬件状态
//	ht : 硬件类型(在 deiver.h 中定义有枚举 enum enum_hardware_type)
//	return : 硬件状态(在 deiver.h 中定义有枚举 enum enum_hardware_status)
//
enum_hardware_status hardware_get_status(enum_hardware_type ht)
{
	switch(ht)
	{
		case enum_ht_signal_sensor_0:
			return signal_sensor_0_status;
		case enum_ht_signal_sensor_1:
			return signal_sensor_1_status;
		case enum_ht_signal_sensor_2:
			return signal_sensor_2_status;
		case enum_ht_signal_sensor_3:
			return signal_sensor_3_status;
		case enum_ht_signal_sensor_4:
			return signal_sensor_4_status;
		case enum_ht_signal_sensor_5:
			return signal_sensor_5_status;
		case enum_ht_signal_sensor_6:
			return signal_sensor_6_status;
		case enum_ht_signal_sensor_7:
			return signal_sensor_7_status;
		case enum_ht_signal_sensor_8:
			return signal_sensor_8_status;
		case enum_ht_signal_sensor_9:
			return signal_sensor_9_status;
		case enum_ht_signal_sensor_10:
			return signal_sensor_10_status;
		case enum_ht_signal_sensor_11:
			return signal_sensor_11_status;
		case enum_ht_signal_sensor_12:
			return signal_sensor_12_status;
		case enum_ht_signal_sensor_13:
			return signal_sensor_13_status;
		case enum_ht_signal_sensor_14:
			return signal_sensor_14_status;
		case enum_ht_signal_sensor_15:
			return signal_sensor_15_status;
	}
	return enum_hs_none;
}

//
//	获取电压值
//	ht : 硬件类型(在 deiver.h 中定义有枚举 enum enum_hardware_type)
//	return : 返回单位为毫伏的电压值,例如 1654 mV
//
unsigned int get_voltage_value(enum_hardware_type ht)
{
	unsigned long adc = 0;
	unsigned long sum = 0;
	unsigned char count = 5;	//读五次值大概在半秒左右
	unsigned int t_count = 0;

	switch(ht)
	{
		case enum_ht_data_sensor_0:
			for(unsigned char i = 0;i < count;i++)
			{
				DATA_SENSOR_0_SET(SET_LOW);
				while(DATA_SENSOR_0_GET)
				{
					t_count++;
					if(t_count > 2000) break;
				}
				for(unsigned char k = 0;k < 24;k++)
				{
					DATA_SENSOR_0_SET(SET_HIGH);
					adc <<= 1;
					if(DATA_SENSOR_0_GET) adc++;
					DATA_SENSOR_0_SET(SET_LOW);
				}
				DATA_SENSOR_0_SET(SET_HIGH);
				adc = adc^0x800000;
				DATA_SENSOR_0_SET(SET_LOW);
				sum += (3.3/16777216)*adc*1000;
				adc = 0;
			}
		break;
		case enum_ht_data_sensor_0:
			for(unsigned char i = 0;i < count;i++)
			{
				DATA_SENSOR_1_SET(SET_LOW);
				while(DATA_SENSOR_1_GET)
				{
					t_count++;
					if(t_count > 2000) break;
				}
				for(unsigned char k = 0;k < 24;k++)
				{
					DATA_SENSOR_1_SET(SET_HIGH);
					adc <<= 1;
					if(DATA_SENSOR_1_GET) adc++;
					DATA_SENSOR_1_SET(SET_LOW);
				}
				DATA_SENSOR_1_SET(SET_HIGH);
				adc = adc^0x800000;
				DATA_SENSOR_1_SET(SET_LOW);
				sum += (3.3/16777216)*adc*1000;
				adc = 0;
			}
		break;
	}

	sum /= count;

	return sum;
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
	usart_init();
	systick_init();
	led_init();
	exti_init();
	motor_init();
	pwm_init();
	adc_init();
}

//
//	adc init
//
void adc_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(ADC_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = ADC_SET_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ADC_GPIO,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = ADC_GET_PIN;
	GPIO_Init(ADC_GPIO,&GPIO_InitStructure);
}

//
//	motor init
//
void motor_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(MOTOR_RCC,ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = MOTOR_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MOTOR_GPIO,&GPIO_InitStructure);

	hardware_control_status(enum_ht_motor_0,enum_hs_stop);
	hardware_control_status(enum_ht_motor_1,enum_hs_stop);
	hardware_control_status(enum_ht_motor_2,enum_hs_stop);
	hardware_control_status(enum_ht_motor_3,enum_hs_stop);
}

//
//	onboard led init
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
	
	LED_A(SET_HIGH);	//turn off the led
	LED_B(SET_HIGH);	//turn off the led
}

//
//	pwm init
//
void pwm_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 	RCC_APB2PeriphClockCmd(PWM_RCC|RCC_APB2Periph_AFIO, ENABLE);

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);

	GPIO_InitStructure.GPIO_Pin = PWM_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_GPIO, &GPIO_InitStructure);

	TIM_TimeBaseStructure.TIM_Period = 3599;	//72000000/3600=20Khz
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM3, ENABLE);

	TIM_SetCompare2(TIM3,2250);	//IO ouput 1.2V
}

//
//	interrupt init
//
void exti_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(INTERRUPT_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = INTERRUPT_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(INTERRUPT_GPIO,&GPIO_InitStructure);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource0);
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_Init(&EXTI_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource1);
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
	EXTI_Init(&EXTI_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource2);
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
	EXTI_Init(&EXTI_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource3);
	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
	EXTI_Init(&EXTI_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource4);
	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
	EXTI_Init(&EXTI_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource5);
	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
	EXTI_Init(&EXTI_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource6);
	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
	EXTI_Init(&EXTI_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource7);
	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
	EXTI_Init(&EXTI_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource8);
	EXTI_InitStructure.EXTI_Line=EXTI_Line8;
	EXTI_Init(&EXTI_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource9);
	EXTI_InitStructure.EXTI_Line=EXTI_Line9;
	EXTI_Init(&EXTI_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource10);
	EXTI_InitStructure.EXTI_Line=EXTI_Line10;
	EXTI_Init(&EXTI_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource11);
	EXTI_InitStructure.EXTI_Line=EXTI_Line11;
	EXTI_Init(&EXTI_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource12);
	EXTI_InitStructure.EXTI_Line=EXTI_Line12;
	EXTI_Init(&EXTI_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource13);
	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
	EXTI_Init(&EXTI_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource14);
	EXTI_InitStructure.EXTI_Line=EXTI_Line14;
	EXTI_Init(&EXTI_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource15);
	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
	EXTI_Init(&EXTI_InitStructure);
	
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
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;
	NVIC_Init(&NVIC_InitStructure);

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

void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		PWM_0_OUTPUT_REVERSE;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

void EXTI0_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line0))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_0) == Bit_SET)
			{signal_sensor_0_status = enum_hs_off; LED_A(SET_HIGH);}
		else
			{signal_sensor_0_status = enum_hs_on; LED_A(SET_LOW);}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI1_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line1))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_1) == Bit_SET)
			{signal_sensor_1_status = enum_hs_off; LED_A(SET_HIGH);}
		else
			{signal_sensor_1_status = enum_hs_on; LED_A(SET_LOW);}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

void EXTI2_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line2))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_2) == Bit_SET)
			{signal_sensor_2_status = enum_hs_off; LED_A(SET_HIGH);}
		else
			{signal_sensor_2_status = enum_hs_on; LED_A(SET_LOW);}
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

void EXTI3_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line3))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_3) == Bit_SET)
			{signal_sensor_3_status = enum_hs_off; LED_A(SET_HIGH);}
		else
			{signal_sensor_3_status = enum_hs_on; LED_A(SET_LOW);}
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}

void EXTI4_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line4))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_4) == Bit_SET)
			{signal_sensor_4_status = enum_hs_off; LED_A(SET_HIGH);}
		else
			{signal_sensor_4_status = enum_hs_on; LED_A(SET_LOW);}
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}

void EXTI9_5_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line5))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_5) == Bit_SET)
			{signal_sensor_5_status = enum_hs_off; LED_A(SET_HIGH);}
		else
			{signal_sensor_5_status = enum_hs_on; LED_A(SET_LOW);}
		EXTI_ClearITPendingBit(EXTI_Line5);
	}

	if(EXTI_GetITStatus(EXTI_Line6))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_6) == Bit_SET)
			{signal_sensor_6_status = enum_hs_off; LED_A(SET_HIGH);}
		else
			{signal_sensor_6_status = enum_hs_on; LED_A(SET_LOW);}
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
	
	if(EXTI_GetITStatus(EXTI_Line7))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_7) == Bit_SET)
			{signal_sensor_7_status = enum_hs_off; LED_A(SET_HIGH);}
		else
			{signal_sensor_7_status = enum_hs_on; LED_A(SET_LOW);}
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
	
	if(EXTI_GetITStatus(EXTI_Line8))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_8) == Bit_SET)
			{signal_sensor_8_status = enum_hs_off; LED_A(SET_HIGH);}
		else
			{signal_sensor_8_status = enum_hs_on; LED_A(SET_LOW);}
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
	
	if(EXTI_GetITStatus(EXTI_Line9))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_9) == Bit_SET)
			{signal_sensor_9_status = enum_hs_off; LED_A(SET_HIGH);}
		else
			{signal_sensor_9_status = enum_hs_on; LED_A(SET_LOW);}
		EXTI_ClearITPendingBit(EXTI_Line9);
	}
}

void EXTI15_10_IRQHandler()
{
	
	if(EXTI_GetITStatus(EXTI_Line10))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_10) == Bit_SET)
			{signal_sensor_10_status = enum_hs_off; LED_A(SET_HIGH);}
		else
			{signal_sensor_10_status = enum_hs_on; LED_A(SET_LOW);}
		EXTI_ClearITPendingBit(EXTI_Line10);
	}
	
	if(EXTI_GetITStatus(EXTI_Line11))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_11) == Bit_SET)
			{signal_sensor_11_status = enum_hs_off; LED_A(SET_HIGH);}
		else
			{signal_sensor_11_status = enum_hs_on; LED_A(SET_LOW);}
		EXTI_ClearITPendingBit(EXTI_Line11);
	}
	
	if(EXTI_GetITStatus(EXTI_Line12))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_12) == Bit_SET)
			{signal_sensor_12_status = enum_hs_off; LED_A(SET_HIGH);}
		else
			{signal_sensor_12_status = enum_hs_on; LED_A(SET_LOW);}
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
	
	if(EXTI_GetITStatus(EXTI_Line13))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_13) == Bit_SET)
			{signal_sensor_13_status = enum_hs_off; LED_A(SET_HIGH);}
		else
			{signal_sensor_13_status = enum_hs_on; LED_A(SET_LOW);}
		EXTI_ClearITPendingBit(EXTI_Line13);
	}
	
	if(EXTI_GetITStatus(EXTI_Line14))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_14) == Bit_SET)
			{signal_sensor_14_status = enum_hs_off; LED_A(SET_HIGH);}
		else
			{signal_sensor_14_status = enum_hs_on; LED_A(SET_LOW);}
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
	
	if(EXTI_GetITStatus(EXTI_Line15))
	{
		if(GPIO_ReadInputDataBit(INTERRUPT_GPIO,GPIO_Pin_15) == Bit_SET)
			{signal_sensor_15_status = enum_hs_off; LED_A(SET_HIGH);}
		else
			{signal_sensor_15_status = enum_hs_on; LED_A(SET_LOW);}
		EXTI_ClearITPendingBit(EXTI_Line15);
	}
}
