/***********************************************************
酷学之家 http://simcom.taobao.com/
联系方式：15296811438 林工
*************************************************************/

#include "sys.h"
#include "io.h"   
#include "stm32f10x_exti.h"

u8 led1_blink_flag = 0;
u8 blink_interval = 0;

void IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;	
	
	// Led1 configure,PA13
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable , ENABLE); //Remap JTCK to PA14
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_14; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//Led2 configure,PD2 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	//PC4 is used for system power on, PC11 is used for blt power on 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );				
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_4;     
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;             
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	// PC2 is used as key interruption
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);				
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;     
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource2);
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn; //EXTI2_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	
	// PA6 is used as recharge interruption
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);				
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;     
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource6);
	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	
}

void LED_Disable()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable , DISABLE); 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_14; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

void LED_Recovery()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable , ENABLE); //Remap JTCK to PA14
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_14; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void LED1_Blink_Start(u16 ms)
{
	led1_blink_flag = 0x1;
	if(!ms){blink_interval = 1;return;}
	blink_interval = ms ;
}

void LED1_Blink_Stop(void)
{
	led1_blink_flag = 0x0;
	LED1_ON;
}
