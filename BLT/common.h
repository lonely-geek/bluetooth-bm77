/*
 * common.h
 *
 *  Created on: 12.9.2014
 *      Author: horinek
 */

#ifndef COMMON_H_
#define COMMON_H_

//#define DEBUG_BT_ENABLED

#ifdef DEBUG_BT_ENABLED
	#define DEBUG_BT(...) DEBUG(__VA_ARGS__)
#else
	#define DEBUG_BT(...)
#endif



#include "string.h"
#include <stdio.h>
#include "delay.h"
#include  "stm32_usart.h"


#define PROGMEM	
#define BUFFER_SIZE	    64
#define HW_REW_1504		0
#define hw_revision		HW_REW_1504


#define PSTR(A) 		(char *)(A)


extern uint8_t device_id[11]; //11byte

extern void GetID_str(char * id); //22 byte


#define pgm_read_byte(A)	*A
#define _delay_ms(A)		delay_ms(A)

extern uint32_t task_get_ms_tick(void );

#define fprintf_P( A , B , C ) \
	for (uint8_t i = 0; i < strlen(this->label); i++) \
		this->StreamWrite(this->label[i]) \
 

#define ISR(A)  				void UNUSEDFUNCTION_##A (void)
#define DEBUG 					printf

typedef struct tg2
{ 
	uint8_t bt_link_key[16];
	//add
	uint8_t btle_mac[6];
	//end add
}cfg_connectivity;

typedef struct tg1 
{
	cfg_connectivity connectivity;

}cfg_t;

extern volatile  cfg_t config;

#define config_ee config
#define config_ro config

#endif /* COMMON_H_ */
