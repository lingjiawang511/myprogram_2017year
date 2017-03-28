#include"HeadType.h"	


////=============================================================================
////函数名称:EXTIX0_Init
////功能概要:外部中断0初始化
////参数名称:无
////函数返回:无
////注意    :无
////=============================================================================
//static void  EXTIX0_Init(void )
//{
//	 	EXTI_InitTypeDef EXTI_InitStructure;
//		NVIC_InitTypeDef NVIC_InitStructure;
//		GPIO_InitTypeDef  GPIO_InitStructure;
//	
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
//	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			 
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//		GPIO_Init(GPIOB, &GPIO_InitStructure);
//	
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	//KEY2
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
//	
//	  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键KEY2所在的外部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级2
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure);
//}
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
//=============================================================================
//函数名称:EXTIX9_5_Init
//功能概要:外部中断9_5初始化
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void  EXTIX9_5_Init(void )
{
	 	EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		GPIO_InitTypeDef  GPIO_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;			 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource6); 
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource7); 
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource8);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource9); 
  	EXTI_InitStructure.EXTI_Line=EXTI_Line6|EXTI_Line7|EXTI_Line8|EXTI_Line9;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
}
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
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;		
//		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_14;			
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10); 
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource11); 
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource12);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource15);
	
  	EXTI_InitStructure.EXTI_Line=EXTI_Line10|EXTI_Line11|EXTI_Line12|EXTI_Line13|EXTI_Line14|EXTI_Line15;
