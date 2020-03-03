#include "cu_queue.h"
#include <stdlib.h>
#include <string.h>


#define cast(x) ((CU_QUEUE*)(x))

typedef struct Node{
	struct Node *next;	
	byte *data;
} Node;

Node* createNode(byte* data, unsigned int itemSize);

typedef struct CU_QUEUE{
	unsigned int itemCount;
	unsigned int itemSize;
	Node *head;
	Node *tail;
} CU_QUEUE;




CUQueue cu_queue_initialize(unsigned int bytesPerItem){
	CU_QUEUE *q = (CU_QUEUE*) malloc(sizeof(CU_QUEUE));
	if(!q) return NULL;
	
	q->itemCount = 0;
	q->itemSize = bytesPerItem;
	q->head = NULL;
	q->tail = NULL;

	return q;
}

Status cu_queue_push(CUQueue q, byte* data){
	if(!q || !data) return FAILURE;	
	Node *n = createNode(data, cast(q)->itemSize);
	if(!n) return FAILURE;

	//inits head to first entree
	if(cast(q)->head == NULL)
		cast(q)->head = n;
	if(cast(q)->tail != NULL)
		cast(q)->tail->next = n;

	cast(q)->tail = n;


	//update itemCount
	cast(q)->itemCount++;
	return SUCCESS;
}


byte*  cu_queue_peek(CUQueue q){
	if(!q || !cast(q)->head || cast(q)->itemCount == 0) return NULL;

	return cast(q)->head->data;
}


Status cu_queue_pop(CUQueue q){
	if(!q || !cast(q)->head || cast(q)->itemCount == 0) return FAILURE;

	//saves second entree
	Node *temp = cast(q)->head->next;
	//clears first entree
	free(cast(q)->head);
	//reassigns head to the second entree
	cast(q)->head = temp;
	
	cast(q)->itemCount--;
	return SUCCESS;
}


int cu_queue_length(CUQueue q){
	if(!q) return -1;

	return cast(q)->itemCount;
}


Status cu_queue_clear(CUQueue q){
	if(!q) return FAILURE;

	while(cu_queue_pop(q) != FAILURE);


	return SUCCESS;
}


void cu_queue_destroy(CUQueue* q){
	if(!q || !*q) return;
	
	while(cu_queue_pop(*q) != FAILURE);
	free(*q);

	*q = NULL;

	return;
}



Node* createNode(byte* data, unsigned int itemSize){
	Node *n = malloc(sizeof(Node) + itemSize);
	if(!n) return NULL;

	n->next = NULL;
	//uses one malloc to allocate both the Node and the Node data
	//the data always points at the end of the Node,
	//(the cast is to prevent pointer arithmetic from using 4/8 byte increments instead of 1)
	n->data = (byte*) &n[1];

	memcpy(n->data, data, itemSize);

	return n;
}
	


