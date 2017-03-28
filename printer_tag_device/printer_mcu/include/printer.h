#ifndef __PRINTER_H
#define __PRINTER_H

#include "stm32f10x.h"

#define				PRINTER_ERR_IO					 GPIO_Pin_13
#define				PRINTER_ERR_PORT			   GPIOB
#define				PRINTER_ERR_RCC				   RCC_APB2Periph_GPIOB
#define				PRINTER_END_IO					 GPIO_Pin_14
#define				PRINTER_END_PORT				 GPIOB
#define				PRINTER_END_RCC			     RCC_APB2Periph_GPIOB

#define				PRINTER_INLINE_IO				 GPIO_Pin_11
#define				PRINTER_INLINE_PORT			 GPIOB
#define				PRINTER_INLINE_RCC			 RCC_APB2Periph_GPIOB
#define				PRINTER_COEND_IO				 GPIO_Pin_12
#define				PRINTER_COEND_PORT			 GPIOB
#define				PRINTER_COEND_RCC			   RCC_APB2Periph_GPIOB

#define				PRINTER_TAGEND_IO				 GPIO_Pin_15
#define				PRINTER_TAGEND_PORT			 GPIOB
#define				PRINTER_TAGEND_RCC			 RCC_APB2Periph_GPIOB
#define				PRINTER_COLESS_IO				 GPIO_Pin_10
#define				PRINTER_COLESS_PORT			 GPIOB
#define				PRINTER_COLESS_RCC			 RCC_APB2Periph_GPIOB

#define       READ_PRINTER_ERR    		  GPIO_ReadInputDataBit(PRINTER_ERR_PORT,PRINTER_ERR_IO) //返回的是一个字节，读的是一个位
#define       READ_PRINTER_END    		  GPIO_ReadInputDataBit(PRINTER_END_PORT,PRINTER_END_IO) //返回的是一个字节，读的是一个位
#define       READ_PRINTER_INLINE   		GPIO_ReadInputDataBit(PRINTER_INLINE_PORT,PRINTER_INLINE_IO) //返回的是一个字节，读的是一个位
#define       READ_PRINTER_COEND    		GPIO_ReadInputDataBit(PRINTER_COEND_PORT,PRINTER_COEND_IO) //返回的是一个字节，读的是一个位
#define       READ_PRINTER_TAGEND    	  GPIO_ReadInputDataBit(PRINTER_TAGEND_PORT,PRINTER_TAGEND_IO) //返回的是一个字节，读的是一个位
#define       READ_PRINTER_COLESS   		GPIO_ReadInputDataBit(PRINTER_COLESS_PORT,PRINTER_COLESS_IO) //返回的是一个字节，读的是一个位

#define				PRINTER_START_IO				  GPIO_Pin_5
#define				PRINTER_START_PORT			  GPIOC
#define				PRINTER_START_RCC			    RCC_APB2Periph_GPIOC
#define				PRINTER_RESTART_IO				GPIO_Pin_4
#define				PRINTER_RESTART_PORT			GPIOC
#define				PRINTER_RESTART_RCC			  RCC_APB2Periph_GPIOC

//#define       PRINTER_START_ON   		GPIO_SetBits(PRINTER_START_PORT, PRINTER_START_IO)
//#define       PRINTER_START_OFF  			GPIO_ResetBits(PRINTER_START_PORT, PRINTER_START_IO)
//#define       PRINTER_RESTART_ON   	GPIO_SetBits(PRINTER_RESTART_PORT, PRINTER_RESTART_IO)
//#define       PRINTER_RESTART_OFF 	 	 	GPIO_ResetBits(PRINTER_RESTART_PORT,PRINTER_RESTART_IO)

#define       PRINTER_START_ON   				GPIO_SetBits(PRINTER_START_PORT, PRINTER_START_IO)
#define       PRINTER_START_OFF  				GPIO_ResetBits(PRINTER_START_PORT, PRINTER_START_IO)
#define       PRINTER_RESTART_ON   			GPIO_SetBits(PRINTER_RESTART_PORT, PRINTER_RESTART_IO)
#define       PRINTER_RESTART_OFF 	 	 	GPIO_ResetBits(PRINTER_RESTART_PORT,PRINTER_RESTART_IO)





void Printer_GPIO_Config(void);
void Printer_Control(void);


#endif








