#include"HeadType.h"

Host_COMM_Union_Type Host_Control;
Host_Answer_Type 	 Host_Answer;

//=============================================================================
//函数名称: Comm_GPIO_Config
//功能概要:硬件通信引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
 void Communication_GPIO_Config(void)
{	
	//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	//COMMUNICATION_IO1  IO配置,设备状态输出
	RCC_APB2PeriphClockCmd(COMMUNICATION_IO1_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = COMMUNICATION_IO1_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(COMMUNICATION_IO1_PORT, &GPIO_InitStructure);
	//COMMUNICATION_IO2  IO配置
	RCC_APB2PeriphClockCmd(COMMUNICATION_IO2_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = COMMUNICATION_IO2_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(COMMUNICATION_IO2_PORT, &GPIO_InitStructure);
	//COMMUNICATION_IO3  IO配置
	RCC_APB2PeriphClockCmd(COMMUNICATION_IO3_RCC,ENABLE);		
	GPIO_InitStructure.GPIO_Pin = COMMUNICATION_IO3_IO;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(COMMUNICATION_IO3_PORT, &GPIO_InitStructure);

}
void Comm_With_Device_State(void)
{
	static u8 delaytime1 = 0;
	static u8 delaytime2 = 0;
   if(Device_State == 0){
		if(READ_COMMUNICATION_IO1 == 0){
				delaytime1++;
			if(delaytime1 >= 10){
				if(READ_COMMUNICATION_IO1 == 0){
					Device_State = 1;
				}else{
					Device_State = 0;
				}
				delaytime1 = 0;
			}
		}else{
			 Device_State = 0;
			 delaytime1 = 0;
		}
	}else{
			if(READ_COMMUNICATION_IO1 == 1){
				delaytime1++;
				if(delaytime1 >= 10){
					if(READ_COMMUNICATION_IO1 == 1){
						Device_State = 0;
					}else{
						Device_State = 1;
					}
					delaytime1 = 0;
				}
			}else{
					delaytime1 = 0;
			}
	}
//test program
	if(Control.scanner.state == 0){
		if(READ_COMMUNICATION_IO2 == 0){
				delaytime2++;
			if(delaytime2 >= 10){
				if(READ_COMMUNICATION_IO2 == 0){
					Control.scanner.state = 1;
				}else{
					Control.scanner.state = 0;
				}
				delaytime2 = 0;
			}
		}else{
			 delaytime2 = 0;
		}
	}
}
//=============================================================================
//函数名称:Execute_Host_Comm
//功能概要:执行上位机发出的命令
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
static u8 Execute_Host_Comm(void)
{
	u8 i;
	u16 crc;
	if(Usart1_Control_Data.rx_count != 16){
		return 0;
	}
	crc=CRC_GetCCITT(Usart1_Control_Data.rxbuf,Usart1_Control_Data.rx_count-2);
	if((Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_count-1]+\
 	    Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_count-2]*256 == crc)){	    
		for(i = 0;i < 16;i++){
            Host_Control.host_buf[i] = Usart1_Control_Data.rxbuf[i];
        }//把数据复制给主机通讯结构体
		switch(Host_Control.control.beep_state){
		case 0x00:	 
					 break;
		case 0x01: 	 Host_Control.control.beep_state = 0;
					 break;
		case 0x02: 	
					 break;
		default : break;
		}
		switch(Host_Control.control.gled_state){
		case 0x00: 
					break;
		case 0x01: 	

					break;
		case 0x02: 	
					break;
	    case 0x03:
					break;
		default : break;
		}
		switch(Host_Control.control.rled_state){
		case 0x00: 
					break;
		case 0x01: 	
					break;
		case 0x02: 	
					break;
	    case 0x03: 	
					break;
		default : break;
		}
		switch(Host_Control.control.scanner_state){
		case 0x00: 
					break;
		case 0x01: 	Host_Answer.answer_state = Host_Control.control.scanner_state;
					Host_Control.control.scanner_state = 0;
					break;
		case 0x02: 	Host_Answer.answer_state = Host_Control.control.scanner_state;
					Host_Control.control.scanner_state = 0;
					break;
		default : break;
		}
		return 1;	
	}else{
		 return 0;
	}
}
//=============================================================================
//函数名称:response_reader
//功能概要:响应扫描头数据包程序
//参数说明:无
//函数返回:返回1代表数据校验正确，返回0代表数据校验出错
//注意    :给扫描头的数据，使用CRC14校验并且只校验数据位，不校验数据头
//=============================================================================
#if SCAN_CR8000
static u8 response_reader(void)
{	   	
	u16 crc;
	if(Usart2_Control_Data.rx_count < 16){
		return 0;
	}
	crc=CRC_GetCCITT(Usart2_Control_Data.rxbuf,Usart2_Control_Data.rx_count-2);
	if((Usart2_Control_Data.rxbuf[Usart2_Control_Data.rx_count-1]+\
 	    Usart2_Control_Data.rxbuf[Usart2_Control_Data.rx_count-2]*256 == crc)){
		/**CRC校验OK，响应READER信号 'Y'**/
		Usart2_Control_Data.tx_count = 0;
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = 0xEE;
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = 0xEE;
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = 0xEE;
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = 0xEE;
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = 'Y' ;
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = 0x01;  //data size 
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = Usart2_Control_Data.rxbuf[8];  
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = 0x00;  //data end
		crc=CRC_GetCCITT(&Usart2_Control_Data.txbuf[4],Usart2_Control_Data.tx_count-4);
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = (crc>>8)&0x7F; //CRC14
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = crc&0x7F;
		/**启动发送**/
//			Beep_Num = 5;
//			Gled_Num = 5;
//			Rled_Num = 5;
//			Host_Answer.answer_state = 1;
//			Host_Answer.answer_timeout = ANSWER_SCANTIME;
		Host_Answer.answer_state = 1; //扫描头接收到正确数据后就把状态转换
		Host_Answer.start_timeout =2; //发送开始算上位机接收超时时间
		Host_Answer.Nanswer_timeout = NANSWER_SCANTIME;
		Host_Answer.answer_timeout = ANSWER_SCANTIME;
		Usart2_Control_Data.tx_index = 0;
		USART_SendData(USART2,Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_index++]);
		return 1;
	}else{
		 /**CRC校验NOK，响应READER信号 'R'**/
		Usart2_Control_Data.tx_count = 0;
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = 0xEE;
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = 0xEE;
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = 0xEE;
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = 0xEE;
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = 'R' ;
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = 0x00;  //data size less than 32
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = 0x05;  //the Reader will use its preferred maximum packet size
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = 0x00;  //data end
		crc=CRC_GetCCITT(&Usart2_Control_Data.txbuf[4],Usart2_Control_Data.tx_count);
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = (crc>>8)&0x7F;	//CRC14
		Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_count++] = crc&0x7F;
		/**启动发送**/
		Usart2_Control_Data.tx_index = 0;
		USART_SendData(USART2,Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_index++]);
	
		return 0;
	}	
}
#else
static u8 response_reader(void)
{	   	
	if(Usart2_Control_Data.rx_count < 3){
		return 0;
	}else{
		Host_Answer.answer_state = 1; //扫描头接收到正确数据后就把状态转换
		Host_Answer.start_timeout =2; //发送开始算上位机接收超时时间
		Host_Answer.Nanswer_timeout = NANSWER_SCANTIME;
		Host_Answer.answer_timeout = ANSWER_SCANTIME;
		return 1;
   	}
}
#endif
//=============================================================================
//函数名称:Copy_Scanner_Data
//功能概要:将扫描抢得到的数据复制到串口一
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
#if SCAN_CR8000
static void  Copy_Scanner_Data(void)
{
    u8 i;
    for(i = 0;i < Usart2_Control_Data.rx_count;i++){
        Usart1_Control_Data.txbuf[i] = Usart2_Control_Data.rxbuf[i];
    }
    Usart1_Control_Data.tx_count = Usart2_Control_Data.rx_count;

    Usart2_Control_Data.rx_count = 0;
    Auto_Frame_Time2 = AUTO_FRAME_TIMEOUT2;
    
    Usart1_Control_Data.rx_index = 0;
    Usart1_Control_Data.tx_index = 0;
    USART_SendData(USART1,Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_index++]);
