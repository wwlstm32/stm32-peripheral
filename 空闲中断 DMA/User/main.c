#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
#include "systick.h"
#include "usart.h"
#include "bsp_led.h"
#include "app_usart.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	usart1_init();
	led_init();
	// ���������ʱ��ϵͳ��ʱ���Ѿ������ó�72M��
	while(1)
	{
		usart_task();
	}

}


