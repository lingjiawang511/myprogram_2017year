#include"HeadType.h"	

#define	DEVICE1_KEY_IO					GPIO_Pin_14
#define	DEVICE1_KEY_PORT				GPIOB

#define READ_DEVICE1_KEY    		GPIO_ReadInputDataBit(DEVICE1_KEY_PORT,DEVICE1_KEY_IO) //返回的是一个字节，读的是一个位


#define KEY_SHORT_TIME 		20
#define KEY_LONG_TIME			300
u8 Key_ScanNum;

//=============================================================================
//函数名称: KEY_GPIO_Config
//功能概要:LED灯引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void KEY_GPIO_Config(void)
{	
	//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	//使能GPIOC的外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//选择要用的GPIO引脚		
	GPIO_InitStructure.GPIO_Pin = DEVICE1_KEY_IO;
	///设置引脚模式为推免输出模式			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	//设置引脚速度为50MHZ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	//调用库函数，初始化GPIO
	GPIO_Init(DEVICE1_KEY_PORT, &GPIO_InitStructure);

}

u8 Key_Scan(void)
{
	 u8 key_num;
	 static u8 key1_triggerstate;
	 static u16 key1_timercount;
	  key_num = 0;
	 //key1
		if(READ_DEVICE1_KEY == READLOW){
			if(key1_triggerstate == 0){
				key1_triggerstate = 1;
			}else{
				key1_timercount++;
			}
		}else{
				if(key1_triggerstate == 1){
					if(key1_timercount <KEY_SHORT_TIME){
						key_num &=0xfe;
					}else if((key1_timercount >=KEY_SHORT_TIME)&&(key1_timercount <KEY_LONG_TIME)){
							key_num |=0x01;
					}else{
							key_num |=0x11;
					}
					key1_triggerstate =0;				
				}
				key1_timercount = 0;
		}
	
	 return key_num;
}
