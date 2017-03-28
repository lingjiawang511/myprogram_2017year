#include"HeadType.h"

/*串口1管脚重映射*/
#define USART1REMAP 0


Usart_Type Usart1_Control_Data;
Usart_Type Usart2_Control_Data;
Usart_Type Usart3_Control_Data;
char Auto_Frame_Time1;
char Auto_Frame_Time2;
char Auto_Frame_Time3;



//=============================================================================
//函数名称:Init_USART1
//功能概要:USART1 初始化串口相关参数
//参数说明:无
//函数返回:无
//=============================================================================
static void Init_USART1(void)
{
    Usart1_Control_Data.tx_index = 0;
    Usart1_Control_Data.rx_index = 0;
    Usart1_Control_Data.tx_count = 0;
    Usart1_Control_Data.rx_count = 0;
    Usart1_Control_Data.rx_start = 0;
    Usart1_Control_Data.rx_aframe = 0;
    
}
//=============================================================================
//函数名称:Init_USART2
//功能概要:USART2 初始化串口相关参数
//参数说明:无
//函数返回:无
//=============================================================================
static void Init_USART2(void)
{
    Usart2_Control_Data.tx_index = 0;
    Usart2_Control_Data.rx_index = 0;
    Usart2_Control_Data.tx_count = 0;
    Usart2_Control_Data.rx_count = 0;
    Usart2_Control_Data.rx_start = 0;
    Usart2_Control_Data.rx_aframe = 0;
    
}
//=============================================================================
//函数名称:Init_USART3
//功能概要:USART3 初始化串口相关参数
//参数说明:无
//函数返回:无
//=============================================================================
static void Init_USART3(void)
{
    Usart3_Control_Data.tx_index = 0;
    Usart3_Control_Data.rx_index = 0;
    Usart3_Control_Data.tx_count = 0;
    Usart3_Control_Data.rx_count = 0;
    Usart3_Control_Data.rx_start = 0;
    Usart3_Control_Data.rx_aframe = 0;
    
}
//=============================================================================
//函数名称:USART1_Interrupts_Config
//功能概要:USART1 中断优先级配置
//参数说明:无
//函数返回:无
//=============================================================================
static void USART1_Interrupts_Config(void)
{
     NVIC_InitTypeDef NVIC_InitStructure; 
    
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    
     NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
}
//=============================================================================
//函数名称:USART2_Interrupts_Config
//功能概要:USART2 中断优先级配置
//参数说明:无
//函数返回:无
//=============================================================================
static void USART2_Interrupts_Config(void)
{
     NVIC_InitTypeDef NVIC_InitStructure; 
    
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    
     NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
}
//=============================================================================
//函数名称:USART3_Interrupts_Config
//功能概要:USART3 中断优先级配置
//参数说明:无
//函数返回:无
//=============================================================================
static void USART3_Interrupts_Config(void)
{
     NVIC_InitTypeDef NVIC_InitStructure; 
    
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    
     NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
}
//=============================================================================
//函数名称:USART1_Config
//功能概要:USART1 初始化配置,工作模式配置。57600 8-N-1
//参数说明:无
//函数返回:无
//=============================================================================
#if USART1REMAP  //如果USART1使用了映射

