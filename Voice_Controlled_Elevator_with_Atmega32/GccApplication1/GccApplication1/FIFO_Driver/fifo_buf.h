/*
 * fifi_buf.h
 *
 *  Created on: Mar 14, 2023
 *      Author: Omar
 */

#ifndef FIFO_BUF_H_
#define FIFO_BUF_H_

#include "../Utilities/Platform_Types.h"

#define Element_type uint16_t

typedef struct FIFO_BUF
{
	Element_type * head;
	Element_type * tail;
	Element_type * base;
	int length;
}FIFO_BUF_t;

void FIFO_BUF_init(FIFO_BUF_t *fifo_buf, int * buf,  int length);
void enqueue(FIFO_BUF_t *fifo_buf, Element_type data);
void dequeue(FIFO_BUF_t *fifo_buf, Element_type * data);

int isFull(FIFO_BUF_t* fifo_buf);
int isEmpty(FIFO_BUF_t *fifo_buf);

#endif /* FIFO_BUF_H_ */