//        return Usart2_Control_Data.rx_count;
}
#else

static void  Copy_Scanner_Data(void)
{
  u8 i,j;
	u16 crc;
	j=0;
	Usart1_Control_Data.txbuf[j++] = 0x01;	
	Usart1_Control_Data.txbuf[j++] = 0x58;
	Usart1_Control_Data.txbuf[j++] = 0x52;	
	Usart1_Control_Data.txbuf[j++] = 0x31;
	Usart1_Control_Data.txbuf[j++] = 0x35;	
	Usart1_Control_Data.txbuf[j++] = 0x36;
	Usart1_Control_Data.txbuf[j++] = 0x37;	
	Usart1_Control_Data.txbuf[j++] = 0x38;
	Usart1_Control_Data.txbuf[j++] = 0x01;	
	Usart1_Control_Data.txbuf[j++] = 0xFF;
	Usart1_Control_Data.txbuf[j++] = 0xFF;	
	Usart1_Control_Data.txbuf[j++] = 0xFF;
	Usart1_Control_Data.txbuf[j++] = 0xFF;
	Usart1_Control_Data.txbuf[j++] = Usart2_Control_Data.rx_count >>8;	
	Usart1_Control_Data.txbuf[j++] = Usart2_Control_Data.rx_count;
    for(i = 0;i < Usart2_Control_Data.rx_count;i++){
        Usart1_Control_Data.txbuf[i+j] = Usart2_Control_Data.rxbuf[i];
    }
  Usart1_Control_Data.tx_count = Usart2_Control_Data.rx_count + j;
	crc=CRC_GetCCITT(Usart1_Control_Data.txbuf,Usart1_Control_Data.tx_count);
	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = crc >> 8;
  Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = crc;

	Usart2_Control_Data.rx_count = 0;
  Auto_Frame_Time2 = AUTO_FRAME_TIMEOUT2;
    
  Usart1_Control_Data.rx_index = 0;
  Usart1_Control_Data.tx_index = 0;
  USART_SendData(USART1,Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_index++]);
