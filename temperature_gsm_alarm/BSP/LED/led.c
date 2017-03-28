#include "led.h"
#include"HeadType.h"
#include "sim900a.h"

u16 Led_Flash_Time;
//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA,PD端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //LED0-->PA.8 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
 GPIO_SetBits(GPIOC,GPIO_Pin_13);						 //PA.8 输出高

// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2 端口配置, 推挽输出
// GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
// GPIO_SetBits(GPIOD,GPIO_Pin_2); 						 //PD.2 输出高 
}
 
void LED_Display(void)
{
			Led_Flash_Time++;
		if(Gsm_Check_Flag ==0){
		if(Sim_Ready){
			if(Led_Flash_Time%100 ==0){
				LED0=!LED0;
			}
		}else{
				if(Led_Flash_Time%30 ==0){
					LED0=!LED0;
				}
			}
		}else{//初始化不通过
			if(Led_Flash_Time<=60){
				 LED0=0;
			}else if((60<Led_Flash_Time)&&(Led_Flash_Time < 400)){
				 LED0=1;
			}else if(Led_Flash_Time > 400){
				Led_Flash_Time = 0;
				LED0=0;
      }
		}
}








