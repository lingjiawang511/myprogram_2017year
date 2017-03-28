#include"HeadType.h"	
#include "usart.h"
#include "TIM.h"

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
		USART1_Config();
		LED_GPIO_Config();
		RS485_GPIO_Config();
		KEY_GPIO_Config();
    TIM2_Config();
    TIM3_Config();  
		delay_ms(100);
		RLED_ON;
	  delay_ms(1000);
	  RLED_OFF;
		RS485_REC;
    while(1){
				Communication_Process();
		}       
}




