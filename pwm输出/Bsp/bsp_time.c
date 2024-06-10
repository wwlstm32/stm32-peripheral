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
	
	/* PWM模式配置 */
	TIM_OCInitTypeDef	TIM_OCInitStruct;
	/*只使用了部分结构体变量 需要将结构体变量赋值为默认值*/
	TIM_OCStructInit(&TIM_OCInitStruct);
		/*设置占空比大小*/
	TIM_OCInitStruct.TIM_Pulse = 0;//CCR
		/*输出通道电平极性配置*/
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
		/*配置为PWM模式1*/
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
		/*输出通道空闲电平极性配置*/
	TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Set;
		/*输出使能*/
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	
	/*死区输出 使用*/
//	/*互补输出通道空闲电平极性配置*/
//	TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
//	/*互补输出通道电平极性配置*/
//	TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
//	/*互补输出使能*/
//	TIM_OCInitStruct.TIM_OutputNState = ENABLE;

	//使能通道和预装载
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);
	TIM_Cmd(TIM3, ENABLE);	 

}

