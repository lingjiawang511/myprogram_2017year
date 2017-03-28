#ifndef __LOCK_H
#define __LOCK_H

#include "stm32f10x.h"

#define		LOCK1_IO					GPIO_Pin_12
#define		LOCK1_PORT				GPIOB
#define   LOCK1_RCC					RCC_APB2Periph_GPIOB
#define		LOCK2_IO					GPIO_Pin_13
#define		LOCK2_PORT				GPIOB
#define   LOCK2_RCC					RCC_APB2Periph_GPIOB
#define		LOCK3_IO					GPIO_Pin_14
#define		LOCK3_PORT				GPIOB
#define   LOCK3_RCC					RCC_APB2Periph_GPIOB
#define		LOCK4_IO					GPIO_Pin_15
#define		LOCK4_PORT				GPIOB
#define   LOCK4_RCC					RCC_APB2Periph_GPIOB

#define   LOCK1_OFF   			GPIO_ResetBits(LOCK1_PORT, LOCK1_IO)
#define   LOCK1_ON  				GPIO_SetBits(LOCK1_PORT, LOCK1_IO)
#define   LOCK2_OFF   			GPIO_ResetBits(LOCK2_PORT, LOCK2_IO)
#define   LOCK2_ON 	 				GPIO_SetBits(LOCK2_PORT, LOCK2_IO)
#define   LOCK3_OFF   			GPIO_ResetBits(LOCK3_PORT, LOCK3_IO)
#define   LOCK3_ON  				GPIO_SetBits(LOCK3_PORT, LOCK3_IO)
#define   LOCK4_OFF   			GPIO_ResetBits(LOCK4_PORT, LOCK4_IO)
#define   LOCK4_ON 	 				GPIO_SetBits(LOCK4_PORT, LOCK4_IO)

#define		LOCK1_CHECK_IO					GPIO_Pin_10
#define		LOCK1_CHECK_PORT				GPIOB
#define   LOCK1_CHECK_RCC					RCC_APB2Periph_GPIOB
#define		LOCK2_CHECK_IO					GPIO_Pin_11
#define		LOCK2_CHECK_PORT				GPIOB
#define   LOCK2_CHECK_RCC					RCC_APB2Periph_GPIOB
#define		LOCK3_CHECK_IO					GPIO_Pin_8
#define		LOCK3_CHECK_PORT				GPIOB
#define   LOCK3_CHECK_RCC					RCC_APB2Periph_GPIOB
#define		LOCK4_CHECK_IO					GPIO_Pin_9
#define		LOCK4_CHECK_PORT				GPIOB
#define   LOCK4_CHECK_RCC					RCC_APB2Periph_GPIOB

#define   READ_LOCK1_CHECK   			GPIO_ReadInputDataBit(LOCK1_CHECK_PORT,LOCK1_CHECK_IO)
#define   READ_LOCK2_CHECK  			GPIO_ReadInputDataBit(LOCK2_CHECK_PORT,LOCK2_CHECK_IO)
#define   READ_LOCK3_CHECK   			GPIO_ReadInputDataBit(LOCK3_CHECK_PORT,LOCK3_CHECK_IO)
#define   READ_LOCK4_CHECK  			GPIO_ReadInputDataBit(LOCK4_CHECK_PORT,LOCK4_CHECK_IO)

#define		LOCK1_LIGHT1_IO					GPIO_Pin_4
#define		LOCK1_LIGHT1_PORT				GPIOA
#define   LOCK1_LIGHT1_RCC				RCC_APB2Periph_GPIOA
//LIGHT2 当作灯的亮度调节，暂时不修改名称
#define		LOCK1_LIGHT2_IO					GPIO_Pin_5
#define		LOCK1_LIGHT2_PORT				GPIOA
#define   LOCK1_LIGHT2_RCC				RCC_APB2Periph_GPIOA

//#define		LOCK2_LIGHT1_IO					GPIO_Pin_4
//#define		LOCK2_LIGHT1_PORT				GPIOA
//#define   LOCK2_LIGHT1_RCC				RCC_APB2Periph_GPIOA
//#define		LOCK2_LIGHT2_IO					GPIO_Pin_6
//#define		LOCK2_LIGHT2_PORT				GPIOA
//#define   LOCK2_LIGHT2_RCC				RCC_APB2Periph_GPIOA

#define   LOCK1_LIGHT1_OFF   			GPIO_ResetBits(LOCK1_LIGHT1_PORT, LOCK1_LIGHT1_IO)
#define   LOCK1_LIGHT1_ON  				GPIO_SetBits(LOCK1_LIGHT1_PORT, LOCK1_LIGHT1_IO)
#define   LOCK1_LIGHT2_OFF   			GPIO_ResetBits(LOCK1_LIGHT2_PORT, LOCK1_LIGHT2_IO)
#define   LOCK1_LIGHT2_ON  				GPIO_SetBits(LOCK1_LIGHT2_PORT, LOCK1_LIGHT2_IO)

//#define   LOCK2_LIGHT1_OFF   			GPIO_ResetBits(LOCK2_LIGHT1_PORT, LOCK2_LIGHT1_IO)
//#define   LOCK2_LIGHT1_ON  				GPIO_SetBits(LOCK2_LIGHT1_PORT, LOCK2_LIGHT1_IO)
//#define   LOCK2_LIGHT2_OFF   			GPIO_ResetBits(LOCK2_LIGHT2_PORT, LOCK2_LIGHT2_IO)
//#define   LOCK2_LIGHT2_ON  				GPIO_SetBits(LOCK2_LIGHT2_PORT, LOCK2_LIGHT2_IO)


#define   LOCK1_LIGHT_OFF()   		{LOCK1_LIGHT1_OFF;LOCK1_LIGHT2_OFF;}
#define   LOCK1_LIGHT_ON_H()  		{LOCK1_LIGHT1_ON;LOCK1_LIGHT2_OFF;}	
#define   LOCK1_LIGHT_ON_L()  		{LOCK1_LIGHT1_ON;LOCK1_LIGHT2_ON;}
//#define   LOCK2_LIGHT_OFF()   		{LOCK2_LIGHT1_OFF;LOCK2_LIGHT2_OFF;}	
//#define   LOCK2_LIGHT_ON() 	 			{LOCK2_LIGHT1_ON;LOCK2_LIGHT2_ON;}		

#define   LOCK_TIME			400
#define   RESET_LOCK_CHECK_STATE  do{Lock.lock1.lock_check_state =0;Lock.lock2.lock_check_state =0;\
																		Lock.lock3.lock_check_state =0;Lock.lock4.lock_check_state =0;}while(0);


typedef struct{
	u8 lock_state;
	u16 lock_time;
	u8 lock_check_state;
	u8 lock_check_value;
}Lock_Control_Type;

typedef struct{
	Lock_Control_Type lock1;
	Lock_Control_Type lock2;
	Lock_Control_Type lock3;
	Lock_Control_Type lock4;
}Lock_Type;



extern Lock_Type Lock;
extern u8 Check_State;
extern u8 Lock_Check_state;

void LOCK_GPIO_Config(void);
void Lock_control(void );



#endif




