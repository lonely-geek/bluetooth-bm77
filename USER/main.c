#include "sys.h"
#include "plusc2c.h"
#include <stdio.h>

#define TX_STR_SIZE 128

extern u8 led1_blink_flag ;
extern u8 blink_interval ;
volatile uint8_t Uart1_pos=0;
char rx_char[TX_STR_SIZE] = {0x0};
uint8_t count = 0;

uint8_t uart1_is_rx_buffer_empty(void)
{
	return !(Uart1_RcvCnt - Uart1_pos);
}

uint8_t uart1_read(void)
{
	uint8_t c;
	c = Uart1_Buff[Uart1_pos++];
	if(Uart1_RcvCnt == Uart1_pos){
		Uart1_RcvCnt = Uart1_pos = 0;
	}	
	return c;
}

void msg_process(void)
{
	while(!uart1_is_rx_buffer_empty()&& count < TX_STR_SIZE)
		rx_char[count++] = uart1_read();
	if(count >= TX_STR_SIZE)
	{
		count = 0;
		return;
	}
	if(count > 0 && rx_char[count-1] == ':') //Space character is used as seperator
	{
		rx_char[count-1] = 0x0 ;
 		C_bt_send(rx_char);
		count = 0 ;
	}
}


int main ( void )
{
	
	SystemInit();//系统时钟等初始化

	if(SysTick_Config(72000*1))	 //配置错误返回1,max 16777216   默认72Mhz 时钟 ,1ms延时							
		while(1);
	
	IO_Init();		
	NVIC_Configuration();
	Uart1Init ( 115200 );  
	Uart3Init ( 115200 );
	
	if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6))//检测到是充电模式
		LED1_Blink_Start(1000);
	else
	{
		SYS_POWER_ON;
		LED1_ON;
	}
	
	BT_POWER_OFF;
	C_bt_init();
	BT_POWER_ON;
	
	printf("\nInitial OK !\n");
	
	while(1)
	{
		if((ms_timer % 1) == 0)
		{
			C_bt_step();
			msg_process();
		}
		//process uart1 buffer 
		//if((ms_timer % 20) == 0)
		//msg_process();
			
		if(led1_blink_flag)
			if((ms_timer % blink_interval) == 0)
			{
				LED1 = !LED1 ;
			}
				
	}
	
}