void USART1_Config(void )
{	
    GPIO_InitTypeDef GPIO_InitStructure;	
    USART_InitTypeDef USART_InitStructure;  //定义串口初始化结构体
    
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB | RCC_APB2Periph_USART1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);

  /*  USART1_TX -> PB6 */
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	       //选中串口默认输出管脚         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //定义输出最大速率 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//定义管脚9的模式  
  GPIO_Init(GPIOB, &GPIO_InitStructure);           //调用函数，把结构体参数输入进行初始化	
  
  /*  USART1_RX ->	PB7*/

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  USART_InitStructure.USART_BaudRate = 19200; //波特率
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位
  USART_InitStructure.USART_StopBits = USART_StopBits_1;	//停止位1位
  USART_InitStructure.USART_Parity = USART_Parity_No;		//校验位 无
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无流控制
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		//使能接收和发送引脚

  USART_Init(USART1, &USART_InitStructure); //将以上赋完值的结构体带入库函数USART_Init进行初始化
  USART_ClearFlag(USART1,USART_FLAG_TC);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART1, USART_IT_TC, ENABLE);
    /* Enable the EXTI Interrupt */
  USART_Cmd(USART1, ENABLE);//开启USART1，注意与上面RCC_APB2PeriphClockCmd()设置的区别
  USART1_Interrupts_Config();
  Init_USART1();
}
#else
void USART1_Config(void)
{
	//gpio，usart初始化结构体定义
	//当gpio复用时（开启外设时），需要初始化同时gpio和ppp外设，并对他们使能和开启时钟
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	//开启gpio和外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

	//gpio初始化结构体成员赋值
	//初始化PA。9，复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//执行上面的gpio初始化
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// PA.10浮空输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//USART初始化
	USART_InitStructure.USART_BaudRate = 19200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_ClearFlag(USART1,USART_FLAG_TC);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART1, USART_IT_TC, ENABLE);
	/* Enable the EXTI Interrupt */
	USART_Cmd(USART1, ENABLE);//开启USART1，注意与上面RCC_APB2PeriphClockCmd()设置的区别
	
	USART1_Interrupts_Config();
	Init_USART1();
}

#endif
 //=============================================================================
//函数名称:USART2_Config
//功能概要:USART2 初始化配置,工作模式配置。57600 8-N-1
//参数说明:无
//函数返回:无
//=============================================================================
void USART2_Config(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* Enable the USART2 Pins Software Remapping */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 

	/* Configure USART2 Tx (PA.02) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Configure USART2 Rx (PA.03) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    

	USART_InitStructure.USART_BaudRate = 19200; 			 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	   
	USART_InitStructure.USART_Parity = USART_Parity_No; 	  
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  

	USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART2, USART_IT_TC, ENABLE);
	USART_ClearFlag(USART2,USART_FLAG_TC);
	/* Enable USART2 */
	USART_Cmd(USART2, ENABLE);
	USART2_Interrupts_Config();
	Init_USART2();

}
//=============================================================================
//函数名称:USART1_Config
//功能概要:USART1 初始化配置,工作模式配置。57600 8-N-1
//参数说明:无
//函数返回:无
//=============================================================================


void USART3_Config(void )
{	
  
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* Enable the USART3 Pins Software Remapping */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 

	/* Configure USART3 Tx (PB .10) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	/* Configure USART3 Rx (PB.11) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
      
	USART_InitStructure.USART_BaudRate = 19200; 			 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	   
	USART_InitStructure.USART_Parity = USART_Parity_No; 	  
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  

	USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART3, USART_IT_TC, ENABLE);
	USART_ClearFlag(USART3,USART_FLAG_TC);
	/* Enable USART2 */
	USART_Cmd(USART3, ENABLE);
	USART3_Interrupts_Config();
	Init_USART3();
}
//=============================================================================
//函数名称:fputc
//功能概要:重定向c库函数printf到USART
//参数说明:无
//函数返回:无
//注意   :由printf调用,需要勾选Use Microlib
//=============================================================================

int fputc(int ch, FILE *f)
{
//将Printf内容发往串口 
  USART_SendData(USART1, (unsigned char) ch);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
  return (ch);
}
//=============================================================================
//函数名称:USART1_Putc
//功能概要:将USART1_Putc（）内容打印到串口
//参数说明:无
//函数返回:无
//注意   :无
//=============================================================================
void USART1_Putc(unsigned char c)
{
    USART_SendData(USART1, c);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
}

