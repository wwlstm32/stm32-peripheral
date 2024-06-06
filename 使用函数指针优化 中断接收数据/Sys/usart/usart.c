#include "usart.h"

static void (*pcallbackfunc)(uint8_t);

/**
*@brief		回调函数 应用层调用驱动层函数 实现指针传递
*@param		无
*@return	无
*/
void (callbackfunc)(void (*processdata)(uint8_t))
{
	pcallbackfunc = processdata;
}

/**
*@brief		USART1 GPIO 配置,工作模式配置.115200 8-N-1
*@param		无
*@return	无
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
	
		
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; // USART1中断通道  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // 抢占优先级0  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; // 响应优先级0  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // IRQ通道使能  
    NVIC_Init(&NVIC_InitStructure);
	

	USART_ITConfig(USART1,  USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART1, ENABLE);
}

/**
*@brief		重定向c库函数printf到USART1
*@param		无
*@return	无
*/
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到USART1 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}
/**
*@brief		重定向c库函数scanf到USART1
*@param		无
*@return	无
*/
int fgetc(FILE *f)
{
		/* 等待串口1输入数据 */
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