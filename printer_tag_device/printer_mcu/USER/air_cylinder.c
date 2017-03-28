#include"HeadType.h"	

Air_Controlr_Type Air_Control;
//=============================================================================
//函数名称: Printer_GPIO_Config
//功能概要:打印机引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
 void Air_Cylinder_GPIO_Config(void)
{	
	//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	//气缸上部到达输入IO配置
	RCC_APB2PeriphClockCmd(UPPER_REACH_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = UPPER_REACH_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(UPPER_REACH_PORT, &GPIO_InitStructure);
	//气缸贴合到位输入IO配置
	RCC_APB2PeriphClockCmd(FIT_REACH_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = FIT_REACH_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(FIT_REACH_PORT, &GPIO_InitStructure);
	//液袋信号输入IO配置
	RCC_APB2PeriphClockCmd(FLUID_BAG_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = FLUID_BAG_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(FLUID_BAG_PORT, &GPIO_InitStructure);
	//扫描枪信号输入IO配置
	RCC_APB2PeriphClockCmd(SCANNER_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = SCANNER_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SCANNER_PORT, &GPIO_InitStructure);

	//气缸下压输出IO配置
	RCC_APB2PeriphClockCmd(AIR_CYLINDER_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = AIR_CYLINDER_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(AIR_CYLINDER_PORT, &GPIO_InitStructure);
	//气缸吹气输出IO配置
	RCC_APB2PeriphClockCmd(AIR_BLOW_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = AIR_BLOW_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(AIR_BLOW_PORT, &GPIO_InitStructure);
	//真空吸纸输出IO配置
	RCC_APB2PeriphClockCmd(VACUUM_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = VACUUM_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(VACUUM_PORT, &GPIO_InitStructure);
	
}

void Air_Cylinder_Control(void)
{

	switch(Air_Control.process){
		case RESERVE:		if(Device_State == 1){  //设备启动
												Air_Control.process = READY;		
										}
										break ;
		case READY:     if((Printer.complete == 1)&&(Air_Control.air_cylinder_position ==IN_UP)&&\
											(Air_Control.delay_time == 0)){  //开始打印的时候就把液袋输入信号置位，可以接收下一次信号输入
																Air_Control.process = WORKING;
																AIR_CYLINDER_DOWM;
																Printer.complete = 0;
																Air_Control.air_cylinder_dowm_timeout = 200;
																 MCU_Host_Send.control.err_message &=0xFB;
														}		                  
					break ;
		case WORKING:   if(Control.fit_reach.state == 1){  //贴合到位
												Control.upper_reach.state = 0; //软件限位，防止两个互斥事件由于状态保存功能同时满足
												AIR_CYLINDER_UP;
												Air_Control.process = WORKEND;
												Control.fit_reach.state = 0;
												Air_Control.air_cylinder_position =IN_DOWN;
												Control.fluid_bag.state = 0;
										}else{
											if(Air_Control.air_cylinder_dowm_timeout == 0){ //压下去不到位，设备故障需要停机
													Device_State = 3;
												 MCU_Host_Send.control.err_message |=0x04;
											}
										}
					break ;
		case WORKEND:   if(Control.upper_reach.state == 1){  //上步到位
												Control.fit_reach.state = 0; //软件限位，防止两个互斥事件由于状态保存功能同时满足
												Air_Control.process = END;
												Air_Control.complete = 1;
												Control.upper_reach.state = 0;
												Air_Control.air_cylinder_position =IN_UP;
												VACUUM_OFF;
												AIR_BLOW_OFF;
//												Control.fluid_bag.state = 0;												
										}
					break;
		case END: if(Device_State == 1){  //设备启动 
									Air_Control.process = READY; 
//									COMMUNICATION_IO2_OFF;
							}else{
									Air_Control.process = RESERVE; 
							}
					break ;
		default :break ;
	}
}