//=============================================================================
//函数名称:USART1_Putc
//功能概要:将USART1_Putc（）内容打印到串口
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
void USART1_Puts(char * str)
{
    while(*str)
    {
        USART_SendData(USART1, *str++);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
}
//=============================================================================
//函数名称:USART2_Putc
//功能概要:将USART2_Putc（）内容打印到串口
//参数说明:无
//函数返回:无
//注意   :无
//=============================================================================
void USART2_Putc(unsigned char c)
{
    USART_SendData(USART2, c);
    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET );
}

//=============================================================================
//函数名称:USART2_Putc
//功能概要:将USART2_Putc（）内容打印到串口
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
void USART2_Puts(char * str)
{
    while(*str){
        USART_SendData(USART2, *str++);
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
    }
}
//=============================================================================
//函数名称:USART3_Putc
//功能概要:将USART3_Putc（）内容打印到串口
//参数说明:无
//函数返回:无
//注意   :无
//=============================================================================
void USART3_Putc(unsigned char c)
{
    USART_SendData(USART3, c);
    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET );
}

//=============================================================================
//函数名称:USART3_Putc
//功能概要:将USART3_Putc（）内容打印到串口
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
void USART3_Puts(char * str)
{
    while(*str){
        USART_SendData(USART3, *str++);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
    }
}
//=============================================================================
//函数名称:USART1_Do_Tx
//功能概要:将串口一的数据发送出去，通过中断发送
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
void USART1_Do_Tx(void )
{
    if (Usart1_Control_Data.tx_index < Usart1_Control_Data.tx_count) {
		USART_SendData(USART1, Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_index]);
		Usart1_Control_Data.tx_index++;
	}else{
       Usart1_Control_Data.tx_count = 0; 
       Usart1_Control_Data.tx_index = 0;
    }
}
//=============================================================================
//函数名称:USART2_Do_Tx
//功能概要:将串口二的数据发送出去，通过中断发送
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
void USART2_Do_Tx(void )
{
    if (Usart2_Control_Data.tx_index < Usart2_Control_Data.tx_count) {
		USART_SendData(USART2, Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_index]);
		Usart2_Control_Data.tx_index++;
	}else{
       Usart2_Control_Data.tx_count = 0; 
       Usart2_Control_Data.tx_index = 0;	   
    }
}
//=============================================================================
//函数名称:USART3_Do_Tx
//功能概要:将串口二的数据发送出去，通过中断发送
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
void USART3_Do_Tx(void )
{
    if (Usart3_Control_Data.tx_index < Usart3_Control_Data.tx_count) {
		USART_SendData(USART3, Usart3_Control_Data.txbuf[Usart3_Control_Data.tx_index]);
		Usart3_Control_Data.tx_index++;
	}else{
       Usart3_Control_Data.tx_count = 0; 
       Usart3_Control_Data.tx_index = 0;	   
    }
}
//=============================================================================
//函数名称:USART1_Do_Rx
//功能概要:处理串口一接收的数据
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
void USART1_Do_Rx(u8 rxdata)
{       
		static u8 old_frame_end1,old_frame_end2;
    if (0 == Usart1_Control_Data.rx_aframe){
       if (0 == Usart1_Control_Data.rx_index){  //接收第一帧的第一个数据开启定时器3做时间自动成帧处理
           Usart1_Control_Data.rx_start = 1;
           Auto_Frame_Time1 = AUTO_FRAME_TIMEOUT1; 
       }else {
            if (Auto_Frame_Time1 <=0){   //时间超时自动成帧
               Usart1_Control_Data.rx_aframe = 1; 
               Usart1_Control_Data.rx_start = 0;
               Usart1_Control_Data.rx_count = Usart1_Control_Data.rx_index;
               Usart1_Control_Data.rx_index = 0;   //得到一帧数据后及时把索引清零
               return ;   //直接返回不接受数据              
            }                    
        }
				Auto_Frame_Time1 = AUTO_FRAME_TIMEOUT1;
       	Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_index] = rxdata;
				Usart1_Control_Data.rx_index++;	
				if(Usart1_Control_Data.rx_index >= 2){		//接受数据帧尾成帧
					old_frame_end1 = Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_index - 2];
					old_frame_end2 = Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_index - 1];
					if((old_frame_end1 == 0x0D)&&(old_frame_end2 == 0X0A)){
							Usart1_Control_Data.rx_aframe = 1;  //接收数据长度自动成帧
							Usart1_Control_Data.rx_count = Usart1_Control_Data.rx_index;
						  Usart1_Control_Data.rx_index = 0;   //得到一帧数据后及时把索引清零
							Usart1_Control_Data.rx_start = 0;
							Auto_Frame_Time1 = AUTO_FRAME_TIMEOUT1; 
					}
				}
        if (Usart1_Control_Data.rx_index > (RxBufMax - 1)){
            Usart1_Control_Data.rx_index = (RxBufMax - 1);
            Usart1_Control_Data.rx_aframe = 1;  //接收数据长度自动成帧
            Usart1_Control_Data.rx_count = Usart1_Control_Data.rx_index+1;
            Usart1_Control_Data.rx_index = 0;   //得到一帧数据后及时把索引清零
            Usart1_Control_Data.rx_start = 0;
            Auto_Frame_Time1 = AUTO_FRAME_TIMEOUT1; 
        }   
    }else{  //接收到一帧数据后必须处理完才可以继续接受下一帧数据
       Usart1_Control_Data.rx_start = 0;
       Auto_Frame_Time1 = AUTO_FRAME_TIMEOUT1; 
        return;
    }           
}
//=============================================================================
//函数名称:USART2_Do_Rx
//功能概要:处理串口二接收的数据
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
void USART2_Do_Rx(u8 rxdata)
{       
    if (0 == Usart2_Control_Data.rx_aframe){
       if (0 == Usart2_Control_Data.rx_index){  //接收第一帧的第一个数据开启定时器3做时间自动成帧处理
           Usart2_Control_Data.rx_start = 1;
           Auto_Frame_Time2 = AUTO_FRAME_TIMEOUT2; 
       }else {
            if (Auto_Frame_Time2 <=0){   //时间超时自动成帧
               Usart2_Control_Data.rx_aframe = 1; 
               Usart2_Control_Data.rx_start = 0;
               Usart2_Control_Data.rx_count = Usart2_Control_Data.rx_index;
               Usart2_Control_Data.rx_index = 0;   //得到一帧数据后及时把索引清零
               return ;   //直接返回不接受数据              
            }                    
        }
				Auto_Frame_Time2 = AUTO_FRAME_TIMEOUT2;
       	Usart2_Control_Data.rxbuf[Usart2_Control_Data.rx_index] = rxdata;
        Usart2_Control_Data.rx_index++;
        if (Usart2_Control_Data.rx_index > (RxBufMax - 1)){
            Usart2_Control_Data.rx_index = (RxBufMax - 1);
            Usart2_Control_Data.rx_aframe = 1;  //接收数据长度自动成帧
            Usart2_Control_Data.rx_count = Usart2_Control_Data.rx_index+1;
            Usart2_Control_Data.rx_index = 0;   //得到一帧数据后及时把索引清零
            Usart2_Control_Data.rx_start = 0;
            Auto_Frame_Time2 = AUTO_FRAME_TIMEOUT2; 
        }   
    }else{  //接收到一帧数据后必须处理完才可以继续接受下一帧数据
       Usart2_Control_Data.rx_start = 0;
       Auto_Frame_Time2 = AUTO_FRAME_TIMEOUT2; 
        return;
    }           
}
//=============================================================================
//函数名称:USART3_Do_Rx
//功能概要:处理串口二接收的数据
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
void USART3_Do_Rx(u8 rxdata)
{       
    if (0 == Usart3_Control_Data.rx_aframe){
       if (0 == Usart3_Control_Data.rx_index){  //接收第一帧的第一个数据开启定时器3做时间自动成帧处理
           Usart3_Control_Data.rx_start = 1;
           Auto_Frame_Time3 = AUTO_FRAME_TIMEOUT3; 
       }else {
            if (Auto_Frame_Time3 <=0){   //时间超时自动成帧
               Usart3_Control_Data.rx_aframe = 1; 
               Usart3_Control_Data.rx_start = 0;
               Usart3_Control_Data.rx_count = Usart3_Control_Data.rx_index;
               Usart3_Control_Data.rx_index = 0;   //得到一帧数据后及时把索引清零
               return ;   //直接返回不接受数据              
            }                    
        }
				Auto_Frame_Time3 = AUTO_FRAME_TIMEOUT3;
       	Usart3_Control_Data.rxbuf[Usart3_Control_Data.rx_index] = rxdata;
        Usart3_Control_Data.rx_index++;
        if (Usart3_Control_Data.rx_index > (RxBufMax - 1)){
            Usart3_Control_Data.rx_index = (RxBufMax - 1);
            Usart3_Control_Data.rx_aframe = 1;  //接收数据长度自动成帧
            Usart3_Control_Data.rx_count = Usart3_Control_Data.rx_index+1;
            Usart3_Control_Data.rx_index = 0;   //得到一帧数据后及时把索引清零
            Usart3_Control_Data.rx_start = 0;
            Auto_Frame_Time3 = AUTO_FRAME_TIMEOUT3; 
        }   
    }else{  //接收到一帧数据后必须处理完才可以继续接受下一帧数据
       Usart3_Control_Data.rx_start = 0;
       Auto_Frame_Time3 = AUTO_FRAME_TIMEOUT3; 
        return;
    }           
}


