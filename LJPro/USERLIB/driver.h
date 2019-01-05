#ifndef _driver_h
#define _driver_h

#include <stm32f10x.h>
#include "systick.h"
#include "usart.h"

//////////////////////////////枚举/////////////////////////////////
enum enum_event
{
	event_none = 0,event_bottle_opendoor = 1,event_bottle_closedoor = 2,
	event_bottle_put = 3,event_bottle_scanfcode = 4,event_bottle_ack = 5,event_bottle_recycle = 6,event_bottle_fail = 7,
	event_metal_opendoor = 8,event_metal_closedoor = 9,event_metal_put = 10,event_metal_recycle = 11,event_metal_weigh = 12,
	event_paper_opendoor = 13,event_paper_closedoor = 14,event_paper_put = 15,event_paper_recycle = 16,event_paper_weigh = 17
};

enum enum_device
{
	bottle_motor_door = 0,bottle_motor_recycle = 1,bottle_lock = 2,
	bottle_sensor_opendoor = 3,bottle_sensor_closedoor = 4,
	bottle_sensor_one = 5,bottle_sensor_two = 6,bottle_sensor_three = 7,
	metal_motor = 8,metal_lock = 9,metal_sensor = 10,
	paper_motor = 11,paper_lock = 12,paper_sensor = 13
};

enum enum_status
{
	on = 0,off = 1,
	open = 2,close = 3,
	run_z = 4,run_f = 5,run_s = 6,
	success = 7,fail = 8,exeing = 9
};

//////////////////////////////声明/////////////////////////////////
void motor_ctrl(enum enum_device device,enum enum_status mrun);
enum enum_status device_status_get(enum enum_device device);
//void motor_pd_ctrl(enum enum_status mrun);
unsigned int get_weight(void);
void driver_init(void);
void hx711_init(void);
void motor_init(void);
void led_init(void);
void tim_init(void);
void exti_init(void);

//////////////////////////////定义/////////////////////////////////
//中断
#define INTERRUPT_RCC RCC_APB2Periph_GPIOD
#define INTERRUPT_GPIO GPIOD
#define INTERRUPT_PIN GPIO_Pin_All
//板载led
#define LED_RCC RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE
#define LED_GPIO_A GPIOB
#define LED_PIN_A GPIO_Pin_5	//板载D4
#define LED_GPIO_B GPIOE
#define LED_PIN_B GPIO_Pin_5	//板载D2
//电机控制信号(开门,金属,纸类，皮带)
#define MOTOR_RCC RCC_APB2Periph_GPIOG
#define MOTOR_GPIO GPIOG
#define MOTOR_PIN GPIO_Pin_All
#define MOTOR_METAL_PIN_OUT1 GPIO_Pin_0//金属电机引脚
#define MOTOR_METAL_PIN_OUT2 GPIO_Pin_1
#define MOTOR_PAPER_PIN_OUT1 GPIO_Pin_2//纸类电机引脚
#define MOTOR_PAPER_PIN_OUT2 GPIO_Pin_3
#define MOTOR_BOTTLE_K_PIN_OUT1 GPIO_Pin_4//瓶子开门引脚
#define MOTOR_BOTTLE_K_PIN_OUT2 GPIO_Pin_5
#define MOTOR_BOTTLE_P_PIN_OUT1 GPIO_Pin_6//瓶子皮带引脚
#define MOTOR_BOTTLE_P_PIN_OUT2 GPIO_Pin_7

//电机调速信号(皮带)
#define MOTOR_PD_RCC RCC_APB2Periph_GPIOC
#define MOTOR_PD_GPIO GPIOC
#define MOTOR_PD_PIN GPIO_Pin_7

//HX711
#define HX711_RCC RCC_APB2Periph_GPIOE
#define HX711_GPIO GPIOE
#define HX711_CK_PIN GPIO_Pin_0
#define HX711_DO_PIN GPIO_Pin_1

////////////////////////////// IO 操作/////////////////////////////////
//电平宏
#define HIGH 1
#define LOW 0
//金属电机
#define MOTOR_METAL_OUT1(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_METAL_PIN_OUT1,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_METAL_PIN_OUT1,Bit_RESET)
#define MOTOR_METAL_OUT2(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_METAL_PIN_OUT2,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_METAL_PIN_OUT2,Bit_RESET)
//纸类电机
#define MOTOR_PAPER_OUT1(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_PAPER_PIN_OUT1,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_PAPER_PIN_OUT1,Bit_RESET)
#define MOTOR_PAPER_OUT2(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_PAPER_PIN_OUT2,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_PAPER_PIN_OUT2,Bit_RESET)
//瓶子开门
#define MOTOR_BOTTLE_K_OUT1(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_BOTTLE_K_PIN_OUT1,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_BOTTLE_K_PIN_OUT1,Bit_RESET)
#define MOTOR_BOTTLE_K_OUT2(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_BOTTLE_K_PIN_OUT2,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_BOTTLE_K_PIN_OUT2,Bit_RESET)
//瓶子皮带
#define MOTOR_BOTTLE_P_OUT1(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_BOTTLE_P_PIN_OUT1,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_BOTTLE_P_PIN_OUT1,Bit_RESET)
#define MOTOR_BOTTLE_P_OUT2(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_BOTTLE_P_PIN_OUT2,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_BOTTLE_P_PIN_OUT2,Bit_RESET)
#define MOTOR_BOTTLE_P_SPEED_REVERSE GPIO_WriteBit(MOTOR_PD_GPIO,MOTOR_PD_PIN,(BitAction)(1-GPIO_ReadOutputDataBit(MOTOR_PD_GPIO,MOTOR_PD_PIN)))
//板载led
#define LED_A(a) if(a) GPIO_WriteBit(LED_GPIO_A,LED_PIN_A,Bit_SET); else GPIO_WriteBit(LED_GPIO_A,LED_PIN_A,Bit_RESET)
#define LED_B(a) if(a) GPIO_WriteBit(LED_GPIO_B,LED_PIN_B,Bit_SET); else GPIO_WriteBit(LED_GPIO_B,LED_PIN_B,Bit_RESET)
//HX711
#define HX711_CK_OUT(a) if(a) GPIO_WriteBit(HX711_GPIO,HX711_CK_PIN,Bit_SET); else GPIO_WriteBit(HX711_GPIO,HX711_CK_PIN,Bit_RESET)
#define HX711_DO_GET GPIO_ReadInputDataBit(HX711_GPIO,HX711_DO_PIN)


#endif
