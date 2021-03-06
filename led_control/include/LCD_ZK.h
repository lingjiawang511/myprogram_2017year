//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : LCD_ZK.H
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : 字库版 OLED SPI接口演示例程(STM32系列)
//              说明: 
//              ------------------------以下为OLED显示所用到的接�----------------------------------------
//              GND    电源地
//              VCC   接5V或3.3v电源
//              CLK   PA5（CLK）
//              MOSI   PA7（DIN）
//              DC   PB0
//              CS1   PB1
//              FSO   PA4                
//              CS2   PB10
//
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2014/3/16
//All rights reserved
//******************************************************************************/
#define _LCD_ZK_H_
#ifdef _LCD_ZK_H_



/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
#define ON  0
#define OFF 1


#define		LCD_SCLK_IO					GPIO_Pin_4					 //SCLK  时钟 D0（SCLK）
#define		LCD_SCLK_PORT				GPIOA
#define   LCD_SCLK_RCC				RCC_APB2Periph_GPIOA
#define		LCD_SDA_IO					GPIO_Pin_5					 //SDA   D1（MOSI） 数据
#define		LCD_SDA_PORT				GPIOA
#define   LCD_SDA_RCC					RCC_APB2Periph_GPIOA
#define		LCD_RST_IO					GPIO_Pin_6					//_RES  hardware reset   复位 
#define		LCD_RST_PORT				GPIOA
#define   LCD_RST_RCC					RCC_APB2Periph_GPIOA
#define		LCD_DC_IO						GPIO_Pin_7				 //A0  H/L 命令数据选通端，H：数据，L:命令
#define		LCD_DC_PORT					GPIOA
#define   LCD_DC_RCC					RCC_APB2Periph_GPIOA
#define		LCD_CS_IO						GPIO_Pin_8				 //OLED片选信号
#define		LCD_CS_PORT					GPIOA
#define   LCD_CS_RCC					RCC_APB2Periph_GPIOA

#define		ROM_CS_IO						GPIO_Pin_6				 //rom片选信号
#define		ROM_CS_PORT					GPIOB
#define   ROM_CS_RCC					RCC_APB2Periph_GPIOB
#define		ROM_OUT_IO					GPIO_Pin_7				 //
#define		ROM_OUT_PORT				GPIOB
#define   ROM_OUT_RCC					RCC_APB2Periph_GPIOB

#define   LCD_SCLK(N) 	 				{if(N==1){GPIO_SetBits(LCD_SCLK_PORT, LCD_SCLK_IO);}else{GPIO_ResetBits(LCD_SCLK_PORT, LCD_SCLK_IO);}}
#define   LCD_SDA(N) 	 				{if(N==1){GPIO_SetBits(LCD_SDA_PORT, LCD_SDA_IO);}else{GPIO_ResetBits(LCD_SDA_PORT, LCD_SDA_IO);}}
#define   LCD_RST(N) 	 				{if(N==1){GPIO_SetBits(LCD_RST_PORT, LCD_RST_IO);}else{GPIO_ResetBits(LCD_RST_PORT, LCD_RST_IO);}}
#define   LCD_DC(N) 	 				{if(N==1){GPIO_SetBits(LCD_DC_PORT, LCD_DC_IO);}else{GPIO_ResetBits(LCD_DC_PORT, LCD_DC_IO);}}

#if 0
//带参宏，可以像内联函数一样使用
#define lcd_cs1(a)	if (a)	\
					GPIO_SetBits(LCD_CS_PORT,LCD_CS_IO);\
					else		\
					GPIO_ResetBits(LCD_CS_PORT,LCD_CS_IO)

//#define lcd_rs(a)	if (a)	\
//					GPIO_SetBits(LCD_DC_PORT,LCD_DC_IO);\
//					else		\
//					GPIO_ResetBits(LCD_DC_PORT,LCD_DC_IO)
#define lcd_rs(a)  LCD_DC(a)

