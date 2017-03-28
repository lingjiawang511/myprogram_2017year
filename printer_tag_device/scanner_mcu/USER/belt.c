#include "HeadType.h"	

//static u8 belt.speed_step;
//static u8 belt11.start_ok;
//static u8 belt21.speed_step;
//static u8 belt21.start_ok;
Belt_Work_Type belt11;
Belt_Work_Type belt12;
u8 Send_Medicine_Finish_State;		//所有通道发药完成状态，避免发药没完成，皮带就停止了
//=============================================================================
//函数名称:Belt11_Config
//功能概要:皮带11 IO配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
 void Belt11_Config(void)
{
		//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	//皮带速度控制IO口1
	GPIO_InitStructure.GPIO_Pin = BELT11_SPEED1_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(BELT11_SPEED1_PORT, &GPIO_InitStructure);
	//皮带速度控制IO口2
	GPIO_InitStructure.GPIO_Pin = BELT11_SPEED2_IO;			 
	GPIO_Init(BELT11_SPEED2_PORT, &GPIO_InitStructure);
	//皮带速度控制IO口3
	GPIO_InitStructure.GPIO_Pin = BELT11_SPEED3_IO;			 
	GPIO_Init(BELT11_SPEED3_PORT, &GPIO_InitStructure);
	//皮带方向控制IO口
	GPIO_InitStructure.GPIO_Pin = BELT11_DIR_IO;			 
	GPIO_Init(BELT11_DIR_PORT, &GPIO_InitStructure);
	//皮带控制器故障IO口
	GPIO_InitStructure.GPIO_Pin = BELT11_ERR_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(BELT11_ERR_PORT, &GPIO_InitStructure);
	//皮带传感器11 IO口
	GPIO_InitStructure.GPIO_Pin = BELT11_SENSOR1_IO;
	GPIO_Init(BELT11_SENSOR1_PORT, &GPIO_InitStructure);
	//皮带传感器12 IO口
	GPIO_InitStructure.GPIO_Pin = BELT11_SENSOR2_IO;
	GPIO_Init(BELT11_SENSOR2_PORT, &GPIO_InitStructure);
	
	belt11.speed_step = 0;
	belt11.start_ok = 0;
	BELT11_SPEED1 = 0;
	BELT11_SPEED2 = 0;
	BELT11_SPEED3 = 0;
	BELT11_DIR = 0;
}

//=============================================================================
//函数名称:Belt21_Config
//功能概要:皮带2IO配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
 void Belt12_Config(void)
{
		//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	//皮带速度控制IO口1
	GPIO_InitStructure.GPIO_Pin = BELT12_SPEED1_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(BELT12_SPEED1_PORT, &GPIO_InitStructure);
	//皮带速度控制IO口2
	GPIO_InitStructure.GPIO_Pin = BELT12_SPEED2_IO;			 
	GPIO_Init(BELT12_SPEED2_PORT, &GPIO_InitStructure);
	//皮带速度控制IO口3
	GPIO_InitStructure.GPIO_Pin = BELT12_SPEED3_IO;			 
	GPIO_Init(BELT12_SPEED3_PORT, &GPIO_InitStructure);
	//皮带方向控制IO口
	GPIO_InitStructure.GPIO_Pin = BELT12_DIR_IO;			 
	GPIO_Init(BELT12_DIR_PORT, &GPIO_InitStructure);
	//皮带控制器故障IO口
	GPIO_InitStructure.GPIO_Pin = BELT12_ERR_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(BELT12_ERR_PORT, &GPIO_InitStructure);
	//皮带传感器11 IO口
	GPIO_InitStructure.GPIO_Pin = BELT12_SENSOR1_IO;
	GPIO_Init(BELT12_SENSOR1_PORT, &GPIO_InitStructure);
	//皮带传感器12 IO口
	GPIO_InitStructure.GPIO_Pin = BELT12_SENSOR2_IO;
	GPIO_Init(BELT12_SENSOR2_PORT, &GPIO_InitStructure);
	
	belt12.speed_step = 0;
	belt12.start_ok = 0;
	BELT12_SPEED1 = 0;
	BELT12_SPEED2 = 0;
	BELT12_SPEED3 = 0;
	BELT12_DIR = 0;
}

