#include "usart.h"

void usart1_dma(void);
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
	

	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	
	USART_Cmd(USART1, ENABLE);
	
	usart1_dma();
}

#define  USART_DR_ADDRESS        (USART1_BASE+0x04)
extern uint8_t buf[20];
uint8_t flag = 0;
void usart1_dma(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	/*DMAԴ��ַ:�������ݼĴ�����ַ*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART_DR_ADDRESS;
	/*DMAĿ�ĵ�ַ:���ձ�����ָ��*/
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)buf;
	/*DMA���䷽��:���赽�ڴ�*/
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	/*�����С*/
	DMA_InitStructure.DMA_BufferSize =20;
	
	/*�ڴ����ݵ�λ*/
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	/*�ڴ����ݵ���*/
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	
	/*�������ݵ�λ*/
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*�����ַ����*/
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	/*ѭ��ģʽ*/
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	/*���ȼ�����*/
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	/*��ֹ�ڴ浽�ڴ�Ĵ���*/
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);		
	// ʹ��DMA
	DMA_Cmd (DMA1_Channel4,ENABLE);
	
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
	uint16_t clear_idle = 0;
	if(USART_GetITStatus(USART1, USART_IT_IDLE) == SET)
	{
		/*��������ж�*/
		clear_idle = USART1->SR;//��SR�Ĵ���
		clear_idle = USART1->DR;//��DR�Ĵ���
		if(20 - DMA_GetCurrDataCounter(DMA1_Channel4) == 7)
		{
			flag = 1;
		}
		/*Normalģʽ�¼������Ĵ���������DMAͨ���رյ�����²���д*/
		DMA_Cmd(DMA1_Channel4, DISABLE);
		DMA_SetCurrDataCounter(DMA1_Channel4,20);
		DMA_Cmd(DMA1_Channel4, ENABLE);
	}
}