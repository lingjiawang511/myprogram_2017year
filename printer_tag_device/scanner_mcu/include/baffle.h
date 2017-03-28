#ifndef __BAFFLE_H
#define __BAFFLE_H

#include "stm32f10x.h"

//baffle_inter 先定义为错误位置，baffle_outer定义为确认位置,BAFFLE_OFF失电是错误位置

#define				BAFFLE_OUTER_IO					 GPIO_Pin_10
#define				BAFFLE_OUTER_PORT			   GPIOB
#define				BAFFLE_OUTER_RCC				 RCC_APB2Periph_GPIOB
#define				BAFFLE_INTER_IO					 GPIO_Pin_11
#define				BAFFLE_INTER_PORT				 GPIOB
#define				BAFFLE_INTER_RCC			   RCC_APB2Periph_GPIOB

#define				SCANNER_IO				 			 GPIO_Pin_0
#define				SCANNER_PORT						 GPIOB
#define				SCANNER_RCC			  			 RCC_APB2Periph_GPIOB


#define       READ_BAFFLE_OUTER  		   GPIO_ReadInputDataBit(BAFFLE_OUTER_PORT,BAFFLE_OUTER_IO) //返回的是一个字节，读的是一个位
#define       READ_BAFFLE_INTER    		 GPIO_ReadInputDataBit(BAFFLE_INTER_PORT,BAFFLE_INTER_IO) //返回的是一个字节，读的是一个位
#define       READ_SCANNER    				 GPIO_ReadInputDataBit(SCANNER_PORT,SCANNER_IO) //返回的是一个字节，读的是一个位

#define				BAFFLE_IO				 				 GPIO_Pin_6
#define				BAFFLE_PORT			 				 GPIOB
#define				BAFFLE_RCC			  			 RCC_APB2Periph_GPIOB


#define       BAFFLE_INTER   					GPIO_SetBits(BAFFLE_PORT, BAFFLE_IO)
#define       BAFFLE_OUTER 	 	 				GPIO_ResetBits(BAFFLE_PORT,BAFFLE_IO)

	



void Baffle_GPIO_Config(void);
void Baffle_Control_Process(void);
void Baffle_Time_Irq(void);
#endif 
