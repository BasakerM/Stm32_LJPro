#ifndef _driver_h
#define _driver_h

#include <stm32f10x.h>
#include "systick.h"
#include "usart.h"

enum device_power{on = 0,off = 1};	//设备电源(通电、断电)
enum motor_device{motor_metal = 0,motor_paper = 1,motor_bottle_k = 2,motor_bottle_p = 3,lock_metal = 4,lock_paper = 5,lock_bottle = 6};	//电机设备类型(金属电机、纸类电机、瓶子开门电机、瓶子皮带电机、金属电控锁、纸类电控锁、瓶子电控锁)
enum motor_status{run_z = 0,run_f = 1,run_s = 2};	//电机的状态(正转、反转、停止)
enum door_device{door_metal_user = 0,door_metal_manage = 1,door_paper_user = 2,door_paper_manage = 3,door_bottle_user = 4,door_bottle_manage = 5};	//门设备类型(金属用户门、金属管理员门，纸类用户门，纸类管理员门、瓶子用户门，瓶子管理员门)
enum door_status{open = 0,close = 1,ing = 2};	//门的状态(开、关、介于开关之间)

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
//电机(开门,金属,纸类)
#define MOTOR_RCC RCC_APB2Periph_GPIOG
#define MOTOR_GPIO GPIOG
#define MOTOR_PIN GPIO_Pin_All
#define MOTOR_METAL_PIN_OUT1 GPIO_Pin_0//金属电机引脚
#define MOTOR_METAL_PIN_OUT2 GPIO_Pin_1
#define MOTOR_PAPER_PIN_OUT1 GPIO_Pin_2//纸类电机引脚
#define MOTOR_PAPER_PIN_OUT2 GPIO_Pin_3
#define MOTOR_BOTTLE_K_PIN_OUT1 GPIO_Pin_8//瓶子开门引脚
#define MOTOR_BOTTLE_K_PIN_OUT2 GPIO_Pin_9
//皮带电机
#define MOTOR_PD_RCC RCC_APB2Periph_GPIOF
#define MOTOR_PD_GPIO GPIOF
#define MOTOR_PD_PIN GPIO_Pin_All

//////////////////////////////控制/////////////////////////////////
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
//板载led
#define LED_A(a) if(a) GPIO_WriteBit(LED_GPIO_A,LED_PIN_A,Bit_SET); else GPIO_WriteBit(LED_GPIO_A,LED_PIN_A,Bit_RESET)
#define LED_B(a) if(a) GPIO_WriteBit(LED_GPIO_B,LED_PIN_B,Bit_SET); else GPIO_WriteBit(LED_GPIO_B,LED_PIN_B,Bit_RESET)

//////////////////////////////声明/////////////////////////////////
void motor_ctrl(enum motor_device device,enum motor_status mrun);
enum door_status door_status_get(enum door_device door);
enum motor_device door_to_motor(enum door_device door);
void driver_init(void);
void motor_init(void);
void led_init(void);
void exti_init(void);

#endif
