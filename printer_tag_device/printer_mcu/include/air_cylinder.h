#ifndef __AIR_CYLINDER_H
#define __AIR_CYLINDER_H

#include "stm32f10x.h"

#define				UPPER_REACH_IO					 GPIO_Pin_8
#define				UPPER_REACH_PORT			   GPIOC
#define				UPPER_REACH_RCC				   RCC_APB2Periph_GPIOC
#define				FIT_REACH_IO						 GPIO_Pin_9
#define				FIT_REACH_PORT					 GPIOC
#define				FIT_REACH_RCC			     	 RCC_APB2Periph_GPIOC

#define				FLUID_BAG_IO				 		 GPIO_Pin_7
#define				FLUID_BAG_PORT			     GPIOC
#define				FLUID_BAG_RCC			       RCC_APB2Periph_GPIOC
#define				SCANNER_IO				 			 GPIO_Pin_6
#define				SCANNER_PORT						 GPIOC
#define				SCANNER_RCC			  			 RCC_APB2Periph_GPIOC


#define       READ_UPPER_REACH   		  GPIO_ReadInputDataBit(UPPER_REACH_PORT,UPPER_REACH_IO) //返回的是一个字节，读的是一个位
#define       READ_FIT_REACH    		  GPIO_ReadInputDataBit(FIT_REACH_PORT,FIT_REACH_IO) //返回的是一个字节，读的是一个位
#define       READ_FLUID_BAG   				GPIO_ReadInputDataBit(FLUID_BAG_PORT,FLUID_BAG_IO) //返回的是一个字节，读的是一个位
#define       READ_SCANNER    				GPIO_ReadInputDataBit(SCANNER_PORT,SCANNER_IO) //返回的是一个字节，读的是一个位

#define				AIR_CYLINDER_IO				  GPIO_Pin_11
#define				AIR_CYLINDER_PORT			  GPIOC
#define				AIR_CYLINDER_RCC			  RCC_APB2Periph_GPIOC
#define				AIR_BLOW_IO				      GPIO_Pin_10
#define				AIR_BLOW_PORT			      GPIOC
#define				AIR_BLOW_RCC			      RCC_APB2Periph_GPIOC
#define				VACUUM_IO				     	  GPIO_Pin_12
#define				VACUUM_PORT			     	  GPIOC
#define				VACUUM_RCC			      	RCC_APB2Periph_GPIOC

#define       AIR_CYLINDER_DOWM   		GPIO_SetBits(AIR_CYLINDER_PORT, AIR_CYLINDER_IO)
#define       AIR_CYLINDER_UP  				GPIO_ResetBits(AIR_CYLINDER_PORT, AIR_CYLINDER_IO)
#define       AIR_BLOW_ON   					GPIO_SetBits(AIR_BLOW_PORT, AIR_BLOW_IO)
#define       AIR_BLOW_OFF 	 	 				GPIO_ResetBits(AIR_BLOW_PORT,AIR_BLOW_IO)
#define       VACUUM_ON   						GPIO_SetBits(VACUUM_PORT, VACUUM_IO)
#define       VACUUM_OFF 	 	 					GPIO_ResetBits(VACUUM_PORT,VACUUM_IO)
	



void Air_Cylinder_GPIO_Config(void);
void Air_Cylinder_Control(void);

#endif 









