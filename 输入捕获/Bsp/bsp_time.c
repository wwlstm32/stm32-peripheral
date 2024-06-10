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
	
	TIM_ICInitTypeDef TIM_ICInitStruct;
	/*���벶��ͨ�� */
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	/*���벶���˲�����С */
	TIM_ICInitStruct.TIM_ICFilter = 0xf;
	/*���벶�񴥷����� */
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	/*�����źŷ�Ƶ�� */
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	/*�����ź� �Ǹ�ͨ������ */
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	
	TIM_ICInit(TIM3,&TIM_ICInitStruct);
	/*ѡ�񴥷�Դ*/
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
	/*���ô�ģʽ*/
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
	TIM_Cmd(TIM3, ENABLE);	 

}

uint32_t ic_getfreq(void)
{
	return (uint32_t)(72000000/72/(TIM_GetCapture1(TIM3) + 1)); /*freq = system/PCS+1/ARR*/
}