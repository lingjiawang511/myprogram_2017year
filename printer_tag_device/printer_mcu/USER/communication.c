#include"HeadType.h"

MCU_State_Type MCU_State;
Answer_Type 	 PC_Answer;
COMM_Rec_Union_Type  MCU_Host_Rec;
COMM_Send_Union_Type  MCU_Host_Send;
////=============================================================================
////函数名称: Comm_GPIO_Config
////功能概要:硬件通信引脚配置
////参数名称:无
////函数返回:无
////注意    :无
////=============================================================================
// void Communication_GPIO_Config(void)
//{	
//	//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
//	GPIO_InitTypeDef  GPIO_InitStructure;
//	//COMMUNICATION_IO1  IO配置,设备状态输出
//	RCC_APB2PeriphClockCmd(COMMUNICATION_IO1_RCC,ENABLE);		
//	GPIO_InitStructure.GPIO_Pin = COMMUNICATION_IO1_IO;	 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//	GPIO_Init(COMMUNICATION_IO1_PORT, &GPIO_InitStructure);
//	//COMMUNICATION_IO2  IO配置
//	RCC_APB2PeriphClockCmd(COMMUNICATION_IO2_RCC,ENABLE);		
//	GPIO_InitStructure.GPIO_Pin = COMMUNICATION_IO2_IO;	 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//	GPIO_Init(COMMUNICATION_IO2_PORT, &GPIO_InitStructure);
//	//COMMUNICATION_IO3  IO配置
//	RCC_APB2PeriphClockCmd(COMMUNICATION_IO3_RCC,ENABLE);		
//	GPIO_InitStructure.GPIO_Pin = COMMUNICATION_IO3_IO;	 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//	GPIO_Init(COMMUNICATION_IO3_PORT, &GPIO_InitStructure);

//}



//=============================================================================
//函数名称:SLAVE_Rec_Comm
//功能概要:PC作为通讯主机时接收的控制字处理并响应
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
static u8  SLAVE_Rec_Comm(void)
{
	u8 i,res;
	u16 crc;
	if(Usart1_Control_Data.rx_count < 18){
		res = 2;
		return res;
	}crc=CRC_GetCCITT(Usart1_Control_Data.rxbuf,Usart1_Control_Data.rx_count-4);//帧结束尾不做校验
	if((Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_count-3]+\
 	    Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_count-4]*256 == crc)){	    
		for(i = 0;i < 18;i++){
            MCU_Host_Rec.rec_buf[i] = Usart1_Control_Data.rxbuf[i];
        }//把数据复制给主机通讯结构体
		switch(MCU_Host_Rec.control.scanner_result){
		case 0x00: 
							break;
		case 0x01:Baffle_Control.scanner_result_old=Baffle_Control.PC_send_scanner_result = MCU_Host_Rec.control.scanner_result;
							break;
		case 0x02:Baffle_Control.scanner_result_old=Baffle_Control.PC_send_scanner_result = MCU_Host_Rec.control.scanner_result;
							break;
		default :
							break;
		}
		switch(MCU_Host_Rec.control.device_control){
		case 0x00:
							break;
		case 0x01: 			if(Device_State == 3){
											Device_State = 3;
										}else{
											if(READ_UPPER_REACH==0){
												Device_State = 1; 
											}else{
												Device_State = 3;
											}
										}
							break;
		case 0x02:
							Device_State = 2;
							break;
		default :
							break;
		}
		if(Device_State == 2){//设备停止状态下才可以手动翻板
				switch(MCU_Host_Rec.control.baffle_control){
				case 0x00:	 
									break;
				case 0x01:BAFFLE_INTER;		
									break;
				case 0x02:BAFFLE_OUTER;
									break;
				default :	
									break;
				}
		}
		switch(MCU_Host_Rec.control.printer_fix){
		case 0x00:	 
							break;
		case 0x01:Air_Control.PC_send_delay_time = (MCU_Host_Rec.control.printer_delay_H*256+MCU_Host_Rec.control.printer_delay_L+2)/5;//上位机发的时间是1ms，单片机捕捉的时间是5MS，下一个周期生效
							break;
		case 0x02:break;
		default : break;
		}
		switch(MCU_Host_Rec.control.baffle_fix){
		case 0x00:	 
							break;
		case 0x01:Baffle_Control.PC_send_process_time = (MCU_Host_Rec.control.baffle_delay_H*256+MCU_Host_Rec.control.baffle_delay_L+2)/5;
							break;
		default : break;
		}
		switch(MCU_Host_Rec.control.check_state){
		case 0x00:	
							break;
		case 0x01: 
		           MCU_Host_Send.control.crc_result = 1;
							 MCU_Host_Send.control.scanner_result = Baffle_Control.scanner_result_old;
							 MCU_Host_Send.control.device_state = Device_State;
							 if(Printer.input_state == 1){
									MCU_Host_Send.control.printer_state = 1;
							 }else{
                  MCU_Host_Send.control.printer_state = 2;
							}
							if((Baffle_Control.bag_input_flag == 1)||(Control.scanner.state == 1)){
								if(Baffle_Control.PC_send_scanner_result==1){
									MCU_Host_Send.control.recom_state = 1;
								}else{
									MCU_Host_Send.control.recom_state = 2;
								}
							}else{
								if(Baffle_Control.PC_send_scanner_result >=1){
									MCU_Host_Send.control.recom_state = 3;
								}else{
									MCU_Host_Send.control.recom_state = 0;
								}
							}
							break;
		case 0x02:
							break;
		default : 
							break;
		}		
			res = 0;	
	}else{
		 res = 1;
	}
	Usart1_Control_Data.tx_count = 0;
	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x01;
	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x58;
	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x06;
	if(res == 0)//接收的数据正确
	{
		 if(MCU_Host_Rec.control.check_state == 1){
				Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x01;
				Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = Baffle_Control.scanner_result_old;
				Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = MCU_Host_Send.control.device_state;
				Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = MCU_Host_Send.control.printer_state;
				Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = MCU_Host_Send.control.recom_state;
				Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = MCU_Host_Send.control.err_message;
		 }else{
				Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x01;
				Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = MCU_Host_Rec.control.scanner_result;
				Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
				Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
				Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
				Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
		}
			crc=CRC_GetCCITT(Usart1_Control_Data.txbuf,Usart1_Control_Data.tx_count);
			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = (crc>>8)&0xFF; ;
			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = crc&0xFF;	
	}else if(res == 1){//CRC校验错误
			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x02;
			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
		  Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
		  Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
		  Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
		  Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
			crc=CRC_GetCCITT(Usart1_Control_Data.txbuf,Usart1_Control_Data.tx_count);
			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = (crc>>8)&0xFF; ;
			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = crc&0xFF;
	}
	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x0D;
	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x0A;
	return res;
}
//=============================================================================
//函数名称:SLAVE_Rec_Comm
//功能概要:PC作为通讯从机时接收的数据，并处理
//参数说明:无
//函数返回:无
//注意    :连续发送三次或者等待接收超时，将不再发送，并且状态机重新转化为从机模式
//=============================================================================
//static u8  Host_Rec_Comm(void)
//{
//  	u8 i,res;
//	u16 crc;
//	if(Usart1_Control_Data.rx_count != 10){
//		res = 2;
//		return res;
//	}crc=CRC_GetCCITT(Usart1_Control_Data.rxbuf,Usart1_Control_Data.rx_count-4);
//	if((Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_count-3]+\
// 	    Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_count-4]*256 == crc)){	    
//		for(i = 0;i < 10;i++){
//            MCU_Host_Rec.rec_buf[i] = Usart1_Control_Data.rxbuf[i];
//        }//把数据复制给主机通讯结构体
//		if(MCU_Host_Rec.control.comm_state == 1){//PC机应答正确接收了数据
//				res = 0;	
//		}else{
//				res = 3;
//		}
//	}else{
//		 res = 1;
//	}
//	return res;



