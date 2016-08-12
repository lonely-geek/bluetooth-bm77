/*
 * bt.h
 *
 *  Created on: 8.7.2014
 *      Author: horinek
 */

#ifndef BT_H_
#define BT_H_

#include "common.h"

#define BT_IRQ_INIT					0
#define BT_IRQ_INIT_OK			1
#define BT_IRQ_DEINIT				2
#define BT_IRQ_CONNECTED		3
#define BT_IRQ_DISCONNECTED	4
#define BT_IRQ_RESET				5

#define BT_PAN1322	0
#define BT_PAN1026	1
#define BT_UNKNOWN	0xFF

#define BT_MOD_STATE_OFF	0
#define BT_MOD_STATE_INIT	1
#define BT_MOD_STATE_OK		2

void bt_init();
void bt_step();
void bt_send(char * str);
void bt_sendBinary(char * str,uint16_t len);
void bt_irgh(uint8_t type, uint8_t * buf);

extern volatile uint8_t bt_module_state;

#endif /* BT_H_ */
