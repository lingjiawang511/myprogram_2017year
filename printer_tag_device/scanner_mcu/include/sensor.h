#ifndef __SENSOR_H
#define __SENSOR_H

#include "stm32f10x.h"

#define		SENSOR1_IO					GPIO_Pin_11
#define		SENSOR1_PORT				GPIOA
#define   SENSOR1_RCC					RCC_APB2Periph_GPIOA
#define		SENSOR2_IO					GPIO_Pin_12
#define		SENSOR2_PORT				GPIOA
#define   SENSOR2_RCC					RCC_APB2Periph_GPIOA
#define		SENSOR3_IO					GPIO_Pin_7
#define		SENSOR3_PORT				GPIOB
#define   SENSOR3_RCC					RCC_APB2Periph_GPIOB
#define		SENSOR4_IO					GPIO_Pin_6
#define		SENSOR4_PORT				GPIOB
#define   SENSOR4_RCC					RCC_APB2Periph_GPIOB
#define		SENSOR5_IO					GPIO_Pin_5
#define		SENSOR5_PORT				GPIOB
#define   SENSOR5_RCC					RCC_APB2Periph_GPIOB
#define		SENSOR6_IO					GPIO_Pin_0
#define		SENSOR6_PORT				GPIOB
#define   SENSOR6_RCC					RCC_APB2Periph_GPIOB


#define   READ_SENSOR1_CHECK   			GPIO_ReadInputDataBit(SENSOR1_PORT,SENSOR1_IO)
#define   READ_SENSOR2_CHECK  			GPIO_ReadInputDataBit(SENSOR2_PORT,SENSOR2_IO)
#define   READ_SENSOR3_CHECK   			GPIO_ReadInputDataBit(SENSOR3_PORT,SENSOR3_IO)
#define   READ_SENSOR4_CHECK  			GPIO_ReadInputDataBit(SENSOR4_PORT,SENSOR4_IO)
#define   READ_SENSOR5_CHECK   			GPIO_ReadInputDataBit(SENSOR5_PORT,SENSOR5_IO)
#define   READ_SENSOR6_CHECK  			GPIO_ReadInputDataBit(SENSOR6_PORT,SENSOR6_IO)

#define   RESET_SENSOR_CHECK_VALUE  do{Sonser.sensor1.sensor_check_value = 0;Sonser.sensor2.sensor_check_value = 0;\
																			Sonser.sensor3.sensor_check_value = 0;Sonser.sensor4.sensor_check_value = 0;\
																			Sonser.sensor5.sensor_check_value = 0;Sonser.sensor6.sensor_check_value = 0;}while(0);


typedef struct{
	u8 sensor_state;
	u8 sensor_check_value;
	u16 sensor_time;
}Sensor_Control_Type;

typedef struct{
	Sensor_Control_Type sensor1;
	Sensor_Control_Type sensor2;
	Sensor_Control_Type sensor3;
	Sensor_Control_Type sensor4;
	Sensor_Control_Type sensor5;
	Sensor_Control_Type sensor6;
}Sensor_Type;


extern u8 Sensor_State;
extern Sensor_Type Sonser;

void SENSOR_GPIO_Config(void);
void Sensor_check(void );



#endif




