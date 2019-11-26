#include "queue.h"
#include "arraylist.h"
#include <stdlib.h>

#define cast(x) ((QUEUE*)(x))

typedef  struct _node Node;

struct _node {
	Node *next;
	byte* data
};

typedef struct _queue {
	unsigned int bytesPerItem;
	Node *head;
	Node *tail;
} QUEUE ;

Queue qu_initialize(unsigned int bytesPerItem) {
	QUEUE *queue = (QUEUE*)malloc(sizeof(QUEUE));
	if (queue == NULL)
		return NULL;

	queue->head = NULL;
	queue->tail = NULL;
	queue->bytesPerItem = bytesPerItem;

	return (Queue) queue;
}

Status qu_push(Queue q, byte* item) {
	if (q == NULL || item == NULL)
		return FAILURE;
	
	QUEUE *queue = cast(q);

	Node *newNode = malloc(sizeof(Node));

	return SUCCESS;
}

byte* qu_pop(Queue queue){

    return NULL;
}

byte* qu_peek(Queue queue){

    return NULL;
}

int qu_size(Queue queue){

    return 0;
}

Status qu_clear(Queue queue) {
	while (qu_pop(queue) != NULL);
	return SUCCESS;
}

Boolean qu_isEmpty(Queue queue) {
	if (queue == NULL)
		return TRUE;
	if (cast(queue)->tail == NULL)
		return TRUE;
	return FALSE;
}

void qu_destroy(Queue *queue) {
	if (queue == NULL || *queue == NULL)
		return;

	while (qu_pop(*queue) != NULL);

	free(*queue);
	*queue = NULL;
	return;
}