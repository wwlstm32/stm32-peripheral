#include "dwt.h"

/*
 在Cortex-M里面有一个外设叫DWT(Data Watchpoint and Trace)，
 该外设有一个32位的寄存器叫CYCCNT，它是一个向上的计数器，
 记录的是内核时钟运行的个数，最长能记录的时间为：
 60s=2的32次方/72000000
 (假设内核频率为72M，内核跳一次的时间大概为1/72M=13.8ns)
 当CYCCNT溢出之后，会清0重新开始向上计数。
 使能CYCCNT计数的操作步骤：
 1、先使能DWT外设，这个由另外内核调试寄存器DEMCR的位24控制，写1使能
 2、使能CYCCNT寄存器之前，先清0
 3、使能CYCCNT寄存器，这个由DWT_CTRL(代码上宏定义为DWT_CR)的位0控制，写1使能
 */

/**
*@brief		dwt初始化
*@param		无
*@return	无	
*/
void dwt_init(void)
{
	    /* 使能DWT外设 */
    DEM_CR |= (uint32_t)DEM_CR_TRCENA;                

    /* DWT CYCCNT寄存器计数清0 */
    DWT_CYCCNT = (uint32_t)0u;

    /* 使能Cortex-M DWT CYCCNT寄存器 */
    DWT_CR |= (uint32_t)DWT_CR_CYCCNTENA;
}

/**
*@brief		us延时函数
*@param		无
*@return	无	
*/
void dwt_us(uint32_t us)
{
	uint32_t tick_start = DWT_CYCCNT;
	
	/*将us转化为跳动次数*/
	us *= (SystemCoreClock/1000000);
	
	/*无符号减法 等待延时*/
	while((DWT_CYCCNT - tick_start) < us);
}

/**
*@brief		ms延时函数
*@param		无
*@return	无	
*/
void dwt_ms(uint32_t ms)
{
	/*无符号整形溢出*/
	for(uint32_t i = 0;i < ms;i++)
	{
		dwt_us(1000);
	}
}
