#ifndef _APP_USART_H_
#define _APP_USART_H_

#include "stm32f10x.h"
#include <stdint.h>
#include "usart.h"
#include "queue.h"

void appusart_init(void);
void usart_task(void);
#endif

