#include "cu_queue.h"
#include <stdlib.h>
#include <string.h>


#define cast(x) ((_queue*)(x))

typedef struct Node{
	struct Node* next;	
	byte *data;
} Node;

Node* createNode(byte* data, unsigned int itemSize);

typedef struct _queue{
	unsigned int itemCount;
	unsigned int itemSize;
	Node *head;
	Node *tail;
}_queue;



Queue cu_queue_initialize(unsigned int bytesPerItem){
	_queue *q = (_queue*) malloc(sizeof(_queue));
	if(!q) return NULL;
	
	q->itemCount = 0;
	q->itemSize = bytesPerItem;
	q->head = NULL;
	q->tail = NULL;

	return q;
}

Status cu_queue_push(Queue q, byte* data){
	if(!q || !data) return FAILURE;	


	Node *n = createNode(data, cast(q)->itemSize);
	if(!n) return FAILURE;

	if(cast(q)->tail == NULL)
		cast(q)->tail = n;


	n->next = cast(q)->head;
	cast(q)->head = n;

	cast(q)->itemCount++;
	return SUCCESS;
}


byte*  cu_queue_peek(Queue q){
	if(!q) return NULL;

	return cast(q)->tail->data;
}


Status cu_queue_pop(Queue q){
	if(!q) return FAILURE;
	
	if(cast(q)->tail == NULL) return FAILURE;

	Node *temp = cast(q)->tail;
	cast(q)->tail = cast(q)->tail->next;
	
	free(temp);

	cast(q)->itemCount--;

	return SUCCESS;
}


int cu_queue_size(Queue q){
	if(!q) return -1;

	return cast(q)->itemCount;
}


Status cu_queue_clear(Queue q){
	if(!q) return FAILURE;

	while(cu_queue_pop(q) != FAILURE);


	return SUCCESS;
}


void cu_queue_destroy(Queue* q){
	if(!q || !*q) return;
	
	while(cu_queue_pop(*q) != FAILURE);
	free(*q);

	*q = NULL;

	return;
}



Node* createNode(byte* data, unsigned int itemSize){
	Node * n = malloc(sizeof(Node) + itemSize);
	if(!n) return NULL;

	n->next = NULL;
	//uses one malloc to allocate both the Node and the Node data
	//the data always points at the end of the Node,
	//(the cast is to prevent pointer arithmatic from using 4/8 byte increments instead of 1)
	n->data = ((byte*)n) + sizeof(Node);

	memcpy(n->data, data, itemSize);

	return n;
}
	


