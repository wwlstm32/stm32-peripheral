#ifndef _BSP_LED_H_
#define _BSP_LED_H_

#include "stm32f10x.h"
void led_init(void);
void led_on(uint8_t no);
void led_off(uint8_t no);
#endif