//}
//=============================================================================
//函数名称:Execute_Host_Comm
//功能概要:执行上位机发出的命令
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
static u8 Execute_Host_Comm(void)
{
	u8 res;
	switch(MCU_State){
	case SLAVE: res = SLAVE_Rec_Comm();
							if(0 == res){
								Usart1_Control_Data.tx_index = 0;
								USART_SendData(USART1,Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_index++]);
//								MCU_State = HOST;		//正确接收到PC机发送的控制信息，响应后状态机变为主机模式
							}else if(1 == res){
								Usart1_Control_Data.tx_index = 0;
								USART_SendData(USART1,Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_index++]);
							}
							break;
	case HOST :
//							res = Host_Rec_Comm();
//							if(( res== 1)||(res == 3)){//主机没有正确接收到数据，重新发送数据
//								Usart1_Control_Data.tx_index = 0;
//								Usart1_Control_Data.tx_count = 16;	
//								PC_Answer.Nanswer_timeout = NANSWER_TIME;
//								if(PC_Answer.answer_numout==0){
//									MCU_State = SLAVE;
//									PC_Answer.Nanswer_timeout = NANSWER_TIME;
//									PC_Answer.answer_numout = NANSWER_NUMOUT;
//									PC_Answer.answer_state = 0;
//								}else{
//									PC_Answer.answer_numout--;
//								}
//								USART_SendData(USART1,Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_index++]);//原来的数据没改变，所以直接发送
//							}else if(res == 0){
//								PC_Answer.answer_state = 0;	
//								MCU_State = SLAVE;		//正确接收到PC机发送的接收状态信息，转化为从机等待下一次PC发送控制信息
//								PC_Answer.Nanswer_timeout = NANSWER_TIME;
//								PC_Answer.answer_numout = NANSWER_NUMOUT;
//							}
						break;
	default :MCU_State = SLAVE;		
					 break ;
	}
	return res;
}

//=============================================================================
//函数名称:Respond_Host_Comm
//功能概要:响应上位机的发出的数据命令，数据已经从串口一接收完整
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
void Respond_Host_Comm(void)
{
    if (1 == Usart1_Control_Data.rx_aframe){    
				Execute_Host_Comm();		
				Usart1_Control_Data.rx_count = 0;
				Auto_Frame_Time1 = AUTO_FRAME_TIMEOUT1;
				Usart1_Control_Data.rx_aframe = 0;
    }else{
        return;
    }
}

















