#include"HeadType.h"

#define LOCK_SHORT_TIME 		20
#define LOCK_LONG_TIME			300
u8 Lock1_State;
u8 Lock2_State;
u16 lock1_time;
u16 lock2_time;
//=============================================================================
//函数名称: LED_GPIO_Config
//功能概要:LED灯引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void LOCK_GPIO_Config(void)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;
	//LOCK1开锁输出信号
	RCC_APB2PeriphClockCmd(LOCK1_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK1_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK1_PORT, &GPIO_InitStructure);
	//LOCK2开锁输出信号
	RCC_APB2PeriphClockCmd(LOCK2_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK2_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK2_PORT, &GPIO_InitStructure);
	//LOCK1状态检查输入信号
	RCC_APB2PeriphClockCmd(LOCK1_CHECK_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK1_CHECK_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK1_CHECK_PORT, &GPIO_InitStructure);
	//LOCK2状态检查输入信号
	RCC_APB2PeriphClockCmd(LOCK2_CHECK_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK2_CHECK_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK2_CHECK_PORT, &GPIO_InitStructure);
	
	//LOCK1开锁指示灯1
	RCC_APB2PeriphClockCmd(LOCK1_LIGHT1_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK1_LIGHT1_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK1_LIGHT1_PORT, &GPIO_InitStructure);
	
	//LOCK1开锁指示灯2
	RCC_APB2PeriphClockCmd(LOCK1_LIGHT2_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK1_LIGHT2_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK1_LIGHT2_PORT, &GPIO_InitStructure);

	//LOCK2开锁指示灯1
	RCC_APB2PeriphClockCmd(LOCK2_LIGHT1_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK2_LIGHT1_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK2_LIGHT1_PORT, &GPIO_InitStructure);

	//LOCK2开锁指示灯1
	RCC_APB2PeriphClockCmd(LOCK2_LIGHT2_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK2_LIGHT2_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK2_LIGHT2_PORT, &GPIO_InitStructure);
	
	
	LOCK1_LIGHT_OFF();
	LOCK2_LIGHT_OFF();
	LOCK1_OFF;
	LOCK2_OFF;
}

void Lock_control(void )
{
	 static u8 lock1_triggerstate;
	 static u16 lock1_timercount;
	 static u8 lock2_triggerstate;
	 static u16 lock2_timercount;
	 //LOCK1
	 if(Lock1_State == 1){	
			if(READ_LOCK1_CHECK == READLOW){
				if(lock1_triggerstate == 0){
					lock1_triggerstate = 1;
				}else{
					lock1_timercount++;
				}
				if(lock1_timercount >= LOCK_SHORT_TIME){
						LOCK1_LIGHT_ON();//检测到锁打开了，开灯并且关闭开锁信号,只有关闭了开锁信号，才可以人工关门
						LOCK1_OFF;
						Lock1_State = 2;
						lock1_triggerstate = 0;
						lock1_timercount = 0;
				}
			}
	 }else if(Lock1_State == 2){//开灯之后一直检查锁的状态，如果锁已经重新锁上，应该灭灯
			if(READ_LOCK1_CHECK == READHIGH){
				if(lock1_triggerstate == 0){
					lock1_triggerstate = 1;
				}else{
					lock1_timercount++;
				}
				if(lock1_timercount >= LOCK_SHORT_TIME){
						LOCK1_LIGHT_OFF();//关灯
						LOCK1_OFF;
						Lock1_State = 0;
						lock1_triggerstate = 0;
						lock1_timercount = 0;
				}
			}
	 }else{
				lock1_triggerstate = 0;
				lock1_timercount = 0;
	 }
	 	 //LOCK2
	 if(Lock2_State == 1){
			if(READ_LOCK2_CHECK == READLOW){
				if(lock2_triggerstate == 0){
					lock2_triggerstate = 1;
				}else{
					lock2_timercount++;
				}
				if(lock2_timercount >= LOCK_SHORT_TIME){
						LOCK2_LIGHT_ON();//检测到锁打开了，开灯并且关闭开锁信号,只有关闭了开锁信号，才可以人工关门
						LOCK2_OFF;
						Lock2_State = 2;
						lock2_triggerstate = 0;
						lock2_timercount = 0;
				}
			}
	 }else if(Lock2_State == 2){//开灯之后一直检查锁的状态，如果锁已经重新锁上，应该灭灯
			if(READ_LOCK2_CHECK == READHIGH){
				if(lock2_triggerstate == 0){
					lock2_triggerstate = 1;
				}else{
					lock2_timercount++;
				}
				if(lock2_timercount >= LOCK_SHORT_TIME){
						LOCK2_LIGHT_OFF();//关灯
						LOCK2_OFF;
						Lock2_State = 0;
						lock2_triggerstate = 0;
						lock2_timercount = 0;
				}
			}
	 }else{
				lock2_triggerstate = 0;
				lock2_timercount = 0;
	 }
	 if(Lock1_State > 0){
			 lock1_time--;
			 if(lock1_time <= 0){
				 LOCK1_OFF;
				 lock1_time = LOCK_TIME;
			}
	}
	if(Lock2_State > 0){
			 lock2_time--;
			 if(lock2_time <= 0){
				 LOCK2_OFF;
				 lock2_time = LOCK_TIME;
			}
	}
}















