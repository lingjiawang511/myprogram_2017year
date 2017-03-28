#include "HeadType.h"	

static u8 Speed_Step;
static u8 Start_Ok;
u8 Send_Medicine_Finish_State;		//所有通道发药完成状态，避免发药没完成，皮带就停止了
//=============================================================================
//函数名称:Send_Medicine1_Config
//功能概要:发药口1相关引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
 void Belt_Config(void)
{
		//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//皮带速度控制IO口1
	GPIO_InitStructure.GPIO_Pin = BELT_SPEED1_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(BELT_SPEED1_PORT, &GPIO_InitStructure);
//	//皮带速度控制IO口2
//	GPIO_InitStructure.GPIO_Pin = BELT_SPEED2_IO;			 
//	GPIO_Init(BELT_SPEED2_PORT, &GPIO_InitStructure);
//	//皮带速度控制IO口3
//	GPIO_InitStructure.GPIO_Pin = BELT_SPEED3_IO;			 
//	GPIO_Init(BELT_SPEED3_PORT, &GPIO_InitStructure);
	//皮带方向控制IO口
	GPIO_InitStructure.GPIO_Pin = BELT_DIR_IO;			 
	GPIO_Init(BELT_DIR_PORT, &GPIO_InitStructure);
	//皮带控制器故障IO口
	GPIO_InitStructure.GPIO_Pin = BELT_ERR_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(BELT_ERR_PORT, &GPIO_InitStructure);
	
	Speed_Step = 0;
	Start_Ok = 0;
	BELT_SPEED1 = 0;
	BELT_DIR = 0;
	Send_Medicine_Finish_State = 0;
}

//=============================================================================
//函数名称:BELT_Speed_Control
//功能概要:皮带速度控制函数
//参数名称:speed：皮带输入速度
//函数返回:无
//注意    :无
//=============================================================================
static void Belt_Speed_Control(u8 speed)
{
	if(speed == 0){
		Belt_Speed(0,0,0);	
	}else if(speed == 1){
		Belt_Speed(0,0,1);
	}else if(speed == 2){
		Belt_Speed(0,1,0);
	}else if(speed == 3){
		Belt_Speed(0,1,1);
	}else if(speed == 4){
		Belt_Speed(1,0,0);
	}else if(speed == 5){
		Belt_Speed(1,0,1);
	}else if(speed == 6){
		Belt_Speed(1,1,0);
	}else if(speed == 7){
		Belt_Speed(1,1,1);
	}
}

//=============================================================================
//函数名称:Start_Belt
//功能概要:皮带电机软启动函数
//参数名称:step：电机速度也是电机运行状态步数
//函数返回:电机执行到哪一步的速度
//注意    :需要在定时器中断函数调用
//=============================================================================
static u8 Start_Belt(u8 step)
{
	static u16 start_time = 0;
	switch(step){
	case 0x00:Belt_Speed_Control(step);step++; break;
	case 0x01:Belt_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;
	case 0x02:Belt_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;						
	case 0x03:Belt_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;
	case 0x04:Belt_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;						
	case 0x05:Belt_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT){step++;start_time = 0;} break;					
	case 0x06:Belt_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;						
	case 0x07:Belt_Speed_Control(step-1);start_time++;
						if(start_time >= START_TIMEOUT/4)
							{step++;start_time = 0;Start_Ok = 1;} break;						
	default:start_time = 0; break;
	}
	return step;
}
//=============================================================================
//函数名称:Stop_Belt
//功能概要:电机软停止函数
//参数名称:step：电机速度也是电机运行状态步数
//函数返回:电机执行到哪一步的速度
//注意    :需要在定时器中断函数调用
//=============================================================================
static u8 Stop_Belt(u8 step)
{
	static u16 stop_time = 0;
	switch(step){
	case 0x01:Belt_Speed_Control(step-1);step--;stop_time = 0;Start_Ok = 0;break;
	case 0x02:Belt_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/4){step--;stop_time = 0;} break;	
	case 0x03:Belt_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/4){step--;stop_time = 0;} break;	
	case 0x04:Belt_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	case 0x05:Belt_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	case 0x06:Belt_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	case 0x07:Belt_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	case 0x08:Belt_Speed_Control(step-2);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	default:Belt_Speed_Control(0);stop_time = 0; break;
	}
		return step;
}

//=============================================================================
//函数名称:Belt_Control
//功能概要:皮带控制
//参数名称:无
//函数返回:无
//注意    :必须在5MS定时器中调用
//=============================================================================
void Belt_Control(void)
{
	static u16 delay_time = 0;
	switch(belt.state){
	case RESERVE:	belt.actual_time = 1000;							
								break;
	case READY:	if(Start_Ok == 0){
								Speed_Step = Start_Belt(Speed_Step);	
						   }else{
									belt.state = WORKING;
									delay_time = 0;
							}
								break ;	
	case WORKING:if(Start_Ok == 1){
									delay_time++;
									if(delay_time >= belt.actual_time){
//										belt.state = END ;
										delay_time = 0;
									}
								}
								break;

	case END:	if(Start_Ok == 1){
								Speed_Step = Stop_Belt(Speed_Step);
						}else{
								belt.state = RESERVE;
						}
								break ;	
	default :
								break;	
	}	
}

