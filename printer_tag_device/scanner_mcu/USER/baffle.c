#include"HeadType.h"	

#define SCANNER_ERR_TIME  140 //液带进入而扫描不到二维码的时间
#define BAG_ERR_TIME  140		//扫描不到二维码到此液带送走的时间
#define PROCESS_TIME  200
Control_Baffle_Type Baffle_Control;

//=============================================================================
//函数名称: Printer_GPIO_Config
//功能概要:打印机引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
 void Baffle_GPIO_Config(void)
{	
	//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	//翻板外翻到达输入IO配置
	RCC_APB2PeriphClockCmd(BAFFLE_OUTER_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = BAFFLE_OUTER_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(BAFFLE_OUTER_PORT, &GPIO_InitStructure);
	//翻板内翻到达输入IO配置
	RCC_APB2PeriphClockCmd(BAFFLE_INTER_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = BAFFLE_INTER_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(BAFFLE_INTER_PORT, &GPIO_InitStructure);
	//扫描枪信号输入IO配置
	RCC_APB2PeriphClockCmd(SCANNER_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = SCANNER_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(SCANNER_PORT, &GPIO_InitStructure);

	//翻板电磁阀输出IO配置
	RCC_APB2PeriphClockCmd(BAFFLE_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = BAFFLE_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(BAFFLE_PORT, &GPIO_InitStructure);

}
//挡板没事时都是处在错误的地方，扫描传感器有信号输入开始算两个时间，一个时间是有信号时扫描枪扫到二维码的时间，此时间内扫不到二维码
//给上位机上传一个错误的二维码，让上位机给我一个错误标志；另一个时间是过程总时间，既是传感器有信号到液带运行到终点皮带运行的时间，
//这个时间一到，如果上位机没有给我正确信号，我就当错误处理。
void Baffle_Control_Process(void)
{
	if(Control.scanner.state == 1){
			Baffle_Control.Scanner_Err_Time = SCANNER_ERR_TIME;		//扫描枪传感器检测到有液带信号，一段时间内扫描枪没有扫到二维码，当作为是错误的液带
			Baffle_Control.bag_input_flag= 1;
		  Baffle_Control.process_flag = 1;
			Baffle_Control.process_time = 0;
		  Control.scanner.state = 0;
	}
	if(Baffle_Control.bag_input_flag ==1){   //此状态清零需要在扫描抢接收到二维码的时候,在此扫不到二维码就上传一个错误信息给上位机
			if(Baffle_Control.Scanner_Err_Time ==0){//然后上位机已经给我一个错误信号标志，如果不给，我也知道错误
				Baffle_Control.bag_err_flag = 1;
//				Baffle_Control.bag_Err_Time = BAG_ERR_TIME;
				Update_Err_Scanner_Data();
				BAFFLE_INTER ;																	//挡板先拨打错误的地方等待
				Baffle_Control.bag_input_flag = 0;
			}
	}
//	if(Baffle_Control.bag_err_flag == 1){
//			if(Baffle_Control.bag_Err_Time == 0){  //液带运行到出口
//					if(Control.baffle_inter.state == 1){
//             BAFFLE_ON;
//						 Control.baffle_inter.state = 0;
//						 Baffle_Control.bag_err_flag = 0;
//					}
//			}
//	}
	if(Baffle_Control.process_time >= PROCESS_TIME){  //每个过程的时间是固定的
		 if(Baffle_Control.bag_ok_flag == 1){  //扫描枪扫到二维码，上位机发来的确认标志
				BAFFLE_OUTER;
				Control.baffle_inter.state = 0;
			  Control.baffle_outer.state = 0;
			  Baffle_Control.bag_ok_flag = 0;
		}else{
				BAFFLE_INTER ;	
			  Control.baffle_outer.state = 0;
			  Baffle_Control.bag_ok_flag = 1;
		}
	  Baffle_Control.bag_err_flag = 0;
		Baffle_Control.process_time = 0;
		Baffle_Control.process_flag= 0;
	}

}

void Baffle_Time_Irq(void)
{
	 static u16 inter_delay_time=0;
	 static u16 outer_delay_time=0;
		if(Baffle_Control.Scanner_Err_Time > 0){
			Baffle_Control.Scanner_Err_Time--;
		}
//    if(Baffle_Control.bag_Err_Time > 0){
//			Baffle_Control.bag_Err_Time--;
//		}
   if(Baffle_Control.process_flag == 1){
			Baffle_Control.process_time++;
		}
		
		if(Control.baffle_inter.state == 1){   //挡板位置中断状态，现在相当于无用
				inter_delay_time++;
			 if(inter_delay_time >= 20){
					inter_delay_time = 0;
				  Control.baffle_inter.state = 0;
				}
		}
		if(Control.baffle_outer.state == 1){ //此传感器如果没有，可以用延时状态为代替
				outer_delay_time++;
			 if(outer_delay_time >= 300){
					outer_delay_time = 0;
				  BAFFLE_INTER ;
				  Control.baffle_outer.state = 0;
				}
		}
}












