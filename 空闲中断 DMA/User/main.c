#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "systick.h"
#include "usart.h"
#include "bsp_led.h"
#include "app_usart.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	usart1_init();
	led_init();
	// 来到这里的时候，系统的时钟已经被配置成72M。
	while(1)
	{
		usart_task();
	}

}


