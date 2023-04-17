/*
 * fifo_buf.c
 *
 *  Created on: Mar 14, 2023
 *      Author: Omar
 */


#include"fifo_buf.h"

void FIFO_BUF_init(FIFO_BUF_t *fifo_buf, int * buf,  int length)
{
	fifo_buf->head = buf;
	fifo_buf->base = buf;
	fifo_buf->tail = buf;
	fifo_buf->length = length;
}

void enqueue(FIFO_BUF_t *fifo_buf, Element_type data)
{
	if(isFull(fifo_buf))
		return ;
	*(fifo_buf->head) = data;
	if(fifo_buf->head == fifo_buf->base + fifo_buf->length)
		fifo_buf->head = fifo_buf->base;
	else
		fifo_buf->head++;
}

void dequeue(FIFO_BUF_t *fifo_buf, Element_type * data)
{
	if(isEmpty(fifo_buf))
		return ;
	*data = *(fifo_buf->tail);
	if(fifo_buf->tail == fifo_buf->base + fifo_buf->length)
		fifo_buf->tail = fifo_buf->base;
	else
		fifo_buf->tail++;
}

int isFull(FIFO_BUF_t *fifo_buf)
{
	if((fifo_buf->head ) == (fifo_buf->base + fifo_buf->length))
	{
		if(fifo_buf->tail  == fifo_buf->base )
			return 1;
	}
	if( (fifo_buf->head + 1) == fifo_buf->tail )
		return 1;
	return 0;
}


int isEmpty(FIFO_BUF_t *fifo_buf)
{
	if(fifo_buf->tail  == fifo_buf->head)
		return 1;
	return 0;
}




