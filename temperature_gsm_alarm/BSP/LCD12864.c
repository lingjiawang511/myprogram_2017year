/*****************************************************/
//描述：LCD12864的驱动
//作者：小四叶草
//时间：2015/07/16
//描述：显示与按键
//s2 ---------GPIO52 ;s3-----------GPIO54 ; s4 -------GPIO72 ; s5 ----GPIO71;
//两种写法：1.消抖；2.状态机
//按键消抖的是时间是20ms
/*****************************************************/
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define LCD_DATA		(*((volatile Uint16 *)0x45EF))
#define E				GpioDataRegs.GPBDAT.bit.GPIO61
#define RW				GpioDataRegs.GPADAT.bit.GPIO27
#define RS 				GpioDataRegs.GPBDAT.bit.GPIO60
#define LOW 			0
#define HIGH			1
#define CLEAR_SCREEN	0x01		//清屏指令：清屏且AC值为00H
#define AC_INIT			0x02		//将AC设置为00H。且游标移到原点位置
#define CURSE_ADD		0x06		//设定游标移到方向及图像整体移动方向（默认游标右移，图像整体不动）
#define FUN_MODE		0x30		//工作模式：8位基本指令集
#define DISPLAY_ON		0x0c		//显示开,显示游标，且游标位置反白
#define DISPLAY_OFF		0x08		//显示关
#define CURSE_DIR		0x14		//游标向右移动:AC=AC+1
#define SET_CG_AC		0x40		//设置AC，范围为：00H~3FH
#define SET_DD_AC		0x80 
#define s2 GpioDataRegs.GPBDAT.bit.GPIO54
#define s3 GpioDataRegs.GPBDAT.bit.GPIO55
#define s4 GpioDataRegs.GPBDAT.bit.GPIO56
#define s5 GpioDataRegs.GPBDAT.bit.GPIO57

#define	DELAY_MS(A)		DELAY_US((long double)A * 1000.0L)
#define DELAY_100US(B)	DELAY_US((long double)B * 100.0L)

void InitXintf(void);
void ConfigGpio(void);
void InitLcd(void);
void Read_Busy(void);
void WriteCmd12864(Uint16 cmd);
void WriteData12864(Uint16 dat);
void DisplayDdram(uchar *hz);
void DispBMP(uchar *adress);
void CLR_GDRAM(void);
void Disp(void);
void fanbai(uchar y,uchar x1,uchar x2);
void  key(void);
void xuanze();
void xunhuan(uchar hang);
void jiantou(uchar hang);


uchar tab1[]="设置参数值";
uchar tab2[]="查询参数值";

uchar tab3[]="查询历史故障";
uchar tab4[]="清除历史故障";
uchar tab5[]="第二级菜单显示";

uchar key2 = 0;
uchar key3 = 0;
uchar key4 = 0;
uchar key5 = 0;

uchar keyindex = 0; //初始化的时候是第一行，选择行的索引
uchar keycur = 0; //0,1,2,3 显示屏的当前行

void main(void)
{
	InitSysCtrl();
	InitXintf();
	InitXintf16Gpio();
	DINT;
	InitPieCtrl();
	
	IER = 0x0000;
	IFR = 0x0000;
	
	ConfigGpio();
	InitLcd();
	WriteCmd12864(CLEAR_SCREEN);
	DELAY_US(50);
	
	Disp();
	
	WriteCmd12864(0x34); //开启扩展指令
	
	fanbai(0,2,11);
	

	WriteCmd12864(0x36);
	WriteCmd12864(0x30); //返回到基本指令
	
	while(1)
	{
		xuanze();
	}

}

void ConfigGpio(void)
{
	EALLOW;
	//===12864====================================
	GpioCtrlRegs.GPBMUX2.bit.GPIO60 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO60 = 1;
	GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO61 = 1;
	GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO27 = 1;
	//===12864====================================
	
	//===key====================================
	GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 0; //s2 GPIO 
	GpioCtrlRegs.GPBDIR.bit.GPIO54= 0;  //input
	GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 0; //s2 GPIO 
	GpioCtrlRegs.GPBDIR.bit.GPIO55= 0;  //input
	GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 0; //s2 GPIO 
	GpioCtrlRegs.GPBDIR.bit.GPIO56= 0;  //input
	GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 0; //s2 GPIO 
	GpioCtrlRegs.GPBDIR.bit.GPIO57= 0;  //input
	
	//disable pull-up
	
	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;
	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;
	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;
	//===key====================================
	
	EDIS;
}

