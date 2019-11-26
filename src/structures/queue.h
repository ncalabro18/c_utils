#ifndef QUEUE_H
#define QUEUE_H
#include "util.h"

typedef void* Queue;

Queue qu_initialize(unsigned int bytesPerItem);

Status qu_push(Queue queue, byte* item);

byte* qu_pop(Queue queue);

byte* qu_peek(Queue queue);

int qu_size(Queue queue);

Status qu_clear(Queue queue);

Boolean qu_isEmpty(Queue queue);

void qu_destroy(Queue *queue);

#endif