//		EXTI_InitStructure.EXTI_Line=EXTI_Line14;
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
//函数名称:Control_Input_IRQTimer
//功能概要:打印机输入状态计数脉冲软件延时检测
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void 	Control_Input_IRQTimer(void)
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
		if(Control.fluid_bag.irqstate == 1){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Control.fluid_bag.irqtime++;
					if(IRQ_TIMEOUT*5 <= Control.fluid_bag.irqtime){
						if(READ_FLUID_BAG == RESET){
							Control.fluid_bag.state = 1;
//							COMMUNICATION_IO2_ON;			//和CPU2通讯，告诉COU2有液袋输入
							Printer.fluid_bag_timeout = 600;  //打印机打印超时时间，故障时间，主要是由于气缸压下时不到位导致的故障
							if(Air_Control.delay_time == 0){
								Air_Control.delay_time = Air_Control.PC_send_delay_time;   //以后要改成可变的时间  
//								Air_Control.delay_time = 0;   //以后要改成可变的时间  
							}
						}
						Control.fluid_bag.irqstate = 0;
						Control.fluid_bag.irqtime = 0;
					}
		}
		if(Control.upper_reach.irqstate == 1){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Control.upper_reach.irqtime++;
					if(IRQ_TIMEOUT <= Control.upper_reach.irqtime){
						if(READ_UPPER_REACH == RESET){
							Control.upper_reach.state = 1;
						}
						Control.upper_reach.irqstate = 0;
						Control.upper_reach.irqtime = 0;
					}
		}
		if(Control.fit_reach.irqstate == 1){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Control.fit_reach.irqtime++;
					if(IRQ_TIMEOUT <= Control.fit_reach.irqtime){
						if(READ_FIT_REACH == RESET){
							Control.fit_reach.state = 1;
						}
						Control.fit_reach.irqstate = 0;
						Control.fit_reach.irqtime = 0;
					}
		}
		
}
//=============================================================================
//函数名称:Printer_Input_IRQTimer
//功能概要:打印机输入状态计数脉冲软件延时检测
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void 	Printer_Input_IRQTimer(void)
{
		if(Printer.color_less.irqstate == 1){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Printer.color_less.irqtime++;
					if(IRQ_TIMEOUT <= Printer.color_less.irqtime){
						if(READ_PRINTER_COLESS == RESET){
							Printer.color_less.state = 1;
						}
						Printer.color_less.irqstate = 0;
						Printer.color_less.irqtime = 0;
					}
		}
		if(Printer.pinline.irqstate == 1){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Printer.pinline.irqtime++;
					if(IRQ_TIMEOUT <= Printer.pinline.irqtime){
						if(READ_PRINTER_INLINE == RESET){
							Printer.pinline.state = 1;
						}
						Printer.pinline.irqstate = 0;
						Printer.pinline.irqtime = 0;
					}
		}
		if(Printer.color_end.irqstate == 1){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Printer.color_end.irqtime++;
					if(IRQ_TIMEOUT <= Printer.color_end.irqtime){
						if(READ_PRINTER_COEND == RESET){
							Printer.color_end.state = 1;
						}
						Printer.color_end.irqstate = 0;
						Printer.color_end.irqtime = 0;
					}
		}
		if(Printer.err.irqstate == 1){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Printer.err.irqtime++;
					if(IRQ_TIMEOUT <= Printer.err.irqtime){
						if(READ_PRINTER_ERR == RESET){
							Printer.err.state = 1;
						}
						Printer.err.irqstate = 0;
						Printer.err.irqtime = 0;
					}
		}
		if(Printer.end.irqstate == 1){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Printer.end.irqtime++;
					if(IRQ_TIMEOUT <= Printer.end.irqtime){
						if(READ_PRINTER_END == RESET){
							Printer.end.state = 1;
						}
						Printer.end.irqstate = 0;
						Printer.end.irqtime = 0;
					}
		}
		if(Printer.tag_end.irqstate == 1){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Printer.tag_end.irqtime++;
					if(IRQ_TIMEOUT <= Printer.tag_end.irqtime){
						if(READ_PRINTER_TAGEND == RESET){
							Printer.tag_end.state = 1;
						}
						Printer.tag_end.irqstate = 0;
						Printer.tag_end.irqtime = 0;
					}
		}
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
//		EXTIX0_Init( );
//		EXTIX3_Init( );
//		EXTIX4_Init( );
		EXTIX9_5_Init( );
		EXTIX15_10_Init( );
  	
}
////=============================================================================
////函数名称:EXTI0_IRQHandler
////功能概要:外部中断0服务程序 
////参数名称:无
////函数返回:无
////注意    :无
////=============================================================================
//void EXTI0_IRQHandler(void)
//{		
//		static u8 test=0;
//		if(EXTI_GetITStatus(EXTI_Line0) != RESET){
//		if(MCU_State == HOST){
//				if((Channel.ch1.motor_irqstate == 0)&&(Channel.ch1.state == WORKING)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
//					if((Channel.ch1.send_num-1 <= Channel.ch1.motor_pulse)){
//						Channel.ch1.motor_pulse++;
//					}else{
//						Channel.ch1.motor_irqstate = 1;
//					}
//				}
//				if(Channel.ch1.state == WORKING){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真，最后一次不用延时
//					if((Channel.ch1.send_num <= Channel.ch1.motor_pulse)){ //电机转过了那么多圈，就应该发那么多药
//							DEVICE1_MOTOR_STOP;	
//							Channel.ch1.motor_state	= 0;	
//							Channel.ch1.motor_irqstate = 0;						
//						}
//					}else if((Channel.ch1.state ==RESERVE)||(Channel.ch1.state == END)){
//						DEVICE1_MOTOR_STOP;	
//						Channel.ch1.motor_state	= 0;	
//				}
//			}else{
//				test++;
//				if(test >= 5){
//					test = 0;
//					DEVICE1_MOTOR_STOP;	//从机模式只要转到原点就停止
//					Channel.ch1.motor_state	= 0;
//				}
////				DEVICE1_MOTOR_STOP;	//从机模式只要转到原点就停止
////				Channel.ch1.motor_state	= 0;
//			}
//		EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
//		}
//}

