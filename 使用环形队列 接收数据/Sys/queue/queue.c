#include "queue.h"

/**
*@brief		���г�ʼ��
*@param		queue ���б���ָ��
			buf  ������ݵ�����
			size ����Ĵ�С
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
*@brief		�����ֽ�����
*@param		queue ���б���ָ��
			data  ��������
*@return	0-error 1-success
*/
uint8_t queue_push_data(queue_t* queue,uint8_t data)
{
	if(((queue->tail + 1) % queue->size) == queue->head)
	{
		/*������*/
		return 0;
	}
	queue->buf[queue->tail] = data;
	queue->tail = (queue->tail + 1) % queue->size;
	// ����ʹ��queue->tail += 1; tail�����
	return 1;
}

/**
*@brief		�����ֽڳ���
*@param		queue ���б���ָ��
			pdata  �������ݴ�ŵ�ַ
*@return	0-error 1-success
*/
uint8_t queue_pop_data(queue_t* queue,uint8_t* pdata)
{
	if(queue->tail == queue->head)
	{
		/*���п�*/
		return 0;
	}
	
	*pdata = queue->buf[queue->head];
	queue->head = (queue->head + 1) % queue->size;
	return 1;
}

/**
*@brief		һ����������
*@param		queue ���б���ָ��
			arr  �������ݵĵ�ַ
			len	 ���ݵĳ���
*@return	ѹ�����ݵĳ���
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
*@brief		һ�����ݳ���
*@param		queue ���б���ָ��
			arr  ��ų������ݵĵ�ַ
			len	 ���ݵĳ���
*@return	ʵ�ʳ������ݵĳ���
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

