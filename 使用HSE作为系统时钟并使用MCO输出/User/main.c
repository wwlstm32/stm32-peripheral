#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>

void hse_config(uint32_t RCC_PLLMul_x);
void hsi_config(uint32_t RCC_PLLMul_x);

int main(void)
{
	// 来到这里的时候，系统的时钟已经被配置成72M。
}


void hse_config(uint32_t RCC_PLLMul_x)
{
	ErrorStatus hse_status;
	
	RCC_DeInit();
	/*使能hse*/
	RCC_HSEConfig(RCC_HSE_ON);
	
	/*等待hse使能成功*/
	do
	{
		hse_status = RCC_WaitForHSEStartUp();
	}while(hse_status != SUCCESS);
	
	/*使能预取缓冲区*/
	
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	FLASH_SetLatency(FLASH_Latency_2);
	
	
	    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
      
    /* PCLK2 = HCLK */
	RCC_PCLK2Config(RCC_HCLK_Div1);
    
    /* PCLK1 = HCLK */
    RCC_PCLK1Config(RCC_HCLK_Div2);
	
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_x);
	
	RCC_PLLCmd(ENABLE);
	
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET);
	
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	
	while(RCC_GetSYSCLKSource() != 0x80);	
}

void hsi_config(uint32_t RCC_PLLMul_x)
{
	volatile uint32_t hsi_status;
	
	RCC_DeInit();
	/*使能hsi*/
	RCC_HSICmd(ENABLE);
	
	/*等待hsi使能成功*/
	do
	{
		hsi_status = RCC->CR & RCC_CR_HSIRDY;;
	}while(hsi_status != RCC_CR_HSIRDY);
	
	/*使能预取缓冲区*/
	
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	FLASH_SetLatency(FLASH_Latency_2);
	
	
	    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
      
    /* PCLK2 = HCLK */
	RCC_PCLK2Config(RCC_HCLK_Div1);
    
    /* PCLK1 = HCLK */
    RCC_PCLK1Config(RCC_HCLK_Div2);
	
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_x);
	
	RCC_PLLCmd(ENABLE);
	
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET);
	
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	
	while(RCC_GetSYSCLKSource() != 0x80);	
}
