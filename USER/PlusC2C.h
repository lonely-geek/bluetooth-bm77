
#include "stm32f10x.h"


#ifndef __PLUSC2C_H__
#define __PLUSC2C_H__

#ifdef __cplusplus
extern "C" {
#endif

//#include "stm32f10x.h"
//#include "bt.h"
	
void C_bt_init(void);
void C_bt_step(void);
void C_bt_send(char * str);
void C_bt_sendBinary(char * str,uint16_t len);

#ifdef __cplusplus
}
#endif


#endif
	
