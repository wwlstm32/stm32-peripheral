#ifndef __DWT_H_
#define __DWT_H_
#include <stdint.h>
#include "system_stm32f10x.h"
#define  DWT_CR      *(volatile uint32_t *)0xE0001000
#define  DWT_CYCCNT  *(volatile uint32_t *)0xE0001004
#define  DEM_CR      *(volatile uint32_t *)0xE000EDFC

#define  DEM_CR_TRCENA                   (1 << 24)
#define  DWT_CR_CYCCNTENA                (1 <<  0)

void dwt_init(void);
void dwt_us(uint32_t us);
void dwt_ms(uint32_t ms);

#endif
