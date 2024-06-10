#include "queue.h"

/**
*@brief		队列初始化
*@param		queue 队列变量指针
			buf  存放数据的数组
			size 数组的大小
*@return	0-error 1-success
*/
void queue_init(queue_t* queue,uint8_t* buf,uint32_t size)
{
	queue->buf = buf;
	queue->size = size;
	queue->head = 0;
	queue->tail = 0;
}
/**
*@brief		单个字节入列
*@param		queue 队列变量指针
			data  入列数据
*@return	0-error 1-success
*/
uint8_t queue_push_data(queue_t* queue,uint8_t data)
{
	if(((queue->tail + 1) % queue->size) == queue->head)
	{
		/*队列满*/
		return 0;
	}
	queue->buf[queue->tail] = data;
	queue->tail = (queue->tail + 1) % queue->size;
	// 不能使用queue->tail += 1; tail会溢出
	return 1;
}

/**
*@brief		单个字节出列
*@param		queue 队列变量指针
			pdata  出列数据存放地址
*@return	0-error 1-success
*/
uint8_t queue_pop_data(queue_t* queue,uint8_t* pdata)
{
	if(queue->tail == queue->head)
	{
		/*队列空*/
		return 0;
	}
	
	*pdata = queue->buf[queue->head];
	queue->head = (queue->head + 1) % queue->size;
	return 1;
}

/**
*@brief		一组数据入列
*@param		queue 队列变量指针
			arr  入列数据的地址
			len	 数据的长度
*@return	压入数据的长度
*/
uint32_t queue_push_arr(queue_t* queue,uint8_t* arr,uint32_t len)
{
	uint32_t i;
	for(i= 0;i < len;i++)
	{
		if(queue_push_data(queue,arr[i]) == 0)
			break;
	}
	return i;
}

/**
*@brief		一组数据出列
*@param		queue 队列变量指针
			arr  存放出列数据的地址
			len	 数据的长度
*@return	实际出列数据的长度
*/
uint32_t queue_pop_arr(queue_t* queue,uint8_t* arr,uint32_t len)
{
	uint32_t i;
	for(i = 0;i < len;i++)
	{
		if(queue_pop_data(queue,&arr[i]) == 0)
			break;
	}
	return i;
}

