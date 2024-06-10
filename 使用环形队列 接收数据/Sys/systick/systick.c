#include "systick.h"

/**
*@brief		配置滴答定时器
*@param		无
*@return	无
*/
void systick_init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);/*使用外部时钟源*/
	
	SysTick->LOAD = 0;
	
	SysTick->VAL = 0; 
}

/**
*@brief		微秒延时函数
*@param		延时时间
*@return	无
*/
void delay_us(uint16_t us)
{
	uint32_t fus = 9 * us;

	SysTick->LOAD = fus;
	
	SysTick->VAL = 0;
	
	SysTick->CTRL |= (1<<0);

	while((SysTick->CTRL & (1<<16)) == 0);
	
	SysTick->CTRL &= ~(1<<0);
	
	SysTick->VAL = 0;
}

/**
*@brief		毫秒延时函数
*@param		延时时间
*@return	无
*@note		
*/
void delay_ms(uint16_t ms)
{
	
	if(ms < 1800)
	{
		SysTick->LOAD = 9000 * ms;
		
		SysTick->VAL = 0;
	
		SysTick->CTRL |= (1<<0);
		
		while((SysTick->CTRL & (1<<16) && (SysTick->CTRL & 0x01)) == 0);
		
		SysTick->CTRL &= ~(1<<0);
		
		SysTick->VAL = 0;
	}
	else
	{
		for(uint8_t i = 0;i < (ms/1800);i++)
		{
			SysTick->LOAD = 9000 * 1800;
			
			SysTick->VAL = 0;
		
			SysTick->CTRL |= (1<<0);
			
			while((SysTick->CTRL & (1<<16) && (SysTick->CTRL & 0x01)) == 0);
			
			SysTick->CTRL &= ~(1<<0);
		}
		
		SysTick->LOAD = (ms%1800) * 9000;
		
		SysTick->VAL = 0;
		
		SysTick->CTRL |= (1<<0);
			
		while((SysTick->CTRL & (1<<16) && (SysTick->CTRL & 0x01)) == 0);
		
		SysTick->CTRL &= ~(1<<0);
		
		SysTick->VAL = 0;
	}

}

