#ifndef QUEUE_H
#define QUEUE_H

#include "../util.h"

typedef void* Queue;

Queue cu_queue_initialize(unsigned int bytesPerItem);

Status cu_queue_push(Queue q, byte* data);
byte*  cu_queue_peek(Queue q);
Status cu_queue_pop(Queue q);

int cu_queue_size(Queue q);

Status cu_queue_clear(Queue q);

void cu_queue_destroy(Queue* q);

#endif
