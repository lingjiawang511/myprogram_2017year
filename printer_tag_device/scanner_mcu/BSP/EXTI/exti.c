#include"HeadType.h"	

 Control_Input_Type Control;

//=============================================================================
//函数名称:EXTIX0_Init
//功能概要:外部中断0初始化
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void  EXTIX0_Init(void )
{
	 	EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		GPIO_InitTypeDef  GPIO_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
}
////=============================================================================
////函数名称:EXTIX3_Init
////功能概要:外部中断3初始化
////参数名称:无
////函数返回:无
////注意    :无
////=============================================================================
//static void  EXTIX3_Init(void )
//{
//	 	EXTI_InitTypeDef EXTI_InitStructure;
//		NVIC_InitTypeDef NVIC_InitStructure;
//		GPIO_InitTypeDef  GPIO_InitStructure;
//	
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
////	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
//		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			 
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//		GPIO_Init(GPIOB, &GPIO_InitStructure);
//	
//	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource3);
//			
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;	//KEY2
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
//	
//	  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY2所在的外部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级2
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure);
//}
////=============================================================================
////函数名称:EXTIX4_Init
////功能概要:外部中断4初始化
////参数名称:无
////函数返回:无
////注意    :无
////=============================================================================
//static void  EXTIX4_Init(void )
//{
//	 	EXTI_InitTypeDef EXTI_InitStructure;
//		NVIC_InitTypeDef NVIC_InitStructure;
//		GPIO_InitTypeDef  GPIO_InitStructure;
//	
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
////	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
//		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;			 
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//		GPIO_Init(GPIOB, &GPIO_InitStructure);
//	
//	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource4);
//	
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;	//KEY2
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
//	
//	  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键KEY2所在的外部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure);
//}
////=============================================================================
////函数名称:EXTIX9_5_Init
////功能概要:外部中断9_5初始化
////参数名称:无
////函数返回:无
////注意    :无
////=============================================================================
//static void  EXTIX9_5_Init(void )
//{
//	 	EXTI_InitTypeDef EXTI_InitStructure;
//		NVIC_InitTypeDef NVIC_InitStructure;
//		GPIO_InitTypeDef  GPIO_InitStructure;
//	
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
//	
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_8;			 
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//		GPIO_Init(GPIOC, &GPIO_InitStructure);
//	
//		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource6); 
// 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource8);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line6|EXTI_Line8;
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
//	
//	  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键KEY2所在的外部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure);
//}
//=============================================================================
//函数名称:EXTIX15_10_Init
//功能概要:外部中断15_10初始化
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void  EXTIX15_10_Init(void )
{
	 	EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		GPIO_InitTypeDef  GPIO_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;			 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10); 
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource11);
	
  	EXTI_InitStructure.EXTI_Line=EXTI_Line10|EXTI_Line11;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
}

//=============================================================================
//函数名称:EXTIX_Init
//功能概要:所有外部中断初始化
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void EXTIX_Init(void)
{
		EXTIX0_Init( );
//		EXTIX3_Init( );
//		EXTIX4_Init( );
//		EXTIX9_5_Init( );
		EXTIX15_10_Init( );
  	
}
//=============================================================================
//函数名称:EXTI0_IRQHandler
//功能概要:外部中断0服务程序 
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void EXTI0_IRQHandler(void)
{		
		if(EXTI_GetITStatus(EXTI_Line0) != RESET){
			if(Control.scanner.irqstate == 0){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真					
					Control.scanner.irqstate = 1;
					Control.scanner.irqtime = 0;					
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
		
}

//=============================================================================
//函数名称:EXTI3_IRQHandler
//功能概要:外部中断3服务程序 
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3) != RESET){

		}
		EXTI_ClearITPendingBit(EXTI_Line3); //清除LINE0上的中断标志位  
	 
}
//=============================================================================
//函数名称:EXTI4_IRQHandler
//功能概要:外部中断4服务程序 
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4) != RESET){
		EXTI_ClearITPendingBit(EXTI_Line4); //清除LINE0上的中断标志位  
	}  
}
//=============================================================================
//函数名称:EXTI9_5_IRQHandler
//功能概要:外部中断9-5服务程序 
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line6) != RESET){
			
			EXTI_ClearITPendingBit(EXTI_Line6);
	}else if(EXTI_GetITStatus(EXTI_Line8) != RESET){

		EXTI_ClearITPendingBit(EXTI_Line8);
	}else{
		EXTI_ClearITPendingBit(EXTI_Line5);
		EXTI_ClearITPendingBit(EXTI_Line7);
		EXTI_ClearITPendingBit(EXTI_Line9);
	}

}
//=============================================================================
//函数名称:EXTI15_10_IRQHandler
//功能概要:外部中断15-10服务程序 
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line10) != RESET){
	if(Control.scanner.irqstate == 0){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真					
					Control.baffle_outer.irqstate = 1;
					Control.baffle_outer.irqtime = 0;					
			}
		EXTI_ClearITPendingBit(EXTI_Line10);
	}else if(EXTI_GetITStatus(EXTI_Line11) != RESET){
	if(Control.scanner.irqstate == 0){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真					
					Control.baffle_inter.irqstate = 1;
					Control.baffle_inter.irqtime = 0;					
			}
			  EXTI_ClearITPendingBit(EXTI_Line11);
	}else if(EXTI_GetITStatus(EXTI_Line14) != RESET){

		EXTI_ClearITPendingBit(EXTI_Line14);
	}else{
		EXTI_ClearITPendingBit(EXTI_Line12);
		EXTI_ClearITPendingBit(EXTI_Line13);
		EXTI_ClearITPendingBit(EXTI_Line15);
	}
}

//=============================================================================
//函数名称:Control_Input_IRQTimer
//功能概要:打印机输入状态计数脉冲软件延时检测
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void 	Control_Input_IRQTimer(void)
{
		if(Control.scanner.irqstate == 1){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Control.scanner.irqtime++;
					if(IRQ_TIMEOUT <= Control.scanner.irqtime){
						if(READ_SCANNER == RESET){
							Control.scanner.state = 1;
						}
						Control.scanner.irqstate = 0;
						Control.scanner.irqtime = 0;
					}
		}
		if(Control.baffle_inter.irqstate == 1){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Control.baffle_inter.irqtime++;
					if(IRQ_TIMEOUT <= Control.baffle_inter.irqtime){
						if(READ_BAFFLE_INTER == RESET){

							Control.baffle_inter.state = 1;
//							if(Air_Control.delay_time == 0){
//								Air_Control.delay_time = 200;   //以后要改成可变的时间  
//							}
						}
						Control.baffle_inter.irqstate = 0;
						Control.baffle_inter.irqtime = 0;
					}
		}
		if(Control.baffle_outer.irqstate == 1){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Control.baffle_outer.irqtime++;
					if(IRQ_TIMEOUT <= Control.baffle_outer.irqtime){
						if(READ_BAFFLE_OUTER  == RESET){
							Control.baffle_outer.state = 1;
						}
						Control.baffle_outer.irqstate = 0;
						Control.baffle_outer.irqtime = 0;
					}
		}

		
}