//        return Usart2_Control_Data.rx_count;
}

#endif

//=============================================================================
//函数名称:Dispose_Data_For_Host
//功能概要:将处理后的扫描抢数据启动发送到上位机
//参数说明:无
//函数返回:无
//注意    :数据正确才上传给上位机
//=============================================================================
void Dispose_Data_For_Host(void)
{

	if (1 == Usart2_Control_Data.rx_aframe){    
   		if(response_reader()){ 
				Baffle_Control.bag_input_flag = 0;	 //扫描枪收到二维码，液带信号标志清零			
   			Copy_Scanner_Data();
		}else{
		//no use 	
		}
		Usart2_Control_Data.rx_aframe = 0;
   }
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
//    u8 i=0;
    if (1 == Usart1_Control_Data.rx_aframe){    
        if(Execute_Host_Comm()){
//	        /*测试程序，把电脑发过来的数据回发回去*/
//	        for(i = 0;i < Usart1_Control_Data.rx_count;i++){
//	            Usart1_Control_Data.txbuf[i] = Usart1_Control_Data.rxbuf[i];
//	        }
//	        Usart1_Control_Data.tx_count =Usart1_Control_Data.rx_count;
//	        Usart1_Control_Data.tx_index = 0;
//	        USART_SendData(USART1,Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_index++]);
//	        /*测试程序，把电脑发过来的数据回发回去*/
			Usart1_Control_Data.rx_count = 0;
			Auto_Frame_Time1 = AUTO_FRAME_TIMEOUT1;
			Host_Answer.start_timeout = 1;
			Host_Answer.answer_timeout = ANSWER_SCANTIME;
			Baffle_Control.bag_ok_flag = 1;
		}
	    Usart1_Control_Data.rx_aframe = 0;
    }else{
        return;
    }
}

