#ifndef __HEADTYPE_H_
#define __HEADTYPE_H_

#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>	
#include "led.h"
#include "delay.h"
#include "send_medicine_control.h"
#include "exti.h"
#include "usart.h"
#include "TIM.h"
#include "belt.h"
#include "printer.h"
#include "air_cylinder.h"
#include "communication.h"
#include "baffle.h"

/*************Typedef datatype start*******************/
typedef char int8;
typedef volatile char vint8;
typedef unsigned char uint8;
typedef volatile unsigned char vuint8;
typedef int int16;
typedef unsigned short uint16;
typedef long int32;
typedef unsigned long uint32;
typedef uint8	uchar,u8,BYTE;		/**< 8-bit value */
typedef uint8 	SOCKET;
typedef uint16	ushort,u16,WORD;	/**< 16-bit value */
typedef uint16	uint;		/**< 16-bit value */
typedef uint32	ulong;		/**< 32-bit value */
/*************Typedef datatype end*******************/

/*************define type start*******************/
#define false      (0)
#define true       (!false)

#ifndef NULL
#define NULL  ((void *)(0))
#endif


#define RxBufMax 512
#define TxBufMax 512
/*自动成帧超时定时时间*/
#define AUTO_FRAME_TIMEOUT1  10  //10*2ms
#define AUTO_FRAME_TIMEOUT2  10  //10*2ms
#define AUTO_FRAME_TIMEOUT3  10  //10*2ms
/*自动成帧超时定时时间*/
//响应超时时间，即上位机确认二维码正确后扫描枪一直扫描直到得到下一次数据的最长时间
#define ANSWER_SCANTIME	 	 4000	  //4000*5ms
//无响应超时时间，即当下位机发送数据给上位机，而上位机没有响应的最长时间
#define NANSWER_TIME	 1000	  //1000*5ms
#define NANSWER_NUMOUT	 	 3	  //1000*5ms

#define IRQ_TIMEOUT							4			//中断软件延时时间


/*************define type end*******************/

/*************union type start*******************/
typedef union{
	long l;
	unsigned long ul;
	int  i;
	unsigned int ui;
	short si[2];
	char  c[4];
	unsigned char uc[4];	
}UL;

typedef union{
	short i;
	unsigned short ui;
	char c[2];
	unsigned char uc[2];
}UI;

/*************union type end*******************/

/*************enum type start*******************/
enum
{
	False=0,True
};
enum{
	READLOW,READHIGH
};
typedef enum{
	SLAVE,
	HOST
}MCU_State_Type;
typedef enum{
	IN_DOWN,
	IN_UP
}Air_Position_Type;

typedef enum{
	PRINTER_RESERVE,
	PRINTER_READY,
//	PRINTER_START,
	PRINTER_WORKING,
	PRINTER_END
}Pulse_Type;
//typedef enum{
//	RESERVE,
//	READY,
//	WORKING,
//	WORKEND,
//	END
//}CH_Work_Enum_Type;
typedef enum{
	RESERVE,
	READY,
	WORKING,
	WORKEND,
	END
}Printer_Work_Enum_Type;
typedef Printer_Work_Enum_Type CH_Work_Enum_Type;
typedef Printer_Work_Enum_Type Air_Cylinder_Enum_Type;
/*************enum type end*******************/

/*************struct type start*******************/

typedef struct{
    u16 tx_index;        //发送当前数据的索引
    u16 rx_index;        //接收到当前数据的索引
    u16 tx_count;        //发送数据总数
    u16 rx_count;        //接收数据总数
    u8 rx_start;
    u8 rx_aframe;       //已经接收到一帧数据
    u8 txbuf[RxBufMax]; //发送数据缓存区
    u8 rxbuf[RxBufMax]; //接收数据缓存区
}Usart_Type;
//主机发送数据协议字节
typedef struct{
	u8  frame_soh;
	u8  frame_x;
	u16 datasize;
	u8  crc_result;       //接收数据CRC结果
	u8  scanner_result;   //二维码扫描结果
  u8  device_state;    //设备状态
	u8  printer_state;   //打印状态
	u8  recom_state;    //复合状态
	u8  err_message;
	u16 crc16_ccitt; 
	u8  frame_end1;
	u8  frame_end2;
}Communation_Send_Type;
//主机接收响应协议字节
typedef struct{
	u8  frame_soh;
	u8  frame_x;
	u16 datasize;
	u8  scanner_result;
	u8  check_state;
	u8  device_control;  //设备控制，控制设备启动停止
	u8  baffle_control;  //挡板控制，只在设备停止状态下有效
	u8  printer_fix;
	u8 printer_delay_H;
	u8 printer_delay_L;
	u8  baffle_fix;
	u8 baffle_delay_H;
	u8 baffle_delay_L;
	u16 crc16_ccitt; 
	u8  frame_end1;
	u8  frame_end2;
}Communation_Rec_Type;

