#include "stack.h"
#include "arraylist.h"
#include "stdlib.h"

#define cast(x) ((STACK*)(x))


typedef struct _stack {
	ArrayList list;
}STACK;


Stack st_initialize(unsigned int bytesPer, unsigned int initialCapacity) {
	STACK *stack = (STACK*)malloc(sizeof(STACK));
	if (stack == NULL)
		return NULL;

	stack->list = al_initialize(bytesPer, initialCapacity);
	if (stack->list == NULL) {
		free(stack);
		return NULL;
	}

	return (Stack)stack;
}

byte* st_pop(Stack stack) {
	if(stack == NULL || al_isEmpty(cast(stack)->list))
		return NULL;
	
	int index = al_size(cast(stack)->list) - 1;
	
	if (index < 0)
		return NULL;
	
	byte *item = al_get(cast(stack)->list, index);
	
	if (item == NULL)
		return NULL;
	
	if ( !al_remove(cast(stack)->list, index) )
		return NULL;

	return item;
}

Status st_push(Stack stack, byte *item) {
	if (stack == NULL)
		return FAILURE;

	return al_append(cast(stack)->list, item);
}


byte* st_peek(Stack stack) {
	if (stack == NULL)
		return NULL;
	int index = al_size(cast(stack)->list) - 1;

	if (index < 0)
		return NULL;

	return al_get(cast(stack)->list, index);
}


Status st_clear(Stack stack) {
	if (stack == NULL)
		return FAILURE;
	return al_clear(cast(stack)->list);
}


int st_size(Stack stack) {
	if (stack == NULL)
		return -3;
	return al_size(cast(stack)->list);
}


Boolean st_isEmpty(Stack stack) {
	if (stack == NULL)
		return TRUE;
	return al_isEmpty(cast(stack)->list);
}


void st_destroy(Stack *stack) {
	if (stack == NULL || *stack == NULL)
		return;
	al_destroy(cast(*stack)->list);
	free(*stack);

	return;
}
