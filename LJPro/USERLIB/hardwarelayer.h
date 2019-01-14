#ifndef _hardwarelayer_h
#define _hardwarelayer_h

#include <stm32f10x.h>
#include "systick.h"
#include "usart.h"

//////////////////////////////enum//////////////////////////////////////////////////////////////////
typedef enum
{
	//motor
	enum_ht_motor_0, enum_ht_motor_1, enum_ht_motor_2, enum_ht_motor_3,
	//relay
	enum_ht_realy_0, enum_ht_realy_1, enum_ht_realy_2,
	//signal sensor
	enum_ht_signal_sensor_0, enum_ht_signal_sensor_1, enum_ht_signal_sensor_2, enum_ht_signal_sensor_3,
	enum_ht_signal_sensor_4, enum_ht_signal_sensor_5, enum_ht_signal_sensor_6, enum_ht_signal_sensor_7,
	enum_ht_signal_sensor_8, enum_ht_signal_sensor_9, enum_ht_signal_sensor_10, enum_ht_signal_sensor_11,
	enum_ht_signal_sensor_12, enum_ht_signal_sensor_13, enum_ht_signal_sensor_14, enum_ht_signal_sensor_15,
	//data sensor
	enum_ht_data_sensor_0, enum_ht_data_sensor_1
}enum_hardware_type;

typedef enum
{
	enum_hs_none,
	//motor status
	enum_hs_forward, enum_hs_backward, enum_hs_stop,
	//relay status
	enum_hs_open, enum_hs_close,
	//sensor status
	enum_hs_on, enum_hs_off
}enum_hardware_status;


//////////////////////////////declare//////////////////////////////////////////////////////////////////
//////////////////////////////declare//////////////////////////////////////////////////////////////////
//////////////////////////////declare//////////////////////////////////////////////////////////////////
//////////////////////////////declare//////////////////////////////////////////////////////////////////
//////////////////////////////declare//////////////////////////////////////////////////////////////////
void hardware_control_status(enum_hardware_type ht,enum_hardware_status hs);
enum_hardware_status hardware_get_status(enum_hardware_type ht);
unsigned int get_voltage_value(enum_hardware_type ht);
void driver_init(void);
void adc_init(void);
void motor_init(void);
void led_init(void);
void pwm_init(void);
void exti_init(void);


//////////////////////////////define//////////////////////////////////////////////////////////////////
//////////////////////////////define//////////////////////////////////////////////////////////////////
//////////////////////////////define//////////////////////////////////////////////////////////////////
//////////////////////////////define//////////////////////////////////////////////////////////////////
//////////////////////////////define//////////////////////////////////////////////////////////////////
//motor
#define MOTOR_RCC RCC_APB2Periph_GPIOG
#define MOTOR_GPIO GPIOG
#define MOTOR_PIN GPIO_Pin_All

#define MOTOR_0_SET_A_PIN GPIO_Pin_0
#define MOTOR_0_SET_B_PIN GPIO_Pin_1
#define MOTOR_1_SET_A_PIN GPIO_Pin_2
#define MOTOR_1_SET_B_PIN GPIO_Pin_3
#define MOTOR_2_SET_A_PIN GPIO_Pin_4
#define MOTOR_2_SET_B_PIN GPIO_Pin_5
#define MOTOR_3_SET_A_PIN GPIO_Pin_6
#define MOTOR_3_SET_B_PIN GPIO_Pin_7
//relay
#define RELAY_RCC RCC_APB2Periph_GPIOG
#define RELAY_GPIO GPIOG
#define RELAY_PIN GPIO_Pin_All

#define RELAY_0_SET_PIN GPIO_Pin_12
#define RELAY_1_SET_PIN GPIO_Pin_13
#define RELAY_2_SET_PIN GPIO_Pin_14
//signal sensor
#define SIGNAL_SENSOR_RCC RCC_APB2Periph_GPIOD
#define SIGNAL_SENSOR_GPIO GPIOD
#define SIGNAL_SENSOR_PIN GPIO_Pin_All

#define SIGNAL_SENSOR_0_GET_PIN GPIO_Pin_0
#define SIGNAL_SENSOR_1_GET_PIN GPIO_Pin_1
#define SIGNAL_SENSOR_2_GET_PIN GPIO_Pin_2
#define SIGNAL_SENSOR_3_GET_PIN GPIO_Pin_3
#define SIGNAL_SENSOR_4_GET_PIN GPIO_Pin_4
#define SIGNAL_SENSOR_5_GET_PIN GPIO_Pin_5
#define SIGNAL_SENSOR_6_GET_PIN GPIO_Pin_6
#define SIGNAL_SENSOR_7_GET_PIN GPIO_Pin_7
#define SIGNAL_SENSOR_8_GET_PIN GPIO_Pin_8
#define SIGNAL_SENSOR_9_GET_PIN GPIO_Pin_9
#define SIGNAL_SENSOR_10_GET_PIN GPIO_Pin_10
#define SIGNAL_SENSOR_11_GET_PIN GPIO_Pin_11
#define SIGNAL_SENSOR_12_GET_PIN GPIO_Pin_12
#define SIGNAL_SENSOR_13_GET_PIN GPIO_Pin_13
#define SIGNAL_SENSOR_14_GET_PIN GPIO_Pin_14
#define SIGNAL_SENSOR_15_GET_PIN GPIO_Pin_15
//data sensor
#define DATA_SENSOR_RCC RCC_APB2Periph_GPIOF
#define DATA_SENSOR_GPIO GPIOF