//#define lcd_sid(a)	if (a)	\
//					GPIO_SetBits(LCD_SDA_PORT,LCD_SDA_IO);\
//					else		\
//					GPIO_ResetBits(LCD_SDA_PORT,LCD_SDA_IO)
#define lcd_sid(a) LCD_SDA(a) 
					
//#define lcd_sclk(a)	if (a)	\
//					GPIO_SetBits(LCD_SCLK_PORT,LCD_SCLK_IO);\
//					else		\
//					GPIO_ResetBits(LCD_SCLK_PORT,LCD_SCLK_IO)
#define lcd_sclk(a) LCD_SCLK(a)		
					
#define Rom_CS(a)	if (a)	\
					GPIO_SetBits(ROM_CS_PORT,ROM_CS_IO);\
					else		\
					GPIO_ResetBits(ROM_CS_PORT,ROM_CS_IO)

#define Rom_OUT(a)	if (a)	\
					GPIO_SetBits(ROM_OUT_PORT,ROM_OUT_IO);\
					else		\
					GPIO_ResetBits(ROM_OUT_PORT,ROM_OUT_IO)				

#define ROM_OUT    GPIO_ReadInputDataBit(ROM_OUT_PORT,ROM_OUT_IO)
					
#else
//带参宏，可以像内联函数一样使用
#define lcd_cs1(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_1);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_1)

#define lcd_rs(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_0);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_0)


#define lcd_sid(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_7);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_7)

#define lcd_sclk(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_5);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_5)
#define Rom_CS(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_10);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_10)

#define Rom_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_4);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_4)				

#define ROM_OUT    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)
#endif					
					
extern unsigned char const bmp1[];
extern unsigned char const bmp2[];
extern unsigned char const bmp3[];
extern unsigned char const jiong1[];
extern unsigned char const lei1[];


/*写指令到LCD模块*/
void transfer_command_lcd(int data1);   
/*写数据到LCD模块*/
void transfer_data_lcd(int data1);
/*延时*/
void delay(int n_ms);               
/*LCD模块初始化*/
void initial_lcd(void);
void lcd_address(unsigned char page,unsigned char column);
/*全屏清屏*/
void clear_screen(void);
/*显示128x64点阵图像*/
void display_128x64(const unsigned char *dp);
/*显示132x64点阵图像*/
//void display_132x64(unsigned char *dp);
/*显示16x16点阵图像、汉字、生僻字或16x16点阵的其他图标*/
void display_graphic_16x16(unsigned int page,unsigned int column,const unsigned char *dp);
/*显示8x16点阵图像、ASCII, 或8x16点阵的自造字符、其他图标*/
void display_graphic_8x16(unsigned int page,unsigned char column,unsigned char *dp);
/*显示5*7点阵图像、ASCII, 或5x7点阵的自造字符、其他图标*/
void display_graphic_5x7(unsigned int page,unsigned char column,unsigned char *dp);
/****送指令到晶联讯字库IC***/
void send_command_to_ROM( unsigned char datu );
/****从晶联讯字库IC中取汉字或字符数据（1个字节）***/
static unsigned char get_data_from_ROM(void);
/*从相关地址（addrHigh：地址高字节,addrMid：地址中字节,addrLow：地址低字节）中连续读出DataLen个字节的数据到 pBuff的地址*/
/*连续读取*/
void get_n_bytes_data_from_ROM(unsigned char addrHigh,unsigned char addrMid,unsigned char addrLow,unsigned char *pBuff,unsigned char DataLen );
/******************************************************************/
void display_GB2312_string(unsigned char y,unsigned char x,unsigned char *text);
void display_string_5x7(unsigned char y,unsigned char x,unsigned char *text);
void LCD_P8x16Showchar(unsigned char x, unsigned char y,unsigned char dat);
void LCD_P8x16Str(unsigned char x, unsigned char y,unsigned char ch[]);
void display_bmp(u8 x,u8 y,u8 size_x,u8 size_y,const unsigned char *dp);
void Gui_Battery(u8 x,u8 y,u8 bat);


#endif
