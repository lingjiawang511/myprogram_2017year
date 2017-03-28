#ifndef __BELT_H
#define __BELT_H

#include "stm32f10x.h"
#include "delay.h"

#define	BELT_SPEED1_IO				GPIO_Pin_6
#define	BELT_SPEED1_PORT			GPIOB
#define	BELT_SPEED2_IO				GPIO_Pin_12
#define	BELT_SPEED2_PORT			GPIOC
#define	BELT_SPEED3_IO				GPIO_Pin_2
#define	BELT_SPEED3_PORT			GPIOD
#define	BELT_DIR_IO						GPIO_Pin_7
#define	BELT_DIR_PORT					GPIOB
#define	BELT_ERR_IO						GPIO_Pin_5
#define	BELT_ERR_PORT					GPIOB

#define BELT_SPEED1_SET  			GPIO_SetBits(BELT_SPEED1_PORT, BELT_SPEED1_IO)
#define BELT_SPEED1_RESET 		GPIO_ResetBits(BELT_SPEED1_PORT, BELT_SPEED1_IO)
#define BELT_SPEED2_SET  			GPIO_SetBits(BELT_SPEED2_PORT, BELT_SPEED2_IO)
#define BELT_SPEED2_RESET 		GPIO_ResetBits(BELT_SPEED2_PORT, BELT_SPEED2_IO)
#define BELT_SPEED3_SET  			GPIO_SetBits(BELT_SPEED3_PORT, BELT_SPEED3_IO)
#define BELT_SPEED3_RESET 		GPIO_ResetBits(BELT_SPEED3_PORT, BELT_SPEED3_IO)
#define BELT_DIR_SET  				GPIO_SetBits(BELT_DIR_PORT, BELT_DIR_IO)
#define BELT_DIR_RESET 				GPIO_ResetBits(BELT_DIR_PORT, BELT_DIR_IO)

#define READ_BELT_ERR    			GPIO_ReadInputDataBit(BELT_ERR_PORT,BELT_ERR_IO) 

#define BELT_SPEED1				 		PBout(6)
#define BELT_SPEED2 					PCout(12)
#define BELT_SPEED3						PDout(2)
#define BELT_DIR 							PBout(7)
// #define BELT_ERR 							PCout(10)// PB5

#define Belt_Speed(x3,x2,x1)	do{	BELT_SPEED1 = x1;BELT_SPEED1 = x2;BELT_SPEED1 = x3;}while(0)

/**现场人员只允许修改这三个参数,时间只是个大概**/
#define START_TIMEOUT		4			//软启动时间，80*5ms*2 =0.8S
#define STOP_TIMEOUT		4			//软停止时间, 80*5ms*2 =0.8S
#define STOP_DELAY			200*2		//200*2*5ms=2s,延时多久只需要改这个参数
/**现场人员只允许修改这三个参数,时间只是个大概**/




void Belt_Config(void);
void Belt_Control(void);


#endif