void InitLcd(void)
{
	DELAY_100US(5);
	WriteCmd12864(FUN_MODE);
	DELAY_US(5);
	
	WriteCmd12864(FUN_MODE);
	DELAY_US(5);
	
	WriteCmd12864(0x0C);
	DELAY_US(5);
	
	WriteCmd12864(CLEAR_SCREEN);
	DELAY_US(30);
	
	WriteCmd12864(AC_INIT);
	DELAY_US(4);

}
void Read_Busy() //读忙标志最高位为1，则busy,不能进行读写操作
{
 	RS = LOW;
	RW = HIGH;
	E = HIGH;
	while(LCD_DATA & 0X80);
	E = LOW;
}
void WriteCmd12864(Uint16 cmd)
{
	Read_Busy();
	RS = LOW;
	RW = LOW;//写数据
	E = HIGH;
	LCD_DATA  = cmd;
	E = LOW;
}

void WriteData12864(Uint16 dat)
{
	Read_Busy();
	RS = HIGH;
	RW = LOW;//写数据
	E = HIGH;
	LCD_DATA  = dat;
	E = LOW;
}

void DisplayDdram(uchar *hz)
{
	while(*hz != '\0')
	{
		WriteData12864(*hz);//地址里面的值
		hz++;
	}
}
//初步显示的画面，选择第一行反白显示
void Disp()
{
	WriteCmd12864(0x81);
	DisplayDdram(tab1);
	WriteCmd12864(0x91);
	DisplayDdram(tab2);
	
	WriteCmd12864(0x89);
	DisplayDdram(tab3);
	WriteCmd12864(0x99);
	DisplayDdram(tab4);
}
//选择某一行反白显示，和某一行的几个数据显示（连续）
//y = {0,1,2,3}
//x = {0,...15} //修改数据 一行有16个数据
void fanbai(uchar y,uchar x1,uchar x2)
{
	uchar x_adress;
	uchar i;
	uchar j;
	switch(y)
	{
		case 0: x_adress = 0x80;break;
		case 1: x_adress = 0x90;break;
		case 2: x_adress = 0x88;break;
		case 3: x_adress = 0x98;break;
		default: x_adress = 0x80;break;
	}
	
	if(0x80 == x_adress) //显示屏的第一行
	{
		for(i = 0; i < 32; i++)
		{
			WriteCmd12864(0x80 + i); //y
			WriteCmd12864(0x80);     //x
			if(i < 16)
			{
				for(j =0;j < 16;j++)
				{
					if((j >= x1) & (j <= x2))
					{
						WriteData12864(0xff); 
					}
					else
					{
						WriteData12864(0x00);
					}
				}
				
			}
			else //显示屏的第二行
			{
				for(j =0;j < 16;j++)
				{
					
					WriteData12864(0x00);
				
				}
			}
		}
		for(i = 0;i < 32; i++)//显示屏的第三四行
		{
			WriteCmd12864(0x80 + i);
			WriteCmd12864(0x88);
			for(j = 0;j <16; j++)
			{
				WriteData12864(0x00);
			}
		}
			
	}
	if(0x90 == x_adress) //第二行
	{
		for(i = 0; i < 32; i++)
		{
			WriteCmd12864(0x80 + i); //y
			WriteCmd12864(0x80);     //x
			if(i < 16)//显示屏第一行
			{
				for(j =0;j < 16;j++) 
				{
					WriteData12864(0x00);
				}
				
			}
			else
			{
				for(j =0;j < 16;j++)
				{
					
					if((j >= x1) & (j <= x2))
					{
						WriteData12864(0xff); 
					}
					else
					{
						WriteData12864(0x00);
					}
				
				}
			}
		}
		for(i = 0;i < 32; i++) //第三四行
		{
			WriteCmd12864(0x80 + i);
			WriteCmd12864(0x88);
			for(j = 0;j <16; j++)
			{
				WriteData12864(0x00);
			}
		}
			
	}
	if(0x88 == x_adress) //显示屏的第三行
	{
		for(i = 0;i < 32; i++) //显示屏的第一二行
		{
			WriteCmd12864(0x80 + i);
			WriteCmd12864(0x80);
			for(j = 0;j <16; j++)
			{
				WriteData12864(0x00); 
			}
		}
		for(i = 0; i < 32; i++)
		{
			WriteCmd12864(0x80 + i); //y
			WriteCmd12864(0x88);     //x
			if(i < 16)
			{
				for(j =0;j < 16;j++) //显示屏第三行
				{
					if((j >= x1) & (j <= x2))
					{
						WriteData12864(0xff); 
					}
					else
					{
						WriteData12864(0x00);
					}
				}
				
			}
			else //显示屏第四行
			{
				for(j =0;j < 16;j++)
				{
					WriteData12864(0x00);
				}
			}
		}
		
			
	}
	
	if(0x98 == x_adress) //显示屏的第三行
	{
		for(i = 0;i < 32; i++) //显示屏的第一二行
		{
			WriteCmd12864(0x80 + i);
			WriteCmd12864(0x80);
			for(j = 0;j <16; j++)
			{
				WriteData12864(0x00); 
			}
		}
		for(i = 0; i < 32; i++)
		{
			WriteCmd12864(0x80 + i); //y
			WriteCmd12864(0x88);     //x
			if(i < 16)
			{
				for(j =0;j < 16;j++) //显示屏第三行
				{
					WriteData12864(0x00);
				}
			}
			else //显示屏第四行
			{
				for(j =0;j < 16;j++)
				{
					if((j >= x1) & (j <= x2))
					{
						WriteData12864(0xff); 
					}
					else
					{
						WriteData12864(0x00);
					}
				}
			}
		}
		
			
	}
		
}

