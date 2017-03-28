#include"HeadType.h"

#define LOCK_SHORT_TIME 		20
#define LOCK_LONG_TIME			300
#define LOCK_STATE_COUNT    3			//锁检查滤波次数，在定时器调用就相当于滤波时间

u8 Check_State;					//上位机主动查询状态变量，给上位机控制
u8 Lock_Check_state;		//锁状态变量
Lock_Type Lock;
//=============================================================================
//函数名称: LOCK_GPIO_Config
//功能概要:LOCK引脚配置
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
		//LOCK3开锁输出信号
	RCC_APB2PeriphClockCmd(LOCK3_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK3_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK3_PORT, &GPIO_InitStructure);
	//LOCK4开锁输出信号
	RCC_APB2PeriphClockCmd(LOCK4_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK4_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK4_PORT, &GPIO_InitStructure);
	
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
	//LOCK3状态检查输入信号
	RCC_APB2PeriphClockCmd(LOCK3_CHECK_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK3_CHECK_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK3_CHECK_PORT, &GPIO_InitStructure);
	//LOCK4状态检查输入信号
	RCC_APB2PeriphClockCmd(LOCK4_CHECK_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK4_CHECK_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK4_CHECK_PORT, &GPIO_InitStructure);	
	
	//LOCK1开锁指示灯1
	RCC_APB2PeriphClockCmd(LOCK1_LIGHT1_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK1_LIGHT1_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK1_LIGHT1_PORT, &GPIO_InitStructure);
	
	//LOCK1开锁指示灯2,这个现在是灯的亮度调节IO
	RCC_APB2PeriphClockCmd(LOCK1_LIGHT2_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = LOCK1_LIGHT2_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LOCK1_LIGHT2_PORT, &GPIO_InitStructure);

//	//LOCK2开锁指示灯1
//	RCC_APB2PeriphClockCmd(LOCK2_LIGHT1_RCC,ENABLE);
//	GPIO_InitStructure.GPIO_Pin = LOCK2_LIGHT1_IO;			 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//	GPIO_Init(LOCK2_LIGHT1_PORT, &GPIO_InitStructure);

//	//LOCK2开锁指示灯1
//	RCC_APB2PeriphClockCmd(LOCK2_LIGHT2_RCC,ENABLE);
//	GPIO_InitStructure.GPIO_Pin = LOCK2_LIGHT2_IO;			 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//	GPIO_Init(LOCK2_LIGHT2_PORT, &GPIO_InitStructure);
	
	
	LOCK1_LIGHT_OFF();
	LOCK1_OFF;
	LOCK2_OFF;
	Lock.lock1.lock_check_state = 0;
	Lock.lock2.lock_check_state = 0;
	Lock.lock3.lock_check_state = 0;
	Lock.lock4.lock_check_state = 0;
	Check_State =0 ;
}

