#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "systick.h"
#include "usart.h"
#include "dwt.h"

int main(void)
{
	usart1_init();
	//systick_init();
	dwt_init();
	// 来到这里的时候，系统的时钟已经被配置成72M。
	while(1)
	{
		//delay_ms(2000);
		dwt_ms(2000);
		printf("1\r\n");
	}

}