//按上移下移键，发白显示那一行
//s4 --上移，s5 --下移
void key()
{
	//1.设置对应IO为输入,在ConfigGpio（）里面，已经设置。
	if(0 == s4) //检测到被按下
	{
		DELAY_US(1000); //延时10MS,前消抖
		if(0 == s4)
		{
			while(!s4); //确认被按下，等下释放
			key5 ++;
		}			
		
	}
	
	if(0 == s5) //检测到被按下
	{
		DELAY_US(1000); //延时10MS,前消抖
		if(0 == s5)
		{
			while(!s5); //确认被按下，等下释放
			key5 ++;
		}			
		
	}
}

void xuanze()
{
	static int16 key_yidong = 0;
	static k = 0;
	if(0 == s4) //上移，检测到被按下
	{
		DELAY_US(1000); //延时10MS,前消抖
		if(0 == s4)
		{
			while(!s4); //确认被按下，等下释放
			key_yidong --;
			if(-1 == key_yidong)
			{
				key_yidong = 3;
				k++;
			}
			xunhuan(key_yidong);
			
		}			
		
	}
	if(0 == s5) //检测到被按下
	{
		DELAY_US(1000); //延时10MS,前消抖
		if(0 == s5)
		{
			while(!s5); //确认被按下，等下释放
			key_yidong ++;
			if(4 == key_yidong)
			{
				key_yidong = 0;
			}
			xunhuan(key_yidong);
		}			
		
	}
	
	
	
}

void xunhuan(uchar hang)
{
	switch(hang)
	{
		case 0: 
			WriteCmd12864(0x34); //开启扩展指令
			fanbai(0,2,11);
			WriteCmd12864(0x36);
			WriteCmd12864(0x30); //返回到基本指令
			jiantou(0);
			break;
		case 1: 
			WriteCmd12864(0x34); //开启扩展指令
			fanbai(1,2,11);
			WriteCmd12864(0x36);
			WriteCmd12864(0x30); //返回到基本指令
			WriteCmd12864(0x90);
			WriteData12864(0x10);
			jiantou(1);
			break;
		case 2: 
			WriteCmd12864(0x34); //开启扩展指令
			fanbai(2,2,13);
			WriteCmd12864(0x36);
			WriteCmd12864(0x30); //返回到基本指令
			jiantou(2);
			break;
		case 3: 
			WriteCmd12864(0x34); //开启扩展指令
			fanbai(3,2,13);
			WriteCmd12864(0x36);
			WriteCmd12864(0x30); //返回到基本指令
			jiantou(3);
			break;
		default:
			WriteCmd12864(0x34); //开启扩展指令
			fanbai(0,2,13);
			WriteCmd12864(0x36);
			WriteCmd12864(0x30); //返回到基本指令
			jiantou(0);
			break;
	}
	
}
void jiantou(uchar hang)
{
	switch(hang)
	{
		case 0: 
			WriteCmd12864(0x80);
			WriteData12864(0x10);
			WriteCmd12864(0x90);
			WriteData12864(0x20);
			WriteCmd12864(0x88);
			WriteData12864(0x20);
			WriteCmd12864(0x98);
			WriteData12864(0x20);
			break;
		case 1:
			WriteCmd12864(0x80);
			WriteData12864(0x20);
			WriteCmd12864(0x90);
			WriteData12864(0x10);
			WriteCmd12864(0x88);
			WriteData12864(0x20);
			WriteCmd12864(0x98);
			WriteData12864(0x20);
			break;
		case 2:
			WriteCmd12864(0x80);
			WriteData12864(0x20);
			WriteCmd12864(0x90);
			WriteData12864(0x20);
			WriteCmd12864(0x88);
			WriteData12864(0x10);
			WriteCmd12864(0x98);
			WriteData12864(0x20);
			break;
		case 3:
			WriteCmd12864(0x80);
			WriteData12864(0x20);
			WriteCmd12864(0x90);
			WriteData12864(0x20);
			WriteCmd12864(0x88);
			WriteData12864(0x20);
			WriteCmd12864(0x98);
			WriteData12864(0x10);
			break;
		default:
			WriteCmd12864(0x80);
			WriteData12864(0x10);
			WriteCmd12864(0x90);
			WriteData12864(0x20);
			WriteCmd12864(0x88);
			WriteData12864(0x20);
			WriteCmd12864(0x98);
			WriteData12864(0x20);
			break;
	}
}
