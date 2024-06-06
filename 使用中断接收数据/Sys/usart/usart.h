#ifndef _USART_H_
#define _USART_H_

#include "stm32f10x.h"
#include <stdio.h>
void usart1_init(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
void usart_task(void);
#endif
