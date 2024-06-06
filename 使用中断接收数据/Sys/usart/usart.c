#include "usart.h"

/**
***********************************************************************
����ʽ��֡ͷ0  ֡ͷ1  ���ݳ���  ������   LED���  ��/��  ���У������
        0x55   0xAA    0x03      0x06     0x00     0x01      0xFB
***********************************************************************
*/

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

uint8_t buf[8] = {0};
static uint8_t flag = 0;
volatile uint8_t g_res = 0;
#define HEAD_0			0x55
#define HEAD_1			0xAA
#define CTRL_NUM		3
#define DATA_BUF_LEN	7

 typedef struct
{
	uint8_t switch_status;
	uint8_t led_num;
	
}led_status;
static void processdata(uint8_t data)
{
	static uint8_t i = 0;
	buf[i++] = data;
	switch(i)
	{
		case 1:
				if(buf[0] != HEAD_0)
				{
					i = 0;
				}
				printf("1");
				break;
		case 2:
				if(buf[1] != HEAD_1)
				{
					i = 0;
				}
				printf("2");
				break;
		case DATA_BUF_LEN:
				flag = 1;
				i = 0;
				printf("7");
				break;
		
		default:
				break;
			
	}
}
static uint8_t usart_xor(uint8_t* buf,uint8_t len)
{
	uint8_t res = 0;
	for(uint8_t i = 0;i < len;i++)
	{
		res ^= buf[i];
	}
	printf("xoor");
	g_res = res;
	return res;
}
extern void led_off(uint8_t no);
extern void led_on(uint8_t no);

static void ctrl_led(led_status* led_state)
{
	printf("119");
	(led_state->switch_status == 0x00)?(led_off(led_state->led_num)):(led_on(led_state->led_num));
}

void usart_task(void)
{
	if(flag != 1)
	{
		return ;
	}
	flag = 0;
	
	if(usart_xor(buf,DATA_BUF_LEN - 1) != buf[DATA_BUF_LEN -1])
	{
		
		return;
	}
	
	if(buf[CTRL_NUM] == 0x06)
	{
		ctrl_led((led_status* )&buf[4]);
	}
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
		processdata(data);
	}
}