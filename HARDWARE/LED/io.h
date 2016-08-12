#ifndef __IO_H
#define __IO_H	 

#include "sys.h"

//LED端口定义
#define LED1 PAout(14)
#define LED2 PDout(2)
#define BT_POWER PCout(11)
#define SYS_POWER PCout(4)


#define LED1_ON LED1 = 1
#define LED2_ON LED2 = 1	
#define BT_POWER_ON BT_POWER = 1
#define SYS_POWER_ON SYS_POWER = 1

#define LED1_OFF LED1 = 0
#define LED2_OFF LED2 = 0	
#define BT_POWER_OFF BT_POWER = 0
#define SYS_POWER_OFF SYS_POWER = 0
	
void IO_Init(void);//初始化
void LED_Disable(void);//关闭
void LED_Recovery(void);//恢复
void LED1_Blink_Start(u16 ms);
void LED1_Blink_Stop(void);		 			
#endif