typedef union{
	Communation_Send_Type control;
	u8	send_buf[14];	
}COMM_Send_Union_Type;

typedef union{
	Communation_Rec_Type control;
	u8	rec_buf[18];	
}COMM_Rec_Union_Type;

typedef struct{
	u8  answer_state;
	u8 	answer_numout;
	u16 answer_timeout;
	u16 Nanswer_timeout;
}Answer_Type;

typedef struct{
	CH_Work_Enum_Type  state;
	u8 	send_num;			//需要发药数，由PC机发送过来
	u8  motor_pulse;	//电机转过的圈数，使用传感器
	u8  send_actual;	//实际发药数，使用传感器计数
	u8  motor_state;	//电机的工作状态，正在工作时不允许执行状态转换
	u8 	timeoutstart; //电机实际发药数超过PC需要发药数时开启超时变量
	u16  timeout;			//电机实际发药数超时时间
	u8  motor_irqstate;//电机中断软件滤波状态
	u8 motor_irqtime;//电机中断软件滤波时间
	u8 send_actual_irqstate;	//实时计数中断软件滤波状态
	u8 send_actual_irqtime;		//实时计数中断软件滤波时间
	u8 motor_start_state;			//电机启动延时状态
	u16 motor_start_time;			//电机延时启动时间
}CH_Work_Type;

typedef struct{
	CH_Work_Enum_Type  state;
	u8 	 send_time;
	u16  actual_time;
}Belt_Work_Type;
typedef struct{
	CH_Work_Type ch1;
	CH_Work_Type ch2;
	CH_Work_Type ch3;
	CH_Work_Type ch4;
}CH_Work;
typedef struct {
	u8 state;
	u8 irqstate;
	u8 irqtime;
}Printer_Input_Type;
typedef struct{
	Printer_Work_Enum_Type  state;  
	Printer_Input_Type 	err;					//打印机故障输入
	Printer_Input_Type  end;					//打印机打印结束输入
	Printer_Input_Type  pinline;			//打印机在线输入
	Printer_Input_Type  color_end;	  //打印机色带完输入
	Printer_Input_Type 	color_less;   //打印机色带少输入
	Printer_Input_Type tag_end;			  //打印机标签用完输入
	u8 input_state;   //打印机输入状态
	Pulse_Type process;         //打印机过程
	u8 start_delay_time;
	u8 restart;       //打印机重复启动
	u8 complete;
	u16 fluid_bag_timeout;  //液袋信号状态超时清零
	u8 printer_work_timeout;
}Printer_Type;
typedef struct{
	Air_Position_Type 	air_cylinder_position;		//下压气缸位置
	u8	air_cylinder_satte;		//下压气缸状态
	u8 	air_blow_satte;				//吹气气缸状态
	u8 	vacuum_satte;					//真空吸纸状态
	Air_Cylinder_Enum_Type process; //下压气缸过程
	u16 delay_time;    //下压气缸下压延时时间
	u16 PC_send_delay_time;
	u8  complete; 
  u16 air_cylinder_dowm_timeout;   //下压气缸下压后无提升超时
}Air_Controlr_Type;
typedef struct{
	Printer_Input_Type fit_reach;
	Printer_Input_Type upper_reach;
	Printer_Input_Type fluid_bag;
	Printer_Input_Type scanner;
}Control_Input_Type;
typedef struct{
	u16 Scanner_Err_Time;
	u16 bag_Err_Time;
	u16 process_time;
	u16 PC_send_process_time;
	u8  bag_input_flag;
	u8  bag_err_flag;
	u8  bag_ok_flag;
	u8  process_flag;
	u8  PC_send_scanner_result;
	u8  baffle_state;
	u8  scanner_result_old;
}Control_Baffle_Type;
/*************struct type end*******************/

/*************extern variable start*******************/
extern char Auto_Frame_Time1;

extern  Usart_Type Usart1_Control_Data;

extern  COMM_Send_Union_Type PC_Host_Rec;
extern  COMM_Rec_Union_Type  PC_Hosr_Send;

extern  COMM_Send_Union_Type MCU_Host_Send;
extern  COMM_Rec_Union_Type  MCU_Host_Rec;

extern  MCU_State_Type MCU_State;
extern  Answer_Type 	 PC_Answer;

extern  CH_Work Channel;
extern	Belt_Work_Type belt;


extern u8 Key_ScanNum;
extern u8 Device_State;
extern Printer_Type Printer;
extern Control_Input_Type Control;
extern Air_Controlr_Type Air_Control;
extern Control_Baffle_Type Baffle_Control;
/*************extern variable end*******************/

/*************function start*******************/
u16 CRC_GetModbus16(u8 *pdata, int len);
u16 CRC_GetCCITT(u8 *pdata, int len);
void Key_Light_Init(void);
void Key_Light_Dispose(void);
void ROLL_PAPER_GPIO_Config(void);
void Roll_Paper_Control(void);
void param_init(void);
/*************function end*******************/
#endif


