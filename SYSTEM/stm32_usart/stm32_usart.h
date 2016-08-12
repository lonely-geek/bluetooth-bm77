#ifndef __STM32_USART_H
#define __STM32_USART_H

#ifdef __cplusplus
	extern "C"{
#endif
		
#define MAXBUF 256

extern u8 Uart1_Buff[MAXBUF];
extern volatile u16 Uart1_RcvCnt;
		
extern u8 Uart3_Buff[MAXBUF];
extern volatile u16 Uart3_RcvCnt;

void Uart1Init(u32 bound);
void Uart1SendHex(u8 ch);
void Uart1SendStr(u8* str);
		
void Uart3Init(u32 bound);
void Uart3SendHex(u8 ch);
void Uart3SendStr(u8* str);

#ifdef __cplusplus
	}
#endif

#endif