//=============================================================================
//函数名称:BELT_Speed_Control
//功能概要:皮带速度控制函数
//参数名称:speed：皮带输入速度
//函数返回:无
//注意    :无
//=============================================================================
static void Belt11_Speed_Control(u8 speed)
{
	if(speed == 0){
		Belt11_Speed(0,0,0);	
	}else if(speed == 1){
		Belt11_Speed(0,0,1);
	}else if(speed == 2){
		Belt11_Speed(0,1,0);
	}else if(speed == 3){
		Belt11_Speed(0,1,1);
	}else if(speed == 4){
		Belt11_Speed(1,0,0);
	}else if(speed == 5){
		Belt11_Speed(1,0,1);
	}else if(speed == 6){
		Belt11_Speed(1,1,0);
	}else if(speed == 7){
		Belt11_Speed(1,1,1);
	}
}

//=============================================================================
//函数名称:Start_Belt
//功能概要:皮带电机软启动函数
//参数名称:step：电机速度也是电机运行状态步数
//函数返回:电机执行到哪一步的速度
//注意    :需要在定时器中断函数调用
//=============================================================================
static u8 Start_Belt11(u8 step)
{
	static u16 start_time = 0;
	switch(step){
	case 0x00:Belt11_Speed_Control(step);step++; break;
	case 0x01:Belt11_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;
	case 0x02:Belt11_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;						
	case 0x03:Belt11_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;
	case 0x04:Belt11_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;						
	case 0x05:Belt11_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT){step++;start_time = 0;} break;					
	case 0x06:Belt11_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;						
	case 0x07:Belt11_Speed_Control(step-1);start_time++;
						if(start_time >= START_TIMEOUT/4)
							{step++;start_time = 0;belt11.start_ok = 1;} break;						
	default:start_time = 0; break;
	}
	return step;
}
//=============================================================================
//函数名称:Stop_Belt11
//功能概要:电机软停止函数
//参数名称:step：电机速度也是电机运行状态步数
//函数返回:电机执行到哪一步的速度
//注意    :需要在定时器中断函数调用
//=============================================================================
static u8 Stop_Belt11(u8 step)
{
	static u16 stop_time = 0;
	switch(step){
	case 0x01:Belt11_Speed_Control(step-1);step--;stop_time = 0;belt11.start_ok = 0;break;
	case 0x02:Belt11_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/4){step--;stop_time = 0;} break;	
	case 0x03:Belt11_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/4){step--;stop_time = 0;} break;	
	case 0x04:Belt11_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	case 0x05:Belt11_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	case 0x06:Belt11_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	case 0x07:Belt11_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	case 0x08:Belt11_Speed_Control(step-2);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	default:Belt11_Speed_Control(0);stop_time = 0; break;
	}
		return step;
}

//=============================================================================
//函数名称:BELT_Speed_Control
//功能概要:皮带速度控制函数
//参数名称:speed：皮带输入速度
//函数返回:无
//注意    :无
//=============================================================================
static void Belt12_Speed_Control(u8 speed)
{
	if(speed == 0){
		Belt12_Speed(0,0,0);	
	}else if(speed == 1){
		Belt12_Speed(0,0,1);
	}else if(speed == 2){
		Belt12_Speed(0,1,0);
	}else if(speed == 3){
		Belt12_Speed(0,1,1);
	}else if(speed == 4){
		Belt12_Speed(1,0,0);
	}else if(speed == 5){
		Belt12_Speed(1,0,1);
	}else if(speed == 6){
		Belt12_Speed(1,1,0);
	}else if(speed == 7){
		Belt12_Speed(1,1,1);
	}
}

