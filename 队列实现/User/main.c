#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
#include "systick.h"
#include "usart.h"
#include "dwt.h"

int main(void)
{
	usart1_init();
	//systick_init();
	dwt_init();
	// ���������ʱ��ϵͳ��ʱ���Ѿ������ó�72M��
	while(1)
	{
		//delay_ms(2000);
		dwt_ms(2000);
		printf("1\r\n");
	}

}


