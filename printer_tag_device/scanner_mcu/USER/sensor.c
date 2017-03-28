#include"HeadType.h"

#define SENSOR_COUNT    4			//锁检查滤波次数，在定时器调用就相当于滤波时间
#define SENSOR_TIME     200		//200*5ms,传感器在触发一次后，需要等这段时间才可以再触发
u8 Sensor_State;
Sensor_Type Sonser;

//=============================================================================
//函数名称: SENSOR_GPIO_Config
//功能概要:SENSOR引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void SENSOR_GPIO_Config(void)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;

	//SENSOR1状态检查输入信号
	RCC_APB2PeriphClockCmd(SENSOR1_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SENSOR1_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SENSOR1_PORT, &GPIO_InitStructure);

	//SENSOR2状态检查输入信号
	RCC_APB2PeriphClockCmd(SENSOR2_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SENSOR2_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SENSOR2_PORT, &GPIO_InitStructure);
	//SENSOR3状态检查输入信号
	RCC_APB2PeriphClockCmd(SENSOR3_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SENSOR3_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SENSOR3_PORT, &GPIO_InitStructure);
	//SENSOR4状态检查输入信号
	RCC_APB2PeriphClockCmd(SENSOR4_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SENSOR4_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SENSOR4_PORT, &GPIO_InitStructure);
	//SENSOR5状态检查输入信号
	RCC_APB2PeriphClockCmd(SENSOR5_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SENSOR5_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SENSOR5_PORT, &GPIO_InitStructure);
	//SENSOR6状态检查输入信号
	RCC_APB2PeriphClockCmd(SENSOR6_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SENSOR6_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SENSOR6_PORT, &GPIO_InitStructure);
	
	Sensor_State = 0;
	Sonser.sensor1.sensor_time = 0;
	Sonser.sensor2.sensor_time = 0;
	Sonser.sensor3.sensor_time = 0;
	Sonser.sensor4.sensor_time = 0;
	Sonser.sensor5.sensor_time = 0;
	Sonser.sensor6.sensor_time = 0;
}
//=============================================================================
//函数名称: Sensor_Time_Control
//功能概要:SENSOR坚持到信号后中断检测的时间
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void Sensor_Time_Control(void)
{
	if(Sonser.sensor1.sensor_time > 0){
		Sonser.sensor1.sensor_time--;
	}
	if(Sonser.sensor2.sensor_time > 0){
		Sonser.sensor2.sensor_time--;
	}
	if(Sonser.sensor3.sensor_time > 0){
		Sonser.sensor3.sensor_time--;
	}
	if(Sonser.sensor4.sensor_time > 0){
		Sonser.sensor4.sensor_time--;
	}
	if(Sonser.sensor5.sensor_time > 0){
		Sonser.sensor5.sensor_time--;
	}
	if(Sonser.sensor6.sensor_time > 0){
		Sonser.sensor6.sensor_time--;
	}
}

void Sensor_check(void )
{
	  static u8 sensor1_count,sensor2_count,sensor3_count,sensor4_count,sensor5_count,sensor6_count;
		if((Sonser.sensor1.sensor_state == 0)&&(Sonser.sensor1.sensor_time == 0)){
			//sensor1
			if(READ_SENSOR1_CHECK == READLOW){	//有信号,传感器信号像按键一样用
					sensor1_count++;
					if(sensor1_count >= SENSOR_COUNT)
					{
						Sonser.sensor1.sensor_state = 1;		
						Sonser.sensor1.sensor_check_value = 1;
						Sonser.sensor1.sensor_time = SENSOR_TIME;
						sensor1_count = 0;
					}
			}else{
					sensor1_count = 0;
			}
		}
		if((Sonser.sensor2.sensor_state == 0)&&(Sonser.sensor2.sensor_time == 0)){
			//sensor2
			if(READ_SENSOR2_CHECK == READLOW){	//有信号,传感器信号像按键一样用
					sensor2_count++;
					if(sensor2_count >= SENSOR_COUNT)
					{
						Sonser.sensor2.sensor_state = 1;		
						Sonser.sensor2.sensor_check_value = 1;
						Sonser.sensor2.sensor_time = SENSOR_TIME;
						sensor2_count = 0;
					}
			}else{
					sensor2_count = 0;
			}	
		}
		if((Sonser.sensor3.sensor_state == 0)&&(Sonser.sensor3.sensor_time == 0)){
			//sensor3
			if(READ_SENSOR3_CHECK == READLOW){	//有信号,传感器信号像按键一样用
					sensor3_count++;
					if(sensor3_count >= SENSOR_COUNT)
					{
						Sonser.sensor3.sensor_state = 1;		
						Sonser.sensor3.sensor_check_value = 1;
						Sonser.sensor3.sensor_time = SENSOR_TIME;
						sensor3_count = 0;
					}
			}else{
					sensor3_count = 0;
			}
		}
		if((Sonser.sensor4.sensor_state == 0)&&(Sonser.sensor4.sensor_time == 0)){
			//sensor4
			if(READ_SENSOR4_CHECK == READLOW){	//有信号,传感器信号像按键一样用
					sensor4_count++;
					if(sensor4_count >= SENSOR_COUNT)
					{
						Sonser.sensor4.sensor_state = 1;		
						Sonser.sensor4.sensor_check_value = 1;
						Sonser.sensor4.sensor_time = SENSOR_TIME;
						sensor4_count = 0;
					}
			}else{
					sensor4_count = 0;
			}
		}
		if((Sonser.sensor5.sensor_state == 0)&&(Sonser.sensor5.sensor_time == 0)){
			//sensor5
			if(READ_SENSOR5_CHECK == READLOW){	//有信号,传感器信号像按键一样用
					sensor5_count++;
					if(sensor5_count >= SENSOR_COUNT)
					{
						Sonser.sensor5.sensor_state = 1;		
						Sonser.sensor5.sensor_check_value = 1;
						Sonser.sensor5.sensor_time = SENSOR_TIME;
						sensor5_count = 0;
					}
			}else{
					sensor5_count = 0;
			}
		}
		if((Sonser.sensor6.sensor_state == 0)&&(Sonser.sensor6.sensor_time == 0)){
			//sensor6
			if(READ_SENSOR6_CHECK == READLOW){	//有信号,传感器信号像按键一样用
					sensor6_count++;
					if(sensor6_count >= SENSOR_COUNT)
					{
						Sonser.sensor6.sensor_state = 1;		
						Sonser.sensor6.sensor_check_value = 1;
						Sonser.sensor6.sensor_time = SENSOR_TIME;
						sensor6_count = 0;
					}
			}else{
					sensor6_count = 0;
			}
		}
		if(Sensor_State == 0){		//
			if((Sonser.sensor1.sensor_state == 1)||(Sonser.sensor2.sensor_state == 1)||(Sonser.sensor3.sensor_state == 1)||\
				(Sonser.sensor4.sensor_state == 1)||(Sonser.sensor5.sensor_state == 1)||(Sonser.sensor6.sensor_state == 1)){
					Sensor_State = 1;
					Sonser.sensor1.sensor_state = 0;
					Sonser.sensor2.sensor_state = 0;
					Sonser.sensor3.sensor_state = 0;
					Sonser.sensor4.sensor_state = 0;
					Sonser.sensor5.sensor_state = 0;
					Sonser.sensor6.sensor_state = 0;
			}
		}
		
		Sensor_Time_Control();
}
















