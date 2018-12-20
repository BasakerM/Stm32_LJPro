#ifndef _driver_h
#define _driver_h

#include <stm32f10x.h>
#include "systick.h"
#include "usart.h"

enum motor_device{motor_metal = 0,motor_paper = 1,motor_bottle_k = 2,motor_bottle_p = 3};
enum motor_run{run_z = 0,run_f = 1,run_s = 2};
enum door_oc{open = 0,close = 1,ing = 2};
enum device_of{on = 0,off = 1};
//中断
#define INTERRUPT_RCC RCC_APB2Periph_GPIOD
#define INTERRUPT_GPIO GPIOD
#define INTERRUPT_PIN GPIO_Pin_All
//板载led
#define LED_RCC RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE
#define LED_GPIO_A GPIOB
#define LED_PIN_A GPIO_Pin_5
#define LED_GPIO_B GPIOE
#define LED_PIN_B GPIO_Pin_5
//电机
#define MOTOR_RCC RCC_APB2Periph_GPIOG
#define MOTOR_GPIO GPIOG
#define MOTOR_PIN GPIO_Pin_All

//电平宏
#define HIGH 1
#define LOW 0
//金属电机
#define MOTOR_METAL_PIN_OUT1 GPIO_Pin_0
#define MOTOR_METAL_PIN_OUT2 GPIO_Pin_1
#define MOTOR_METAL_OUT1(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_METAL_PIN_OUT1,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_METAL_PIN_OUT1,Bit_RESET)
#define MOTOR_METAL_OUT2(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_METAL_PIN_OUT2,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_METAL_PIN_OUT2,Bit_RESET)
//纸类电机
#define MOTOR_PAPER_PIN_OUT1 GPIO_Pin_2
#define MOTOR_PAPER_PIN_OUT2 GPIO_Pin_3
#define MOTOR_PAPER_OUT1(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_PAPER_PIN_OUT1,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_PAPER_PIN_OUT1,Bit_RESET)
#define MOTOR_PAPER_OUT2(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_PAPER_PIN_OUT2,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_PAPER_PIN_OUT2,Bit_RESET)
//瓶子开门
#define MOTOR_BOTTLE_K_PIN_OUT1 GPIO_Pin_8
#define MOTOR_BOTTLE_K_PIN_OUT2 GPIO_Pin_9
#define MOTOR_BOTTLE_K_OUT1(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_BOTTLE_K_PIN_OUT1,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_BOTTLE_K_PIN_OUT1,Bit_RESET)
#define MOTOR_BOTTLE_K_OUT2(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_BOTTLE_K_PIN_OUT2,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_BOTTLE_K_PIN_OUT2,Bit_RESET)



//开关宏
#define ON 0
#define OFF 1
//led开关宏
//将开关宏作为参数填入即可控制板载led的开关
#define LED_A(a) if(a) GPIO_WriteBit(LED_GPIO_A,LED_PIN_A,Bit_SET); else GPIO_WriteBit(LED_GPIO_A,LED_PIN_A,Bit_RESET)
#define LED_B(a) if(a) GPIO_WriteBit(LED_GPIO_B,LED_PIN_B,Bit_SET); else GPIO_WriteBit(LED_GPIO_B,LED_PIN_B,Bit_RESET)

void driver_init(void);
void motor_ctrl(enum motor_device device,enum motor_run mrun);
enum door_oc door_bottle_k_getstatus(void);
void motor_init(void);
void led_init(void);
void exti_init(void);

#endif
