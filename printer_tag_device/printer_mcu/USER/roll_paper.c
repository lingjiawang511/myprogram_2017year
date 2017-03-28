#include"HeadType.h"	


#define	ROLL_PAPER_IO			  	GPIO_Pin_7
#define	ROLL_PAPER_PORT			  GPIOA
#define	ROLL_PAPER_RCC				RCC_APB2Periph_GPIOA

#define ROLL_PAPER_ON  		 		GPIO_SetBits(ROLL_PAPER_PORT, ROLL_PAPER_IO)
#define ROLL_PAPER_OFF  			GPIO_ResetBits(ROLL_PAPER_PORT, ROLL_PAPER_IO)



//=============================================================================
//函数名称: ROLL_PAPER_GPIO_Config
//功能概要:卷纸电机控制引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void ROLL_PAPER_GPIO_Config(void)
{	
	//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	//停止按键IO配置
	RCC_APB2PeriphClockCmd(ROLL_PAPER_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = ROLL_PAPER_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(ROLL_PAPER_PORT, &GPIO_InitStructure);

}

void Roll_Paper_Control(void)
{
	 if(Device_State == 1){//Device_State=0：待机状态，Device_State=1：启动状态，Device_State=2：停止状态
			ROLL_PAPER_ON;
		 	belt.state = READY;			//运输皮带启动
//		  COMMUNICATION_IO1_ON;
	}else if(Device_State == 2){
			ROLL_PAPER_OFF;
		  AIR_CYLINDER_UP;
		  AIR_BLOW_OFF;
		  VACUUM_OFF;
			belt.state = END ;     //运输皮带停止
			param_init();
	}else if(Device_State == 3){
			Printer.complete = 0;
			Printer.process = PRINTER_RESERVE;
			PRINTER_START_OFF;
		  Air_Control.process = RESERVE;
			belt.state = END ;     //运输皮带停止
		  AIR_BLOW_OFF;
		  VACUUM_OFF;
//		  COMMUNICATION_IO1_OFF;
		}else{
      ROLL_PAPER_ON;
			belt.state = END ;     //运输皮带停止
			param_init();
			if(READ_UPPER_REACH==0){
				AIR_CYLINDER_UP;
		  }
	}

}









