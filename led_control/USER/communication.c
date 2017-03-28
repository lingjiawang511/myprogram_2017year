#include"HeadType.h"


COMM_Rec_Union_Type  MCU_Host_Rec;//MCU作为主机时的结构体接收应答变量
static u8 slave_rec_state;

//=============================================================================
//函数名称: LED_GPIO_Config
//功能概要:LED灯引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void RS485_GPIO_Config(void)
{	
	//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	//使能GPIOC的外设时钟
	RCC_APB2PeriphClockCmd(RS485EN_RCC,ENABLE);	
	GPIO_InitStructure.GPIO_Pin = RS485EN_IO;		 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(RS485EN_PORT, &GPIO_InitStructure);
	

}

//=============================================================================
//函数名称:Respond_Host_Comm
//功能概要:响应上位机的发出的数据命令，数据已经从串口一接收完整
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
static void Respond_Host_Comm(void)
{
		u8 i;
		u16 crc;
//	  u8 res;
//		static u8 slaveaddr = 3;
		if(Usart1_Control_Data.rx_count < 22){
				return;
		}
//		if((Usart1_Control_Data.rxbuf[2] != slaveaddr)||(Usart1_Control_Data.rxbuf[5] != Usart1_Control_Data.rx_count - 10)){
//				return ;
//		}
//		crc=CRC_GetCCITT(Usart1_Control_Data.rxbuf,Usart1_Control_Data.rx_count-4);
			crc=LRC16(&Usart1_Control_Data.rxbuf[1],Usart1_Control_Data.rx_count-5);	//第二个字节都校验和的有效数据
		if((Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_count-3]+\
			Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_count-4]*256 == crc)){	 
			for(i = 0;i < Usart1_Control_Data.rx_count;i++){
					MCU_Host_Rec.rec_buf[i] = Usart1_Control_Data.rxbuf[i];
			}//把数据复制给主机通讯结构体,数据正确，先回应主机，记录刷写OLED状态位
			slave_rec_state = 1;	//从机接收数据正确
			Execute_Host_Comm();  //执行完动作再回复PC，这样比较慢，但是可以给PC正确状态的答复
		}
		Usart1_Control_Data.rx_aframe = 0;	//清空和主机的通讯，避免通讯错误
		Usart1_Control_Data.rx_count = 0;	
}

//=============================================================================
//函数名称:Execute_Host_Comm
//功能概要:执行上位机发出的命令
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
u8  Execute_Host_Comm(void)
{
  u8 res;
	if(slave_rec_state == 1){//执行主机发送的命令
		if((MCU_Host_Rec.control.smg1H ==0x30)&&(MCU_Host_Rec.control.smg1L ==0x30)&&(MCU_Host_Rec.control.smg2H ==0x30)&&(MCU_Host_Rec.control.smg2L ==0x30)\
			 &&(MCU_Host_Rec.control.smg3H ==0x30)&&(MCU_Host_Rec.control.smg3L ==0x30)&&(MCU_Host_Rec.control.smg4H ==0x30)&&(MCU_Host_Rec.control.smg4L ==0x30)\
			 &&(MCU_Host_Rec.control.smg5H ==0x30)&&(MCU_Host_Rec.control.smg5L ==0x30)&&(MCU_Host_Rec.control.smg6H ==0x30)&&(MCU_Host_Rec.control.smg6L ==0x30)\
		 ){		//灯灭
				RLED_OFF;
			}else{//灯亮
				RLED_ON;
			}
		slave_rec_state =0;
	}
	return res;
}

void Communication_Process(void )
{
		if (1 == Usart1_Control_Data.rx_aframe){ 
			Respond_Host_Comm();
			Usart1_Control_Data.rx_count = 0;
			Usart1_Control_Data.rx_aframe = 0;
		}
}