////=============================================================================
////函数名称:SLAVE_Rec_Comm
////功能概要:PC作为通讯主机时接收的控制字处理并响应
////参数说明:无
////函数返回:无
////注意    :无
////=============================================================================
//static u8  SLAVE_Rec_Comm(void)
//{
//	u8 i,res;
//	u16 crc;
//	if(Usart1_Control_Data.rx_count < 18){
//		res = 2;
//		return res;
//	}crc=CRC_GetCCITT(Usart1_Control_Data.rxbuf,Usart1_Control_Data.rx_count-4);//帧结束尾不做校验
//	if((Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_count-3]+\
// 	    Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_count-4]*256 == crc)){	    
//		for(i = 0;i < 18;i++){
//            PC_Host_Rec.send_buf[i] = Usart1_Control_Data.rxbuf[i];
//        }//把数据复制给主机通讯结构体
//		switch(PC_Host_Rec.control.ch1_state){
//		case 0x00:
//							Channel.ch1.send_num = 0;
//							Channel.ch1.state = READY;	 
//							break;
//		case 0x01:Channel.ch1.send_num = PC_Host_Rec.control.ch1_num;	
//							Channel.ch1.send_actual = 0;
//							Channel.ch1.state = READY ;
//							PC_Host_Rec.control.ch1_state = 0;
//							break;
//		default : Channel.ch1.send_num = 0;
//							Channel.ch1.state = READY;
//							break;
//		}
//		switch(PC_Host_Rec.control.ch2_state){
//		case 0x00:	
//							Channel.ch2.send_num = 0;
//							Channel.ch2.state = READY;
//							break;
//		case 0x01:Channel.ch2.send_num = PC_Host_Rec.control.ch2_num;	
//							Channel.ch2.send_actual = 0;
//							Channel.ch2.state = READY ;
//							PC_Host_Rec.control.ch2_state = 0;
//							break;
//		default : Channel.ch2.send_num = 0;
//							Channel.ch2.state = READY;
//							break;
//		}
//		switch(PC_Host_Rec.control.ch3_state){
//		case 0x00:
//							Channel.ch3.send_num = 0;
//							Channel.ch3.state = READY;
//							break;
//		case 0x01:Channel.ch3.send_num = PC_Host_Rec.control.ch3_num;	
//							Channel.ch3.send_actual = 0;
//							Channel.ch3.state = READY ;
//							PC_Host_Rec.control.ch3_state = 0;
//							break;
//		default :
//							Channel.ch3.send_num = 0;
//							Channel.ch3.state = READY;
//							break;
//		}
//		switch(PC_Host_Rec.control.ch4_state){
//		case 0x00:	 
//							Channel.ch4.send_num = 0;
//							Channel.ch4.state = READY;
//							break;
//		case 0x01:Channel.ch4.send_num = PC_Host_Rec.control.ch4_num;	
//							Channel.ch4.send_actual = 0;
//							Channel.ch4.state = READY ;
//							PC_Host_Rec.control.ch4_state = 0;
//							break;
//		default :	Channel.ch4.send_num = 0;
//							Channel.ch4.state = READY;
//							break;
//		}
//		switch(PC_Host_Rec.control.belt_state){
//		case 0x00:	 
//							break;
//		case 0x01:belt.send_time = PC_Host_Rec.control.belt_time;	
//							belt.actual_time = belt.send_time *400; //*2s
//							belt.state = READY ;
//							PC_Host_Rec.control.belt_state = 0;
//							break;
//		default : break;
//		}		
//			res = 0;	
//	}else{
//		 res = 1;
//	}
//	Usart1_Control_Data.tx_count = 0;
//	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x01;
//	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x58;
//	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
//	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x02;
//	if(res == 0)//接收的数据正确
//	{
//			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x01;
//			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
//			crc=CRC_GetCCITT(Usart1_Control_Data.txbuf,Usart1_Control_Data.tx_count);
//			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = (crc>>8)&0xFF; ;
//			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = crc&0xFF;	
//	}else if(res == 1){//CRC校验错误
//			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
//			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x00;
//			crc=CRC_GetCCITT(Usart1_Control_Data.txbuf,Usart1_Control_Data.tx_count);
//			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = (crc>>8)&0xFF; ;
//			Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = crc&0xFF;
//	}
//	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x0D;
//	Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_count++] = 0x0A;
//	return res;
//}
////=============================================================================
////函数名称:SLAVE_Rec_Comm
////功能概要:PC作为通讯从机时接收的数据，并处理
////参数说明:无
////函数返回:无
////注意    :连续发送三次或者等待接收超时，将不再发送，并且状态机重新转化为从机模式
////=============================================================================
//static u8  Host_Rec_Comm(void)
//{
//	u8 i,res;
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
////=============================================================================
////函数名称:Execute_Host_Comm
////功能概要:执行上位机发出的命令
////参数说明:无
////函数返回:无
////注意    :无
////=============================================================================
//static u8 Execute_Host_Comm(void)
//{
//	u8 res;
//	switch(MCU_State){
//	case SLAVE: res = SLAVE_Rec_Comm();
//							if(0 == res){
//								Usart1_Control_Data.tx_index = 0;
//								USART_SendData(USART1,Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_index++]);
//								MCU_State = HOST;		//正确接收到PC机发送的控制信息，响应后状态机变为主机模式
//							}else if(1 == res){
//								Usart1_Control_Data.tx_index = 0;
//								USART_SendData(USART1,Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_index++]);
//							}
//							break;
//	case HOST :	res = Host_Rec_Comm();
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
//						break;
//	default :MCU_State = SLAVE;		
//					 break ;
//	}
//	return res;
//}

////=============================================================================
////函数名称:Respond_Host_Comm
////功能概要:响应上位机的发出的数据命令，数据已经从串口一接收完整
////参数说明:无
////函数返回:无
////注意    :无
////=============================================================================
//void Respond_Host_Comm(void)
//{
//    if (1 == Usart1_Control_Data.rx_aframe){    
//				Execute_Host_Comm();		
//				Usart1_Control_Data.rx_count = 0;
//				Auto_Frame_Time1 = AUTO_FRAME_TIMEOUT1;
//				Usart1_Control_Data.rx_aframe = 0;
//    }else{
//        return;
//    }
//}



