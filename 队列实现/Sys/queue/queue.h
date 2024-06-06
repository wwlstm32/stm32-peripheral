#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "stm32f10x.h"
#include <stdint.h>

typedef struct
{
	uint32_t head;
	uint32_t tail;
	uint32_t size;
	uint8_t* buf;
}queue_t;
void queue_init(queue_t* queue,uint8_t* buf,uint32_t size);

uint8_t queue_push_data(queue_t* queue,uint8_t data);

uint8_t queue_pop_data(queue_t* queue,uint8_t* pdata);

uint32_t queue_push_arr(queue_t* queue,uint8_t* arr,uint32_t len);

uint32_t queue_pop_arr(queue_t* queue,uint8_t* arr,uint32_t len);

#endif