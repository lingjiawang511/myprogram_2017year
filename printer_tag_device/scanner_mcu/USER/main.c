#include"HeadType.h"	
#include "usart.h"
#include "TIM.h"
u8 Device_State;

void param_init(void);
void delay_ms1(u16 ms)
{
	u16  i;
	u32  j;
	for(i=ms;i>0;i--)
	{
		for(j=5000;j>0;j--)
		;
	}
}
//配置时钟在target宏定义
int main(void)
{
		delay_init();
		Baffle_GPIO_Config();
	  Communication_GPIO_Config();
		USART1_Config();
		USART2_Config();
//		EXTIX_Init();
		LED_GPIO_Config();
    TIM2_Config();
    TIM3_Config();
	  param_init();
		delay_ms(100);
    while(1){
//        Dispose_Data_For_Host();
//        Respond_Host_Comm();
//				if(Device_State == 1){
//					Baffle_Control_Process();
//				}
		}       
}

void param_init(void)
{
	 Device_State =0;
	 Baffle_Control.bag_err_flag = 0;
	 Baffle_Control.process_time = 0;
	 Baffle_Control.process_flag= 0;
	 Baffle_Control.Scanner_Err_Time = 0;
	 Baffle_Control.process_time = 0;
	 Control.baffle_inter.state = 0;
	 Control.baffle_outer.state = 0;
	 BAFFLE_INTER ;
}



