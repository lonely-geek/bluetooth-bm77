#include "plusc2c.h"
#include  "bt.h"

void C_bt_init(void)
{
	bt_init();
}

void C_bt_step(void)
{
	bt_step();
}

void C_bt_send(char * str)
{
	bt_send(str);
}

void C_bt_sendBinary(char * str,uint16_t len)
{
	bt_sendBinary(str, len);
}
