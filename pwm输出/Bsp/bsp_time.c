#include "bsp_time.h"

/*������ʱ�������ʱʱ��Ϊ910ms*/
void timer_init(uint16_t preiod_num)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_InternalClockConfig(TIM3);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	/*�Զ���װ��ֵ*/
	TIM_TimeBaseInitStruct.TIM_Period = preiod_num - 1;//ARR
	/*Ԥ����ϵ�� �������Ϊ910us*/
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;//PSC
	/*ʱ��Ԥ�������� ������ʱ��û�� */
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	/*�ظ���������ֵ ������ʱ��û��*/
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	/*������ģʽ ������ʱ��ֻ�����ϼ��� */
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStruct);
	
	/* PWMģʽ���� */
	TIM_OCInitTypeDef	TIM_OCInitStruct;
	/*ֻʹ���˲��ֽṹ����� ��Ҫ���ṹ�������ֵΪĬ��ֵ*/
	TIM_OCStructInit(&TIM_OCInitStruct);
		/*����ռ�ձȴ�С*/
	TIM_OCInitStruct.TIM_Pulse = 0;//CCR
		/*���ͨ����ƽ��������*/
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
		/*����ΪPWMģʽ1*/
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
		/*���ͨ�����е�ƽ��������*/
	TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Set;
		/*���ʹ��*/
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	
	/*������� ʹ��*/
//	/*�������ͨ�����е�ƽ��������*/
//	TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
//	/*�������ͨ����ƽ��������*/
//	TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
//	/*�������ʹ��*/
//	TIM_OCInitStruct.TIM_OutputNState = ENABLE;

	//ʹ��ͨ����Ԥװ��
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);
	TIM_Cmd(TIM3, ENABLE);	 

}

