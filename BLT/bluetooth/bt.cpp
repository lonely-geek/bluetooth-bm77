#include "bt.h"
#include "pan1026.h"
#include "io.h"  

uint8_t bt_module_type = BT_PAN1026;
volatile bool bt_device_connected = false;
volatile uint8_t bt_module_state = BT_MOD_STATE_OFF;

pan1026 bt_pan1026;
Usart bt_uart;


void bt_init()
{
	DEBUG_BT("\r\nbt_init\r\n");

	//init bt_uart
	bt_uart.InitBuffers(BUFFER_SIZE * 2, BUFFER_SIZE);
	
	//module specific code
	switch (bt_module_type)
	{
		case(BT_PAN1026):
			bt_pan1026.Init(&bt_uart);
		break;
		
		default: //UNKNOWN module
			bt_module_type = BT_PAN1026;
			bt_pan1026.Init(&bt_uart);
		break;
	}
}

void bt_unknown_parser()
{
	while (!bt_uart.isRxBufferEmpty())
	{
		uint8_t c = bt_uart.Read();
		DEBUG_BT(">> %02X %c ??\r\n", c, c);
	}
}

void bt_step()
{
	if (bt_module_state == BT_MOD_STATE_OFF)
		return;
	

	if (bt_module_type == BT_PAN1026)
		bt_pan1026.Step();

	if (bt_module_type == BT_UNKNOWN)
		bt_unknown_parser();
}

void bt_send(char * str)
{
	if (!bt_device_connected)
		return;
	
	if (bt_module_type == BT_PAN1026)
		bt_pan1026.SendString(str);
}
void bt_sendBinary(char * str,uint16_t len)
{
	if (!bt_device_connected)
		return;
	
	bt_pan1026.SendBinary(str,len);
}

void bt_irgh(uint8_t type, uint8_t * buf)
{
	switch(type)
	{
		case(BT_IRQ_INIT):
			DEBUG_BT("BT_MOD_STATE_INIT\r\n");
			bt_module_state = BT_MOD_STATE_INIT;
			LED2_ON;
		break;
		case(BT_IRQ_INIT_OK):
			DEBUG_BT("BT_MOD_STATE_OK\r\n");
			_delay_ms(10);
			bt_module_state = BT_MOD_STATE_OK;
			LED2_OFF;
		break;
		case(BT_IRQ_DEINIT):
			DEBUG_BT("BT_MOD_STATE_OFF\r\n");
			bt_module_state = BT_MOD_STATE_OFF;
			bt_device_connected = false;
		break;
		case(BT_IRQ_CONNECTED):
			DEBUG_BT("BT_IRQ_CONNECTED\r\n");
			bt_device_connected = true;
			LED2_ON;
		break;
		case(BT_IRQ_DISCONNECTED):
			DEBUG_BT("BT_IRQ_DISCONNECTED\r\n");
			bt_device_connected = false;
			LED2_OFF;
		break;
		case(BT_IRQ_RESET):
			DEBUG_BT("BT_IRQ_RESET\r\n");
			bt_device_connected = false;
		break;
		
	}
}

