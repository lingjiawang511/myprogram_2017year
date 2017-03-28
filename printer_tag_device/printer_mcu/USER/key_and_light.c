#include"HeadType.h"	


#define	START_KEY_IO					GPIO_Pin_6
#define	START_KEY_PORT				GPIOA
#define	START_KEY_RCC				  RCC_APB2Periph_GPIOA
#define	STOP_KEY_IO					  GPIO_Pin_5
#define	STOP_KEY_PORT				  GPIOA
#define	STOP_KEY_RCC				  RCC_APB2Periph_GPIOA
 
#define READ_START_KEY    		GPIO_ReadInputDataBit(START_KEY_PORT,START_KEY_IO) //返回的是一个字节，读的是一个位
#define READ_STOP_KEY    		  GPIO_ReadInputDataBit(STOP_KEY_PORT,STOP_KEY_IO) //返回的是一个字节，读的是一个位

#define	START_LIGHT_IO				GPIO_Pin_4
#define	START_LIGHT_PORT			GPIOA
#define	START_LIGHT_RCC				RCC_APB2Periph_GPIOA
#define	STOP_LIGHT_IO					GPIO_Pin_3
#define	STOP_LIGHT_PORT				GPIOA
#define	STOP_LIGHT_RCC				RCC_APB2Periph_GPIOA
 
#define START_LIGHT_ON  		 	GPIO_SetBits(START_LIGHT_PORT, START_LIGHT_IO)
#define START_LIGHT_OFF  			GPIO_ResetBits(START_LIGHT_PORT, START_LIGHT_IO)
#define STOP_LIGHT_ON   			GPIO_SetBits(STOP_LIGHT_PORT, STOP_LIGHT_IO)
#define STOP_LIGHT_OFF  			GPIO_ResetBits(STOP_LIGHT_PORT,STOP_LIGHT_IO)

#define KEY_SHORT_TIME 		    10
#define KEY_LONG_TIME			    300
#define KEY_LONGLONG_TIME			400
u8 Key_ScanNum;
u8 Device_State = 2;

//=============================================================================
//函数名称: KEY_GPIO_Config
//功能概要:按钮引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void KEY_GPIO_Config(void)
{	
	//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	//停止按键IO配置
	RCC_APB2PeriphClockCmd(STOP_KEY_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = STOP_KEY_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(STOP_KEY_PORT, &GPIO_InitStructure);
	//启动按键IO配置
	RCC_APB2PeriphClockCmd(START_KEY_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = START_KEY_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(START_KEY_PORT, &GPIO_InitStructure);
}
//=============================================================================
//函数名称: Light_GPIO_Config
//功能概要:灯引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void Light_GPIO_Config(void)
{	
	//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	//停止按键IO配置
	RCC_APB2PeriphClockCmd(STOP_LIGHT_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = STOP_LIGHT_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(STOP_LIGHT_PORT, &GPIO_InitStructure);
	//启动按键IO配置
	RCC_APB2PeriphClockCmd(START_LIGHT_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = START_LIGHT_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(START_LIGHT_PORT, &GPIO_InitStructure);
}
static u8 Key_Scan(void)
{
	 u8 key_num;
	 static u8  start_key_triggerstate;
	 static u16 start_key_timercount;
	 static u8 stop_key_triggerstate;
	 static u16 stop_key_timercount;
	 key_num = 0;
	 //start_key
		if(READ_START_KEY == READLOW){
				if(start_key_triggerstate == 0){
					start_key_triggerstate = 1;
				}else if(start_key_triggerstate == 1){
					start_key_timercount++;
					if(start_key_timercount > KEY_LONG_TIME){
						key_num |=0x11;
						start_key_triggerstate = 2;
						start_key_timercount = 0;
						return key_num;
					}
				}
		}else{
				if(start_key_triggerstate >= 1){
					if(start_key_timercount <KEY_SHORT_TIME){
							key_num &=0xfe;
					}else if((start_key_timercount >=KEY_SHORT_TIME)&&(start_key_timercount <KEY_LONG_TIME)){
							key_num |=0x01;
					}
					start_key_triggerstate =0;	
				  return key_num;					
				}
				start_key_timercount = 0;
			}
	 //stop_key
		if(READ_STOP_KEY == READLOW){
				if(stop_key_triggerstate == 0){
					stop_key_triggerstate = 1;
				}else{
					stop_key_timercount++;
					if(stop_key_timercount > KEY_LONG_TIME){
						key_num |=0x12;
						stop_key_triggerstate = 2;
						stop_key_timercount = 0;
						return key_num;
					}
				}
		}else{
				if(stop_key_triggerstate >= 1){
					if(stop_key_timercount <KEY_SHORT_TIME){
							key_num &=0xfd;
					}else if((stop_key_timercount >=KEY_SHORT_TIME)&&(stop_key_timercount <KEY_LONG_TIME)){
							key_num |=0x02;
					}
					stop_key_triggerstate =0;				
				}
				stop_key_timercount = 0;
			}
	 return key_num;
}

static void Light_Scan(void)
{
	static u8 flash_time =100;
	static u8 flash_flag = 0;
  if(Device_State == 1){//Device_State=0：待机状态，Device_State=1：启动状态，Device_State=2：停止状态
		START_LIGHT_ON;
		STOP_LIGHT_OFF;
	}else if(Device_State == 2){
    STOP_LIGHT_ON;
		START_LIGHT_OFF;
	}else if(Device_State == 3){
		START_LIGHT_OFF;
		if(flash_time >0){
			flash_time --;
		}else{
			flash_time = 100;
			if(flash_flag == 0){
        STOP_LIGHT_ON;
				flash_flag = 1;
			}else{
				STOP_LIGHT_OFF;
				flash_flag = 0;
			}
		}
	
	}else{
		STOP_LIGHT_OFF;
		START_LIGHT_OFF;
	}
}


void Key_Light_Init(void)
{
		KEY_GPIO_Config();
		Light_GPIO_Config();
}

void Key_Light_Dispose(void)
{
  if(Key_ScanNum ==0){
		Key_ScanNum = Key_Scan();
	}
	if(Key_ScanNum !=0){  
		if(((Key_ScanNum&0x01) == 0x01)||((Key_ScanNum&0x11) == 0x11)){
			if(Device_State == 3){
				Device_State = 3;
			}else{
				if(READ_UPPER_REACH==0){
					Device_State = 1; 
				}else{
					Device_State = 3;
				}
			}
		}else if(((Key_ScanNum&0x02) == 0x02)||((Key_ScanNum&0x12) == 0x12)){
			Device_State = 2;  
		}else{
//			Device_State = 0;   //长按启动按键不放手，可以回到待机状态
		}
		Key_ScanNum = 0;
	}
	Light_Scan();
}



