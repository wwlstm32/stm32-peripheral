#include "bsp_led.h"

void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOF, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 |GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_0);
	GPIO_SetBits(GPIOB,GPIO_Pin_1);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	GPIO_SetBits(GPIOF,GPIO_Pin_7);
	GPIO_SetBits(GPIOF,GPIO_Pin_8);
}
static void ledred_on(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	GPIO_SetBits(GPIOB,GPIO_Pin_1);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
}

static void ledred_off(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_0);
//	GPIO_SetBits(GPIOB,GPIO_Pin_1);
//	GPIO_SetBits(GPIOB,GPIO_Pin_5);
}
void led_on(uint8_t no)
{
	switch(no)
	{
		case 0:
				ledred_on();	
				break;
		case 1:
				GPIO_ResetBits(GPIOF,GPIO_Pin_7);
				break;
		case 2:
				GPIO_ResetBits(GPIOF,GPIO_Pin_8);
				break;
		default:
			break;
	}
}

void led_off(uint8_t no)
{
	switch(no)
	{
		case 0:
				ledred_off();	
				break;
		case 1:
				GPIO_SetBits(GPIOF,GPIO_Pin_7);
				break;
		case 2:
				GPIO_SetBits(GPIOF,GPIO_Pin_8);
				break;
		default:
			break;
	}
}