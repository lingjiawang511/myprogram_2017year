#include"HeadType.h"	
#include "usart.h"
#include "TIM.h"

Belt_Work_Type belt;
 Printer_Type Printer;
 Control_Input_Type Control;

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
		Key_Light_Init();
		Belt_Config();
		LED_GPIO_Config();
	  ROLL_PAPER_GPIO_Config();
	  Printer_GPIO_Config();
		Air_Cylinder_GPIO_Config();
		Baffle_GPIO_Config();
		EXTIX_Init();
    USART1_Config();
    TIM2_Config();
    TIM3_Config();
	  Baffle_Control.PC_send_process_time = 300;
	  Air_Control.PC_send_delay_time = 300;
		param_init();
		delay_ms(1000);
    while(1){
			Roll_Paper_Control();
			Printer_Control();
			Air_Cylinder_Control();
			Baffle_Control_Process();
			Respond_Host_Comm();
		}
        
}

void param_init(void)
{

	Air_Control.process = RESERVE;
	Air_Control.complete = 1;
	Air_Control.air_cylinder_position =IN_UP;

	Printer.complete = 0;
	Printer.process = PRINTER_RESERVE;
	PRINTER_START_OFF;
	
	Control.upper_reach.state = 0;
	Control.scanner.state = 0;
	Control.fit_reach.state = 0;
	Control.fluid_bag.state = 0;
	Printer.color_end.state = 0;
	Printer.color_less.state = 0;
	Printer.end.state = 0;
	Printer.err.state = 0;
	Printer.pinline.state = 0;
	Printer.tag_end.state = 0;
	Printer.input_state = 0;
	MCU_Host_Send.control.err_message = 0;
	Baffle_Control.process_time = Baffle_Control.PC_send_process_time;
  MCU_Host_Send.control.recom_state = 0;
	Baffle_Control.PC_send_scanner_result = 0;
	Baffle_Control.scanner_result_old = 0;
}