////=============================================================================
////函数名称:EXTI3_IRQHandler
////功能概要:外部中断3服务程序 
////参数名称:无
////函数返回:无
////注意    :无
////=============================================================================
//void EXTI3_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line3) != RESET){
//		if(MCU_State == HOST){
//				if((Channel.ch4.motor_irqstate == 0)&&(Channel.ch4.state == WORKING)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
//					if((Channel.ch4.send_num-1 <= Channel.ch4.motor_pulse)){
//						Channel.ch4.motor_pulse++;
//					}else{
//						Channel.ch4.motor_irqstate = 1;
//					}
//				}
//				if(Channel.ch4.state == WORKING){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真，最后一次不用延时
//					if((Channel.ch4.send_num <= Channel.ch4.motor_pulse)){ //电机转过了那么多圈，就应该发那么多药
//							DEVICE4_MOTOR_STOP;	
//							Channel.ch4.motor_state	= 0;	
//							Channel.ch4.motor_irqstate = 0;						
//						}
//					}else if((Channel.ch4.state ==RESERVE)||(Channel.ch4.state == END)){
//						DEVICE4_MOTOR_STOP;	
//						Channel.ch4.motor_state	= 0;	
//				}
//			}else{
//				DEVICE4_MOTOR_STOP;	//从机模式只要转到原点就停止
//				Channel.ch4.motor_state	= 0;
//			}
//		EXTI_ClearITPendingBit(EXTI_Line3); //清除LINE0上的中断标志位  
//	} 
//}
////=============================================================================
////函数名称:EXTI4_IRQHandler
////功能概要:外部中断4服务程序 
////参数名称:无
////函数返回:无
////注意    :无
////=============================================================================
//void EXTI4_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line4) != RESET){
//		if(MCU_State == HOST){
//				if((Channel.ch4.send_actual_irqstate == 0)&&(Channel.ch4.state == WORKING)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真					
//						Channel.ch4.send_actual_irqstate = 1;
//						Channel.ch4.send_actual_irqtime = 0;					
//				}
//			}
//		EXTI_ClearITPendingBit(EXTI_Line4); //清除LINE0上的中断标志位  
//	}  
//}
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
			if(Control.scanner.irqstate == 0){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真					
					Control.scanner.irqstate = 1;
					Control.scanner.irqtime = 0;					
			}
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
	if(EXTI_GetITStatus(EXTI_Line7) != RESET){
			if(Control.fluid_bag.irqstate == 0){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真					
					Control.fluid_bag.irqstate = 1;
					Control.fluid_bag.irqtime = 0;					
			}
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
	if(EXTI_GetITStatus(EXTI_Line8) != RESET){
			if(Control.upper_reach.irqstate == 0){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真					
					Control.upper_reach.irqstate = 1;
					Control.upper_reach.irqtime = 0;					
			}
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
	if(EXTI_GetITStatus(EXTI_Line9) != RESET){
			if(Control.fit_reach.irqstate == 0){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真					
					Control.fit_reach.irqstate = 1;
					Control.fit_reach.irqtime = 0;					
			}
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
			if(Printer.color_less.irqstate == 0){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真					
					Printer.color_less.irqstate = 1;
					Printer.color_less.irqtime = 0;					
			}
		EXTI_ClearITPendingBit(EXTI_Line10);
	}
	if(EXTI_GetITStatus(EXTI_Line11) != RESET){
			if(Printer.pinline.irqstate == 0){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真					
					Printer.pinline.irqstate = 1;
					Printer.pinline.irqtime = 0;					
			}
		EXTI_ClearITPendingBit(EXTI_Line11);
	}
	if(EXTI_GetITStatus(EXTI_Line12) != RESET){
			if(Printer.color_end.irqstate == 0){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真					
					Printer.color_end.irqstate = 1;
					Printer.color_end.irqtime = 0;					
			}
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
	if(EXTI_GetITStatus(EXTI_Line13) != RESET){
			if(Printer.err.irqstate == 0){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真					
					Printer.err.irqstate = 1;
					Printer.err.irqtime = 0;					
			}
		EXTI_ClearITPendingBit(EXTI_Line13);
	}
	if(EXTI_GetITStatus(EXTI_Line14) != RESET){
			if(Printer.end.irqstate == 0){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真					
					Printer.end.irqstate = 1;
					Printer.end.irqtime = 0;					
			}
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
	if(EXTI_GetITStatus(EXTI_Line15) != RESET){
			if(Printer.tag_end.irqstate == 0){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真					
					Printer.tag_end.irqstate = 1;
					Printer.tag_end.irqtime = 0;					
			}
		EXTI_ClearITPendingBit(EXTI_Line15);
	}
}
//=============================================================================
//函数名称:Motor_pulse_IRQTimer
//功能概要:电机原点脉冲中断延时检测函数 
//参数名称:无
//函数返回:无
//注意    :必须在2ms定时器中断服务函数中调用
//=============================================================================
void 	Input_pulse_IRQTimer(void)
{
	Control_Input_IRQTimer();
	Printer_Input_IRQTimer();
}






