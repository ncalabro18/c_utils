#include "cu_stack.h"
#include "cu_arraylist.h"
#include "stdlib.h"

#define cast(x) ((STACK*)(x))


typedef struct _stack {
	ArrayList list;
}STACK;


Stack cu_stack_init(unsigned int bytesPer, unsigned int initialCapacity) {
	STACK *stack = (STACK*)malloc(sizeof(STACK));
	if (stack == NULL)
		return NULL;

	stack->list = cu_arraylist_init(bytesPer, initialCapacity);
	if (stack->list == NULL) {
		free(stack);
		return NULL;
	}

	return (Stack)stack;
}

byte* cu_stack_pop(Stack stack) {
	if(stack == NULL || cu_arraylist_isEmpty(cast(stack)->list))
		return NULL;
	
	int index = cu_arraylist_size(cast(stack)->list) - 1;
	
	if (index < 0)
		return NULL;
	
	byte *item = cu_arraylist_get(cast(stack)->list, index);
	
	if (item == NULL)
		return NULL;
	
	if ( !cu_arraylist_remove(cast(stack)->list, index) )
		return NULL;

	return item;
}

Status cu_stack_push(Stack stack, byte *item) {
	if (stack == NULL)
		return FAILURE;

	return cu_arraylist_append(cast(stack)->list, item);
}


byte* cu_stack_peek(Stack stack) {
	if (stack == NULL)
		return NULL;
	int index = cu_arraylist_size(cast(stack)->list) - 1;

	if (index < 0)
		return NULL;

	return cu_arraylist_get(cast(stack)->list, index);
}


Status cu_stack_clear(Stack stack) {
	if (stack == NULL)
		return FAILURE;
	return cu_arraylist_clear(cast(stack)->list);
}


int cu_stack_size(Stack stack) {
	if (stack == NULL)
		return -3;
	return cu_arraylist_size(cast(stack)->list);
}


Boolean cu_stack_isEmpty(Stack stack) {
	if (stack == NULL)
		return TRUE;
	return cu_arraylist_isEmpty(cast(stack)->list);
}


void cu_stack_destroy(Stack *stack) {
	if (stack == NULL || *stack == NULL)
		return;
    cu_arraylist_destroy(cast(*stack)->list);
	free(*stack);

	return;
}
