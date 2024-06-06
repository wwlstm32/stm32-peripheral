#include "app_usart.h"

/**
***********************************************************************
包格式：帧头0  帧头1  数据长度  功能字   LED编号  亮/灭  异或校验数据
        0x55   0xAA    0x03      0x06     0x00     0x01      0xFB
***********************************************************************
*/

uint8_t buf[8] = {0};
static uint8_t flag = 0;
#define HEAD_0			0x55
#define HEAD_1			0xAA
#define CTRL_NUM		3
#define DATA_BUF_LEN	7

 typedef struct
{
	uint8_t switch_status;
	uint8_t led_num;
	
}led_status;

void processdata(uint8_t data)
{
	static uint8_t i = 0;
	buf[i++] = data;
	switch(i)
	{
		case 1:
				if(buf[0] != HEAD_0)
				{
					i = 0;
				}
				break;
		case 2:
				if(buf[1] != HEAD_1)
				{
					i = 0;
				}
				break;
		case DATA_BUF_LEN:
				flag = 1;
				i = 0;
				break;
		
		default:
				break;
			
	}
}
static uint8_t usart_xor(uint8_t* buf,uint8_t len)
{
	uint8_t res = 0;
	for(uint8_t i = 0;i < len;i++)
	{
		res ^= buf[i];
	}
	return res;
}
extern void led_off(uint8_t no);
extern void led_on(uint8_t no);

static void ctrl_led(led_status* led_state)
{
	
	(led_state->switch_status == 0x00)?(led_off(led_state->led_num)):(led_on(led_state->led_num));
}

void usart_task(void)
{
	if(flag != 1)
	{
		return ;
	}
	flag = 0;
	
	if(usart_xor(buf,DATA_BUF_LEN - 1) != buf[DATA_BUF_LEN -1])
	{
		
		return;
	}
	
	if(buf[CTRL_NUM] == 0x06)
	{
		ctrl_led((led_status* )&buf[4]);
	}
}

void appusart_init(void)
{
	callbackfunc(processdata);
}