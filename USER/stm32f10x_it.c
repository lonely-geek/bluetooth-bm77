/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
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
#include "stm32f10x_exti.h"
#include "io.h"

volatile u16 ms_delay = 0;
volatile u32 ms_timer = 0;
u8 io_status ;

void SysTick_Handler ( void )
{
	ms_delay++;
	ms_timer++;
}

void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)
	{
			EXTI_ClearITPendingBit(EXTI_Line2); 
			io_status = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2);
			if(!io_status)
			{
				ms_delay = 0;
			}
			else
			{
				if(ms_delay > 600)
				{
					SYS_POWER_OFF;
				}
			}
	}
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	{
			EXTI_ClearITPendingBit(EXTI_Line6); 
			io_status = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
			if(!io_status)
			{
				LED1_Blink_Start(1000);
			}
			else
			{
				LED1_Blink_Stop();
			}
	}
}

