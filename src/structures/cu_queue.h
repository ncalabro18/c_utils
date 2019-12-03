#ifndef QUEUE_H
#define QUEUE_H

#include "../util.h"

typedef void* CUQueue;

CUQueue cu_queue_initialize(unsigned int bytesPerItem);

Status cu_queue_push(CUQueue q, byte* data);
byte*  cu_queue_peek(CUQueue q);
Status cu_queue_pop(CUQueue q);

int cu_queue_size(CUQueue q);

Status cu_queue_clear(CUQueue q);

void cu_queue_destroy(CUQueue* q);

#endif
