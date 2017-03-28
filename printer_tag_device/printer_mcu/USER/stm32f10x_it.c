/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include"HeadType.h"
#include "usart.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}
//=============================================================================
//函数名称:TIM2_IRQHandler
//功能概要:TIM2 中断函数
//参数说明:无
//函数返回:无
//=============================================================================
void TIM2_IRQHandler(void)
{
	if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) 
	{	
		Led_Flash();
		Belt_Control();
		Key_Light_Dispose();
		Baffle_Time_Irq();
		if(Printer.start_delay_time > 0)
		{
			Printer.start_delay_time--;
		}else{
			PRINTER_START_OFF;	
			Printer.start_delay_time = 0;
		}
		if(Air_Control.delay_time > 0){
			Air_Control.delay_time--;
		}
		if(Printer.fluid_bag_timeout>0){
			Printer.fluid_bag_timeout--;
		}else{
			Control.fluid_bag.state = 0;
		}
		if(Air_Control.air_cylinder_dowm_timeout > 0){
			Air_Control.air_cylinder_dowm_timeout --;
		}
		if(Printer.printer_work_timeout > 0){
			Printer.printer_work_timeout--;
		}
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);  		 
	}		 	
}
//=============================================================================
//函数名称:TIM3_IRQHandler
//功能概要:TIM3 中断函数
//参数说明:无
//函数返回:无
//=============================================================================
void TIM3_IRQHandler(void)
{
	if ( TIM_GetITStatus(TIM3 , TIM_IT_Update) != RESET ) 
	{	
        if (1 == Usart1_Control_Data.rx_start){
            if(Auto_Frame_Time1 >0){
                Auto_Frame_Time1--;
            }else{
                Auto_Frame_Time1 = 0;
                Usart1_Control_Data.rx_aframe = 1; 
                Usart1_Control_Data.rx_count = Usart1_Control_Data.rx_index;
                Usart1_Control_Data.rx_start = 0;
                Usart1_Control_Data.rx_index = 0;
            }
        }
			Input_pulse_IRQTimer();    //所有通道电机脉冲计数
      TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update);     
	}		 	
}

//=============================================================================
//函数名称:USART1_IRQHandler
//功能概要:USART1 中断函数
//参数说明:无
//函数返回:无
//=============================================================================
void USART1_IRQHandler(void)
{
  
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE)||USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET){ //解决数据没接收完一直进中断的问题
       USART1_Do_Rx(USART_ReceiveData(USART1));
       USART_ClearFlag(USART1,USART_FLAG_RXNE);
	}
	if(USART_GetFlagStatus(USART1, USART_FLAG_TC)){
       USART1_Do_Tx();
       USART_ClearFlag(USART1,USART_FLAG_TC);
	}
}



