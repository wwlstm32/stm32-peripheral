#include "stm32f10x.h"  

#include "systick.h"
#include "usart.h"
#include "key.h"

/*使能中断 但没有定义中断服务函数 当发生中断后 程序会卡在B.出*/
int main(void)
{
	usart1_init();
	key_init();
	key_exti_init();

	while(1)
	{
		delay_ms(2000);
		printf("1\r\n");
	}

}