//=============================================================================
//函数名称:scanner_scan
//功能概要:循环扫描时间定时，在定时器调用
//参数名称:无
//函数返回:无
//注意    :定时器扫描时间为5ms,所以实际扫描头扫描时间为N*5*100
//=============================================================================
void scanner_scan(void)
{	
	static u16 scan_time = DEFAULT_SCANTIME;					//默认扫描周期时间
	static u16 scan_time_old = DEFAULT_SCANTIME;

	if(Host_Answer.answer_state == 2){//第一时间先响应参数修改,上位机控制扫描头扫描时间
		if(Host_Control.control.scanner_time <0X02){
			Host_Control.control.scanner_time = 0X02;
		}
		scan_time_old =Host_Control.control.scanner_time * 100;
		scan_time =	scan_time_old;
		Host_Answer.answer_state = 1;//修改之后变为主机响应状态
		Host_Answer.answer_timeout = ANSWER_SCANTIME;
	}
	if(Host_Answer.answer_state == 1){//主机响应了，就不以固定的扫描周期扫描了，扫描到二维码，一直扫描到设置值结束
		if(Host_Answer.answer_timeout <=0){
			Host_Answer.answer_state = 0;
			Host_Answer.start_timeout = 0;
		}
		if(Host_Answer.start_timeout ==1){
		    if(Host_Answer.answer_timeout == ANSWER_SCANTIME){

			 }
		 Host_Answer.answer_timeout--;	//此处相当于产生脉冲后一直为低
		 }else if(Host_Answer.start_timeout ==2){		 	 	
				if(Host_Answer.Nanswer_timeout <=0){//上位机超时没有回应，当错误处理
					Rled_Num = 5;	//错误处理
					Host_Answer.answer_state = 0;

					Host_Control.control.gled_state = 0;
					Gled_Light_Static = 0;
					GLED_OFF;
					Host_Control.control.rled_state = 0;
					Rled_Light_Static = 0;
				}
				Host_Answer.Nanswer_timeout--;
		 }
		return;
	}
	if(scan_time >0){
		scan_time--;
	}
}


void  Update_Err_Scanner_Data(void)
{
  u8 i,j;
	u16 crc;
	j=0;
	Usart1_Control_Data.txbuf[j++] = 0x01;	
	Usart1_Control_Data.txbuf[j++] = 0x58;
	Usart1_Control_Data.txbuf[j++] = 0x52;	
	Usart1_Control_Data.txbuf[j++] = 0x31;
	Usart1_Control_Data.txbuf[j++] = 0x35;	
	Usart1_Control_Data.txbuf[j++] = 0x36;
	Usart1_Control_Data.txbuf[j++] = 0x37;	
	Usart1_Control_Data.txbuf[j++] = 0x38;
	Usart1_Control_Data.txbuf[j++] = 0x01;	
	Usart1_Control_Data.txbuf[j++] = 0xFF;
	Usart1_Control_Data.txbuf[j++] = 0xFF;	
	Usart1_Control_Data.txbuf[j++] = 0xFF;
	Usart1_Control_Data.txbuf[j++] = 0xFF;
	Usart1_Control_Data.txbuf[j++] = 0;	
	Usart1_Control_Data.txbuf[j++] = 8;
    for(i = 0;i < 8;i++){
        Usart1_Control_Data.txbuf[i+j] = 0xFF;
    }
  Usart1_Control_Data.tx_count = Usart2_Control_Data.rx_count + j;
	crc=CRC_GetCCITT(Usart1_Control_Data.txbuf,Usart1_Control_Data.tx_count);
	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = crc >> 8;
  Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = crc;

  Auto_Frame_Time2 = AUTO_FRAME_TIMEOUT2;
    
  Usart1_Control_Data.rx_index = 0;
  Usart1_Control_Data.tx_index = 0;
  USART_SendData(USART1,Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_index++]);
//        return Usart2_Control_Data.rx_count;
}