#define DATA_SENSOR_0_SET_PIN GPIO_Pin_0
#define DATA_SENSOR_0_GET_PIN GPIO_Pin_1
#define DATA_SENSOR_1_SET_PIN GPIO_Pin_2
#define DATA_SENSOR_1_GET_PIN GPIO_Pin_3

//onboard led
#define LED_RCC RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE
#define LED_GPIO_A GPIOB
#define LED_PIN_A GPIO_Pin_5	//onboard D4
#define LED_GPIO_B GPIOE
#define LED_PIN_B GPIO_Pin_5	//onboard D2

//pwm
#define PWM_RCC RCC_APB2Periph_GPIOC
#define PWM_GPIO GPIOC
#define PWM_PIN GPIO_Pin_7
//interrupt
#define INTERRUPT_RCC SIGNAL_SENSOR_RCC
#define INTERRUPT_GPIO SIGNAL_SENSOR_GPIO
#define INTERRUPT_PIN SIGNAL_SENSOR_PIN
//adc
#define ADC_RCC DATA_SENSOR_RCC
#define ADC_GPIO DATA_SENSOR_GPIO
#define ADC_SET_PIN DATA_SENSOR_0_SET_PIN|DATA_SENSOR_1_SET_PIN
#define ADC_GET_PIN DATA_SENSOR_0_GET_PIN|DATA_SENSOR_1_GET_PIN

