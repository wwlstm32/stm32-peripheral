#include "bsp_time.h"

/*基本定时器最大延时时间为910ms*/
void timer_init(uint16_t preiod_num)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_InternalClockConfig(TIM3);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	/*自动重装载值*/
	TIM_TimeBaseInitStruct.TIM_Period = preiod_num - 1;//ARR
	/*预分配系数 最大周期为910us*/
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;//PSC
	/*时钟预分配因子 基本定时器没有 */
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	/*重复计数器的值 基本定时器没有*/
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	/*计数器模式 基本定时器只有向上计数 */
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStruct);
	
	TIM_ICInitTypeDef TIM_ICInitStruct;
	/*输入捕获通道 */
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	/*输入捕获滤波器大小 */
	TIM_ICInitStruct.TIM_ICFilter = 0xf;
	/*输入捕获触发极性 */
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	/*触发信号分频器 */
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	/*触发信号 那个通道输入 */
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	
	TIM_ICInit(TIM3,&TIM_ICInitStruct);
	/*选择触发源*/
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
	/*配置从模式*/
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
	TIM_Cmd(TIM3, ENABLE);	 

}

uint32_t ic_getfreq(void)
{
	return (uint32_t)(72000000/72/(TIM_GetCapture1(TIM3) + 1)); /*freq = system/PCS+1/ARR*/
}