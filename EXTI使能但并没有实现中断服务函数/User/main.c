#include "stm32f10x.h"  

#include "systick.h"
#include "usart.h"
#include "key.h"

/*ʹ���ж� ��û�ж����жϷ����� �������жϺ� ����Ῠ��B.��*/
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


