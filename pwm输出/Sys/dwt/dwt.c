#include "dwt.h"

/*
 ��Cortex-M������һ�������DWT(Data Watchpoint and Trace)��
 ��������һ��32λ�ļĴ�����CYCCNT������һ�����ϵļ�������
 ��¼�����ں�ʱ�����еĸ�������ܼ�¼��ʱ��Ϊ��
 60s=2��32�η�/72000000
 (�����ں�Ƶ��Ϊ72M���ں���һ�ε�ʱ����Ϊ1/72M=13.8ns)
 ��CYCCNT���֮�󣬻���0���¿�ʼ���ϼ�����
 ʹ��CYCCNT�����Ĳ������裺
 1����ʹ��DWT���裬����������ں˵��ԼĴ���DEMCR��λ24���ƣ�д1ʹ��
 2��ʹ��CYCCNT�Ĵ���֮ǰ������0
 3��ʹ��CYCCNT�Ĵ����������DWT_CTRL(�����Ϻ궨��ΪDWT_CR)��λ0���ƣ�д1ʹ��
 */

/**
*@brief		dwt��ʼ��
*@param		��
*@return	��	
*/
void dwt_init(void)
{
	    /* ʹ��DWT���� */
    DEM_CR |= (uint32_t)DEM_CR_TRCENA;                

    /* DWT CYCCNT�Ĵ���������0 */
    DWT_CYCCNT = (uint32_t)0u;

    /* ʹ��Cortex-M DWT CYCCNT�Ĵ��� */
    DWT_CR |= (uint32_t)DWT_CR_CYCCNTENA;
}

/**
*@brief		us��ʱ����
*@param		��
*@return	��	
*/
void dwt_us(uint32_t us)
{
	uint32_t tick_start = DWT_CYCCNT;
	
	/*��usת��Ϊ��������*/
	us *= (SystemCoreClock/1000000);
	
	/*�޷��ż��� �ȴ���ʱ*/
	while((DWT_CYCCNT - tick_start) < us);
}

/**
*@brief		ms��ʱ����
*@param		��
*@return	��	
*/
void dwt_ms(uint32_t ms)
{
	/*�޷����������*/
	for(uint32_t i = 0;i < ms;i++)
	{
		dwt_us(1000);
	}
}