//=============================================================================
//函数名称:Start_Belt
//功能概要:皮带电机软启动函数
//参数名称:step：电机速度也是电机运行状态步数
//函数返回:电机执行到哪一步的速度
//注意    :需要在定时器中断函数调用
//=============================================================================
static u8 Start_Belt12(u8 step)
{
	static u16 start_time = 0;
	switch(step){
	case 0x00:Belt12_Speed_Control(step);step++; break;
	case 0x01:Belt12_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;
	case 0x02:Belt12_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;						
	case 0x03:Belt12_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;
	case 0x04:Belt12_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;						
	case 0x05:Belt12_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT){step++;start_time = 0;} break;					
	case 0x06:Belt12_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;						
	case 0x07:Belt12_Speed_Control(step-1);start_time++;
						if(start_time >= START_TIMEOUT/4)
							{step++;start_time = 0;belt12.start_ok = 1;} break;						
	default:start_time = 0; break;
	}
	return step;
}
//=============================================================================
//函数名称:Stop_Belt11
//功能概要:电机软停止函数
//参数名称:step：电机速度也是电机运行状态步数
//函数返回:电机执行到哪一步的速度
//注意    :需要在定时器中断函数调用
//=============================================================================
static u8 Stop_Belt21(u8 step)
{
	static u16 stop_time = 0;
	switch(step){
	case 0x01:Belt12_Speed_Control(step-1);step--;stop_time = 0;belt12.start_ok = 0;break;
	case 0x02:Belt12_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/4){step--;stop_time = 0;} break;	
	case 0x03:Belt12_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/4){step--;stop_time = 0;} break;	
	case 0x04:Belt12_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	case 0x05:Belt12_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	case 0x06:Belt12_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	case 0x07:Belt12_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	case 0x08:Belt12_Speed_Control(step-2);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	default:Belt12_Speed_Control(0);stop_time = 0; break;
	}
		return step;
}
//=============================================================================
//函数名称:Belt_Control
//功能概要:皮带控制
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void Belt11_Control(void)
{
			if((READ_BELT11_SENSOR1 == 0)||(READ_BELT11_SENSOR2 == 0)){
			delay_ms(10);	
			if((READ_BELT11_SENSOR1 == 0)||(READ_BELT11_SENSOR2 == 0)){
				if(belt11.start_signal == 0){
					belt11.start_signal = 1;	
					belt11.stop_signal  = 0;
					belt11.start_ok = 0;
					belt11.stop_ok = 0;
					belt11.stop_delay_state = 0;
					if(belt11.speed_step>0){
						belt11.speed_step--; 
					}
				}
			}
		}else{
			if(belt11.start_ok == 1){
				belt11.stop_delay_state = 1;
				belt11.start_ok = 0;
				belt11.start_signal = 0;
			}
			if(belt11.stop_ok == 1){
				belt11.stop_signal = 1;
				belt11.start_signal = 0;
				belt11.stop_ok = 0;
			}
		}
}

//=============================================================================
//函数名称:Belt_Control
//功能概要:皮带控制
//参数名称:无
//函数返回:无
//注意    :无 
//=============================================================================
void Belt12_Control(void)
{
			if((READ_BELT12_SENSOR1 == 0)||(READ_BELT12_SENSOR2 == 0)){
			delay_ms(10);	
			if((READ_BELT12_SENSOR1 == 0)||(READ_BELT12_SENSOR2 == 0)){
				if(belt12.start_signal == 0){
					belt12.start_signal = 1;	
					belt12.stop_signal  = 0;
					belt12.start_ok = 0;
					belt12.stop_ok = 0;
					belt12.stop_delay_state = 0;
					if(belt12.speed_step>0){
						belt12.speed_step--; 
					}
				}
			}
		}else{
			if(belt12.start_ok == 1){
				belt12.stop_delay_state = 1;
				belt12.start_ok = 0;
				belt12.start_signal = 0;
			}
			if(belt12.stop_ok == 1){
				belt12.stop_signal = 1;
				belt12.start_signal = 0;
				belt12.stop_ok = 0;
			}
		}
}
//=============================================================================
//函数名称:belt11_time_control
//功能概要:
//参数名称:无
//函数返回:无
//注意    :在5MS定时器内调用
//=============================================================================
void belt11_time_control(void) 
{
	static u16 stop_delay_time;

	if(belt11.start_signal ==1){
		belt11.speed_step = Start_Belt11(belt11.speed_step);
	}
	if(belt11.stop_signal == 1){
		belt11.speed_step = Stop_Belt11(belt11.speed_step);
	}
	if(belt11.stop_delay_state == 1){
		stop_delay_time++;
		if(stop_delay_time >= belt11.actual_time){
			belt11.stop_ok = 1;
			belt11.stop_delay_state = 0;
			stop_delay_time = 0;
		}
	}
}
//=============================================================================
//函数名称:belt21_time_control
//功能概要:
//参数名称:无
//函数返回:无
//注意    :在5MS定时器内调用
//=============================================================================
void belt12_time_control(void) 
{
	static u16 stop_delay_time;

	if(belt12.start_signal ==1){
		belt12.speed_step = Start_Belt12(belt12.speed_step);
	}
	if(belt12.stop_signal == 1){
		belt12.speed_step = Stop_Belt21(belt12.speed_step);
	}
	if(belt12.stop_delay_state == 1){
		stop_delay_time++;
		if(stop_delay_time >= belt12.actual_time){
			belt12.stop_ok = 1;
			belt12.stop_delay_state = 0;
			stop_delay_time = 0;
		}
	}
}









