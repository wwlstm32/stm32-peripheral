#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "stm32f10x.h"
#include <stdint.h>
void systick_init(void);

void delay_us(uint16_t us);

void delay_ms(uint16_t ms);

#endif
