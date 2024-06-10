#include "app_usart.h"


/**
***********************************************************************
包格式：帧头0  帧头1  数据长度  功能字   LED编号  亮/灭  异或校验数据
        0x55   0xAA    0x03      0x06     0x00     0x01      0xFB
***********************************************************************
*/

static queue_t queue;
#define BUF_MAX	77
static uint8_t buf[BUF_MAX] = {0};
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
	queue_push_data(&queue,data);
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
	uint8_t readbuf[7] = {0};
	
	while(queue_pop_data(&queue,&readbuf[0]) == 1)
	{
		if(queue_pop_data(&queue,&readbuf[0]) != HEAD_0)
		{
			continue;
		}
		if((queue_pop_data(&queue,&readbuf[1]) == 0 ) || readbuf[1] != HEAD_1)
		{
			continue;
		}
		if((queue_pop_data(&queue,&readbuf[2]) == 0 ) || readbuf[2] > 7)
		{
			continue;
		}
		if(queue_pop_arr(&queue,&readbuf[CTRL_NUM],CTRL_NUM + 1) == 0)
		{
			continue;
		}
		if(usart_xor(readbuf,DATA_BUF_LEN - 1) != readbuf[DATA_BUF_LEN -1])
		{
			continue;
		}
		if(readbuf[CTRL_NUM] == 0x06)
		{
			ctrl_led((led_status* )&readbuf[CTRL_NUM + 1]);
		}
	}
}

void appusart_init(void)
{
	callbackfunc(processdata);
	queue_init(&queue,buf,BUFSIZ);
}
