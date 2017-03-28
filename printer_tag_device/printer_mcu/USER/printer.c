#include"HeadType.h"	

#define PRINTER_START_DELAY_TIME  6;
//=============================================================================
//º¯ÊıÃû³Æ: Printer_GPIO_Config
//¹¦ÄÜ¸ÅÒª:´òÓ¡»úÒı½ÅÅäÖÃ
//²ÎÊıÃû³Æ:ÎŞ
//º¯Êı·µ»Ø:ÎŞ
//×¢Òâ    :ÎŞ
//=============================================================================
 void Printer_GPIO_Config(void)
{	
	//¶¨ÒåÒ»¸öGPIO_InitTypeDef ÀàĞÍµÄ½á¹¹Ìå£¬Ãû×Ö½ĞGPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	//´òÓ¡»ú¹ÊÕÏÊäÈëIOÅäÖÃ
	RCC_APB2PeriphClockCmd(PRINTER_ERR_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_ERR_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_ERR_PORT, &GPIO_InitStructure);
	//´òÓ¡»ú´òÓ¡½áÊøÊäÈëIOÅäÖÃ
	RCC_APB2PeriphClockCmd(PRINTER_END_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_END_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_END_PORT, &GPIO_InitStructure);
	//´òÓ¡»úÔÚÏßÊäÈëIOÅäÖÃ
	RCC_APB2PeriphClockCmd(PRINTER_INLINE_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_INLINE_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_INLINE_PORT, &GPIO_InitStructure);
	//´òÓ¡»ú±êÇ©ÓÃÍêÊäÈëIOÅäÖÃ
	RCC_APB2PeriphClockCmd(PRINTER_TAGEND_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_TAGEND_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_TAGEND_PORT, &GPIO_InitStructure);
	//´òÓ¡»úÉ«´øÓÃÍêÊäÈëIOÅäÖÃ
	RCC_APB2PeriphClockCmd(PRINTER_COEND_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_COEND_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_COEND_PORT, &GPIO_InitStructure);
	//´òÓ¡»úÉ«´øÉÙÊäÈëIOÅäÖÃ
	RCC_APB2PeriphClockCmd(PRINTER_COLESS_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_COLESS_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_COLESS_PORT, &GPIO_InitStructure);	
	
	//´òÓ¡»úÆô¶¯Êä³öIOÅäÖÃ
	RCC_APB2PeriphClockCmd(PRINTER_START_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_START_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_START_PORT, &GPIO_InitStructure);
	//´òÓ¡»úÖØ¸´Æô¶¯Êä³öIOÅäÖÃ
	RCC_APB2PeriphClockCmd(PRINTER_RESTART_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = PRINTER_RESTART_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PRINTER_RESTART_PORT, &GPIO_InitStructure);
	

}
static void Printer_Input_Scan(void)
{
   if((Printer.err.state == 0)&&(Printer.tag_end.state == 0)&&(Printer.color_end.state == 0)){
			Printer.input_state = 1;
		}else{ //ÓĞ´íÎó±ØĞëÊ¹Éè±¸»Ö¸´µ½´ı»ú×´Ì¬»òÕßÆô¶¯×´Ì¬²Å¿ÉÒÔÈ¡Ïû´íÎó×´Ì¬
			Printer.input_state = 0;
		}

}
static u8 Printer_Process_Input(void)
{
	 u8 res;
	 Printer_Input_Scan();
	 if(Device_State == 1){  //Éè±¸Æô¶¯
			if(Printer.input_state == 1){  //´òÓ¡»úÊäÈë×´Ì¬OK
//				if(Printer.process == 1){      //´òÓ¡»úÆô¶¯´òÓ¡
//					PRINTER_START_ON;
//				}
				res = 0;
			}else{
				Device_State = 3;
				res = 1;
			}
		  return res;
		}else if(Device_State == 2){ //Éè±¸Í£Ö¹
			 PRINTER_START_OFF;
			 Printer.err.state = 0;
			 Printer.tag_end.state = 0;
			 Printer.color_end.state = 0;
			 Printer.pinline.state = 0;
		}else{
			 PRINTER_START_OFF;
			 Printer.err.state = 0;
			 Printer.tag_end.state = 0;
			 Printer.color_end.state = 0;
			 Printer.pinline.state = 0;
		}
		res = 1;
		return res;

}
void Printer_Control(void)
{
	static u8 working_err = 0;
	if(1 == Printer_Process_Input()){		//Ã¿¸ö¹ı³Ì¶¼ĞèÒª²éÑ¯Ò»ÏÂ´òÓ¡»ú×´Ì¬ºÍÉè±¸×´Ì¬ÊÇ·ñOK
			Printer.process = PRINTER_RESERVE;		
	}else{
			Printer.process = Printer.process;	
	}
	switch(Printer.process){
		case PRINTER_RESERVE:		
													if(Device_State == 1){  //Éè±¸Æô¶¯
															if(0 == Printer_Process_Input()){		//´òÓ¡»úOKÄ
																Printer.process = PRINTER_READY;		
															}
													}
													break ;
		case PRINTER_READY:   
														if(Printer.fluid_bag_timeout==0){
																Control.fluid_bag.state = 0;  //Ò»¶ÎÊ±¼äÄÚ´òÓ¡»úÃ»·´Ó¦£¬ÏÂÑ¹Æø¸×ÓĞÎÊÌâ£¬ĞèÒªÇåÁãÕâ¸ö×´Ì¬£¬·ñÔòÏÂ´ÎÆô¶¯´òÓ¡»ú»á´òÓ¡
															}
														if((Air_Control.complete == 1)&&(Control.fluid_bag.state == 1)&&(READ_UPPER_REACH==0)){  //¿ªÊ¼´òÓ¡µÄÊ±ºò¾Í°ÑÒº´üÊäÈëĞÅºÅÖÃÎ»£¬¿ÉÒÔ½ÓÊÕÏÂÒ»´ÎĞÅºÅÊäÈë
																Printer.process = PRINTER_WORKING;
																Printer.start_delay_time = PRINTER_START_DELAY_TIME;																																
																AIR_BLOW_ON;
																VACUUM_ON;
																PRINTER_START_ON;
																Air_Control.complete = 0;
															  Printer.printer_work_timeout = 100;
															  MCU_Host_Send.control.err_message &=0xF7;
//																Control.fluid_bag.state = 0;
														}		                  
					break ;
		case PRINTER_WORKING:   if(Printer.end.state == 1){
															Printer.process = PRINTER_END;
															Printer.complete = 1;														
															Control.fluid_bag.state = 0;
															Printer.end.state = 0;
													  }else{
															if(Printer.printer_work_timeout == 0){
																	if(READ_PRINTER_END == SET){//´òÓ¡ÖĞ£¬µ«ÊÇÃ»ÓĞÈÎÎñ£¬ËùÒÔÎª¸ßµçÆ½
																		Printer.process = PRINTER_END;
																		Printer.complete = 1;
																		AIR_BLOW_OFF;
																		VACUUM_OFF;
																		AIR_BLOW_OFF;
																		Control.fluid_bag.state = 0;
																		Printer.end.state = 0;
																		working_err++;
																		if(working_err > 3){//Á¬Ğø3´Î·¢ËÍ´òÓ¡²Ù×÷£¬µ«ÊÇÃ»ÓĞ´òÓ¡ÈÎÎñ£¬Ò²¾ÍÊÇÃ»ÓĞ´òÓ¡½áÊøĞÅºÅ£¬ÉèÖÃÎª¹ÊÕÏ±¨¾¯
																			Device_State = 3;
																			working_err = 0;	
																			MCU_Host_Send.control.err_message |=0x08;
																		}
																	}
															}
														}
					break ;
		case PRINTER_END: if(Device_State == 1){  //Éè±¸Æô¶¯     
													Printer.process = PRINTER_READY; 
											}else{
													Printer.process = PRINTER_RESERVE;	
											}
					break ;
		default :break ;
	}
}




















