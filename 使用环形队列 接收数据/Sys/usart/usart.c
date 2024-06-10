#include "usart.h"

static void (*pcallbackfunc)(uint8_t);

/**
*@brief		�ص����� Ӧ�ò���������㺯�� ʵ��ָ�봫��
*@param		��
*@return	��
*/
void (callbackfunc)(void (*processdata)(uint8_t))
{
	pcallbackfunc = processdata;
}

/**
*@brief		USART1 GPIO ����,����ģʽ����.115200 8-N-1
*@param		��
*@return	��
*/
void usart1_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 
	/* config USART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	/* USART1 GPIO config */
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    
	/* Configure USART1 Rx (PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
	/* USART1 mode config */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure); 
	
		
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; // USART1�ж�ͨ��  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // ��ռ���ȼ�0  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; // ��Ӧ���ȼ�0  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // IRQͨ��ʹ��  
    NVIC_Init(&NVIC_InitStructure);
	

	USART_ITConfig(USART1,  USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART1, ENABLE);
}

/**
*@brief		�ض���c�⺯��printf��USART1
*@param		��
*@return	��
*/
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ�USART1 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}
/**
*@brief		�ض���c�⺯��scanf��USART1
*@param		��
*@return	��
*/
int fgetc(FILE *f)
{
		/* �ȴ�����1�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		uint8_t data = (uint8_t)USART_ReceiveData(USART1);
		pcallbackfunc(data);
	}
}