//锁的控制和检测分开，因为所的控制需要控制灯，并且人工关锁的时候要自动关灯，但是锁的状态改变需要上传给PC
//=============================================================================
//函数名称: Lock_control_12
//功能概要:锁12控制函数
//参数名称:无
//函数返回:无
//注意    :需在定时器调用
//=============================================================================
static void Lock_control_12(void )
{
	 static u8 lock1_triggerstate;
	 static u16 lock1_timercount;
	 static u8 lock2_triggerstate;
	 static u16 lock2_timercount;
	 //LOCK1
	 if(Lock.lock1.lock_state == 1){	
			if(READ_LOCK1_CHECK == READLOW){   //锁是关的，才打开，不然没有意义
				if(lock1_triggerstate == 0){
					lock1_triggerstate = 1;
				}else{
					lock1_timercount++;
				}
				if(lock1_timercount >= LOCK_SHORT_TIME){
						LOCK1_LIGHT_ON_H();//检测到锁打开了，开灯并且关闭开锁信号,只有关闭了开锁信号，才可以人工关门
						LOCK1_OFF;
						Lock.lock1.lock_state = 2;
						lock1_triggerstate = 0;
						lock1_timercount = 0;
				}
			}
	 }else if(Lock.lock1.lock_state == 2){//开灯之后一直检查锁的状态，如果锁已经重新锁上，应该灭灯
			if(READ_LOCK1_CHECK == READHIGH){
				if(lock1_triggerstate == 0){
					lock1_triggerstate = 1;
				}else{
					lock1_timercount++;
				}
				if(lock1_timercount >= LOCK_SHORT_TIME){
//						LOCK1_LIGHT_OFF();//关灯
						LOCK1_OFF;
						Lock.lock1.lock_state = 0;
						lock1_triggerstate = 0;
						lock1_timercount = 0;
				}
			}
	 }else{
				lock1_triggerstate = 0;
				lock1_timercount = 0;
	 }
	 	 //LOCK2
	 if(Lock.lock2.lock_state == 1){
			if(READ_LOCK2_CHECK == READLOW){
				if(lock2_triggerstate == 0){
					lock2_triggerstate = 1;
				}else{
					lock2_timercount++;
				}
				if(lock2_timercount >= LOCK_SHORT_TIME){
//						LOCK2_LIGHT_ON();//检测到锁打开了，开灯并且关闭开锁信号,只有关闭了开锁信号，才可以人工关门
					  LOCK1_LIGHT_ON_H();//检测到锁打开了，开灯并且关闭开锁信号,只有关闭了开锁信号，才可以人工关门
						LOCK2_OFF;
						Lock.lock2.lock_state = 2;
						lock2_triggerstate = 0;
						lock2_timercount = 0;
				}
			}
	 }else if(Lock.lock2.lock_state == 2){//开灯之后一直检查锁的状态，如果锁已经重新锁上，应该灭灯
			if(READ_LOCK2_CHECK == READHIGH){
				if(lock2_triggerstate == 0){
					lock2_triggerstate = 1;
				}else{
					lock2_timercount++;
				}
				if(lock2_timercount >= LOCK_SHORT_TIME){
//						LOCK2_LIGHT_OFF();//关灯
//				  	LOCK1_LIGHT_OFF();//关灯
						LOCK2_OFF;
						Lock.lock2.lock_state = 0;
						lock2_triggerstate = 0;
						lock2_timercount = 0;
				}
			}
	 }else{
				lock2_triggerstate = 0;
				lock2_timercount = 0;
	 }
	 
	 if(Lock.lock1.lock_state > 0){   //最长开锁时间，如果锁是开的，上位机让MCU开锁，超时后状态复位
			 Lock.lock1.lock_time--;
			 if(Lock.lock1.lock_time <= 0){
				 LOCK1_OFF;
				 Lock.lock1.lock_time = LOCK_TIME;
			}
	}
	if(Lock.lock2.lock_state > 0){
			 Lock.lock2.lock_time--;
			 if(Lock.lock2.lock_time <= 0){
				 LOCK2_OFF;
				 Lock.lock2.lock_time = LOCK_TIME;
			}
	}
}
//锁的控制和检测分开，因为所的控制需要控制灯，并且人工关锁的时候要自动关灯，但是锁的状态改变需要上传给PC
//=============================================================================
//函数名称: Lock_control_34
//功能概要:锁34控制函数
//参数名称:无
//函数返回:无
//注意    :需在定时器调用
//=============================================================================
static void Lock_control_34(void )
{
	 static u8 lock3_triggerstate;
	 static u16 lock3_timercount;
	 static u8 lock4_triggerstate;
	 static u16 lock4_timercount;
	 //LOCK3
	 if(Lock.lock3.lock_state == 1){	
			if(READ_LOCK3_CHECK == READLOW){
				if(lock3_triggerstate == 0){
					lock3_triggerstate = 1;
				}else{
					lock3_timercount++;
				}
				if(lock3_timercount >= LOCK_SHORT_TIME){
						LOCK1_LIGHT_ON_H();//检测到锁打开了，开灯并且关闭开锁信号,只有关闭了开锁信号，才可以人工关门
						LOCK3_OFF;
						Lock.lock3.lock_state = 2;
						lock3_triggerstate = 0;
						lock3_timercount = 0;
				}
			}
	 }else if(Lock.lock3.lock_state == 2){//开灯之后一直检查锁的状态，如果锁已经重新锁上，应该灭灯
			if(READ_LOCK3_CHECK == READHIGH){
				if(lock3_triggerstate == 0){
					lock3_triggerstate = 1;
				}else{
					lock3_timercount++;
				}
				if(lock3_timercount >= LOCK_SHORT_TIME){
//						LOCK1_LIGHT_OFF();//关灯
						LOCK3_OFF;
						Lock.lock3.lock_state = 0;
						lock3_triggerstate = 0;
						lock3_timercount = 0;
				}
			}
	 }else{
				lock3_triggerstate = 0;
				lock3_timercount = 0;
	 }
	 	 //LOCK4
	 if(Lock.lock4.lock_state == 1){
			if(READ_LOCK4_CHECK == READLOW){
				if(lock4_triggerstate == 0){
					lock4_triggerstate = 1;
				}else{
					lock4_timercount++;
				}
				if(lock4_timercount >= LOCK_SHORT_TIME){
//						LOCK2_LIGHT_ON();//检测到锁打开了，开灯并且关闭开锁信号,只有关闭了开锁信号，才可以人工关门
					  LOCK1_LIGHT_ON_H();//检测到锁打开了，开灯并且关闭开锁信号,只有关闭了开锁信号，才可以人工关门
						LOCK4_OFF;
						Lock.lock4.lock_state = 2;
						lock4_triggerstate = 0;
						lock4_timercount = 0;
				}
			}
	 }else if(Lock.lock4.lock_state == 2){//开灯之后一直检查锁的状态，如果锁已经重新锁上，应该灭灯
			if(READ_LOCK4_CHECK == READHIGH){
				if(lock4_triggerstate == 0){
					lock4_triggerstate = 1;
				}else{
					lock4_timercount++;
				}
				if(lock4_timercount >= LOCK_SHORT_TIME){
//						LOCK2_LIGHT_OFF();//关灯
//				  	LOCK1_LIGHT_OFF();//关灯
						LOCK4_OFF;
						Lock.lock4.lock_state = 0;
						lock4_triggerstate = 0;
						lock4_timercount = 0;
				}
			}
	 }else{
				lock4_triggerstate = 0;
				lock4_timercount = 0;
	 }
	 
	 if(Lock.lock3.lock_state > 0){
			 Lock.lock3.lock_time--;
			 if(Lock.lock3.lock_time <= 0){
				 LOCK3_OFF;
				 Lock.lock3.lock_time = LOCK_TIME;
			}
	}
	if(Lock.lock4.lock_state > 0){
			 Lock.lock4.lock_time--;
			 if(Lock.lock4.lock_time <= 0){
				 LOCK4_OFF;
				 Lock.lock4.lock_time = LOCK_TIME;
			}
	}
}
//=============================================================================
//函数名称: Lock_check
//功能概要:锁状态检查函数
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void Lock_check(void )
{
	static u8 old_lock1_state,old_lock2_state,old_lock3_state,old_lock4_state;
  static u8 lock1_state_count,lock2_state_count,lock3_state_count,lock4_state_count;	
	
	if(Lock.lock1.lock_check_state == 0){
		if(old_lock1_state != READ_LOCK1_CHECK){
				lock1_state_count++;
				if(lock1_state_count >= LOCK_STATE_COUNT)
				{
					Lock.lock1.lock_check_state = 1;		//锁状态变化位，为1的时候需要主动上传数据，数据上传完之后清零
					Lock.lock1.lock_check_value = READ_LOCK1_CHECK;
					lock1_state_count = 0;
					old_lock1_state = Lock.lock1.lock_check_value;
				}
			}else{
					lock1_state_count = 0;
			}
	}
	if(Lock.lock2.lock_check_state == 0){
		if(old_lock2_state != READ_LOCK2_CHECK){
				lock2_state_count++;
				if(lock2_state_count >= LOCK_STATE_COUNT)
				{
					Lock.lock2.lock_check_state = 1;
					Lock.lock2.lock_check_value = READ_LOCK2_CHECK;
					lock2_state_count = 0;
					old_lock2_state = Lock.lock2.lock_check_value;
				}
			}else{
					lock2_state_count = 0;
			}
	 }
	if(Lock.lock3.lock_check_state == 0){
			if(old_lock3_state != READ_LOCK3_CHECK){
				lock3_state_count++;
				if(lock3_state_count >= LOCK_STATE_COUNT)
				{
					Lock.lock3.lock_check_state = 1;
					Lock.lock3.lock_check_value = READ_LOCK3_CHECK;
					lock3_state_count = 0;
					old_lock3_state = Lock.lock3.lock_check_value;
				}
			}else{
					lock3_state_count = 0;
			}
	 }
	 if(Lock.lock4.lock_check_state == 0){
			if(old_lock4_state != READ_LOCK4_CHECK){
				lock4_state_count++;
				if(lock4_state_count >= LOCK_STATE_COUNT)
				{
					Lock.lock4.lock_check_state = 1;
					Lock.lock4.lock_check_value = READ_LOCK4_CHECK;
					lock4_state_count = 0;
					old_lock4_state = Lock.lock4.lock_check_value;
					lock4_state_count = 0;
				}
			}else{
					lock4_state_count = 0;
			}
	}	
	if(Lock_Check_state == 0){
		if((Lock.lock1.lock_check_state ==1)||(Lock.lock2.lock_check_state ==1)||(Lock.lock2.lock_check_state ==1)||(Lock.lock4.lock_check_state ==1)){
				Lock_Check_state = 1;				
		}
	}
}
//=============================================================================
//函数名称: Lock_control
//功能概要:锁控制函数
//参数名称:无
//函数返回:无
//注意    :需在定时器调用
//=============================================================================
void Lock_control(void )
{
	Lock_control_12();
	Lock_control_34();
	if((Lock.lock1.lock_state > 0)||(Lock.lock2.lock_state > 0)||(Lock.lock3.lock_state > 0)||(Lock.lock4.lock_state > 0)){
		 LOCK1_LIGHT_ON_H();//检测到锁打开了，开灯并且关闭开锁信号,只有关闭了开锁信号，才可以人工关门
	}else{//四个锁都是关的状态，自动关灯
		LOCK1_LIGHT_OFF();//关灯
	}
	Lock_check();
}