//////////////////////////////action//////////////////////////////////////////////////////////////////
//////////////////////////////action//////////////////////////////////////////////////////////////////
//////////////////////////////action//////////////////////////////////////////////////////////////////
//////////////////////////////action//////////////////////////////////////////////////////////////////
//////////////////////////////action//////////////////////////////////////////////////////////////////
//IO
#define SET_HIGH 1
#define SET_LOW 0
//motor
#define MOTOR_0_SET_A(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_0_SET_A_PIN,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_0_SET_A_PIN,Bit_RESET)
#define MOTOR_0_SET_B(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_0_SET_B_PIN,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_0_SET_B_PIN,Bit_RESET)
#define MOTOR_1_SET_A(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_1_SET_A_PIN,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_1_SET_A_PIN,Bit_RESET)
#define MOTOR_1_SET_B(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_1_SET_B_PIN,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_1_SET_B_PIN,Bit_RESET)
#define MOTOR_2_SET_A(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_2_SET_A_PIN,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_2_SET_A_PIN,Bit_RESET)
#define MOTOR_2_SET_B(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_2_SET_B_PIN,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_2_SET_B_PIN,Bit_RESET)
#define MOTOR_3_SET_A(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_3_SET_A_PIN,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_3_SET_A_PIN,Bit_RESET)
#define MOTOR_3_SET_B(a) if(a) GPIO_WriteBit(MOTOR_GPIO,MOTOR_3_SET_B_PIN,Bit_SET); else GPIO_WriteBit(MOTOR_GPIO,MOTOR_3_SET_B_PIN,Bit_RESET)
//relay
#define RELAY_0_SET(a) if(a) GPIO_WriteBit(RELAY_GPIO,RELAY_0_SET_PIN,Bit_SET); else GPIO_WriteBit(RELAY_GPIO,RELAY_0_SET_PIN,Bit_RESET)
#define RELAY_1_SET(a) if(a) GPIO_WriteBit(RELAY_GPIO,RELAY_1_SET_PIN,Bit_SET); else GPIO_WriteBit(RELAY_GPIO,RELAY_1_SET_PIN,Bit_RESET)
#define RELAY_2_SET(a) if(a) GPIO_WriteBit(RELAY_GPIO,RELAY_2_SET_PIN,Bit_SET); else GPIO_WriteBit(RELAY_GPIO,RELAY_2_SET_PIN,Bit_RESET)
//signal sensor
#define SIGNAL_SENSOR_0_GET GPIO_ReadInputDataBit(SIGNAL_SENSOR_GPIO,SIGNAL_SENSOR_0_GET_PIN)
#define SIGNAL_SENSOR_1_GET GPIO_ReadInputDataBit(SIGNAL_SENSOR_GPIO,SIGNAL_SENSOR_1_GET_PIN)
#define SIGNAL_SENSOR_2_GET GPIO_ReadInputDataBit(SIGNAL_SENSOR_GPIO,SIGNAL_SENSOR_2_GET_PIN)
#define SIGNAL_SENSOR_3_GET GPIO_ReadInputDataBit(SIGNAL_SENSOR_GPIO,SIGNAL_SENSOR_3_GET_PIN)
#define SIGNAL_SENSOR_4_GET GPIO_ReadInputDataBit(SIGNAL_SENSOR_GPIO,SIGNAL_SENSOR_4_GET_PIN)
#define SIGNAL_SENSOR_5_GET GPIO_ReadInputDataBit(SIGNAL_SENSOR_GPIO,SIGNAL_SENSOR_5_GET_PIN)
#define SIGNAL_SENSOR_6_GET GPIO_ReadInputDataBit(SIGNAL_SENSOR_GPIO,SIGNAL_SENSOR_6_GET_PIN)
#define SIGNAL_SENSOR_7_GET GPIO_ReadInputDataBit(SIGNAL_SENSOR_GPIO,SIGNAL_SENSOR_7_GET_PIN)
#define SIGNAL_SENSOR_8_GET GPIO_ReadInputDataBit(SIGNAL_SENSOR_GPIO,SIGNAL_SENSOR_8_GET_PIN)
#define SIGNAL_SENSOR_9_GET GPIO_ReadInputDataBit(SIGNAL_SENSOR_GPIO,SIGNAL_SENSOR_9_GET_PIN)
#define SIGNAL_SENSOR_10_GET GPIO_ReadInputDataBit(SIGNAL_SENSOR_GPIO,SIGNAL_SENSOR_10_GET_PIN)
#define SIGNAL_SENSOR_11_GET GPIO_ReadInputDataBit(SIGNAL_SENSOR_GPIO,SIGNAL_SENSOR_11_GET_PIN)
#define SIGNAL_SENSOR_12_GET GPIO_ReadInputDataBit(SIGNAL_SENSOR_GPIO,SIGNAL_SENSOR_12_GET_PIN)
#define SIGNAL_SENSOR_13_GET GPIO_ReadInputDataBit(SIGNAL_SENSOR_GPIO,SIGNAL_SENSOR_13_GET_PIN)
#define SIGNAL_SENSOR_14_GET GPIO_ReadInputDataBit(SIGNAL_SENSOR_GPIO,SIGNAL_SENSOR_14_GET_PIN)
#define SIGNAL_SENSOR_15_GET GPIO_ReadInputDataBit(SIGNAL_SENSOR_GPIO,SIGNAL_SENSOR_15_GET_PIN)
//data sensor
#define DATA_SENSOR_0_SET(a) if(a) GPIO_WriteBit(DATA_SENSOR_GPIO,DATA_SENSOR_0_SET_PIN,Bit_SET); else GPIO_WriteBit(DATA_SENSOR_GPIO,DATA_SENSOR_0_SET_PIN,Bit_RESET)
#define DATA_SENSOR_0_GET GPIO_ReadInputDataBit(DATA_SENSOR_GPIO,DATA_SENSOR_0_GET_PIN)
#define DATA_SENSOR_1_SET(a) if(a) GPIO_WriteBit(DATA_SENSOR_GPIO,DATA_SENSOR_1_SET_PIN,Bit_SET); else GPIO_WriteBit(DATA_SENSOR_GPIO,DATA_SENSOR_1_SET_PIN,Bit_RESET)
#define DATA_SENSOR_1_GET GPIO_ReadInputDataBit(DATA_SENSOR_GPIO,DATA_SENSOR_1_GET_PIN)

//onboard led
#define LED_A(a) if(a) GPIO_WriteBit(LED_GPIO_A,LED_PIN_A,Bit_SET); else GPIO_WriteBit(LED_GPIO_A,LED_PIN_A,Bit_RESET)
#define LED_A_REVERSE GPIO_WriteBit(LED_GPIO_A,LED_PIN_A,(BitAction)(1-GPIO_ReadInputDataBit(LED_GPIO_A,LED_PIN_A)));
#define LED_B(a) if(a) GPIO_WriteBit(LED_GPIO_B,LED_PIN_B,Bit_SET); else GPIO_WriteBit(LED_GPIO_B,LED_PIN_B,Bit_RESET)
#define LED_B_REVERSE GPIO_WriteBit(LED_GPIO_B,LED_PIN_B,(BitAction)(1-GPIO_ReadInputDataBit(LED_GPIO_B,LED_PIN_B)));

//pwm
#define PWM_0_OUTPUT_REVERSE GPIO_WriteBit(PWM_GPIO,PWM_PIN,(BitAction)(1-GPIO_ReadInputDataBit(PWM_GPIO,PWM_PIN)));

#endif
