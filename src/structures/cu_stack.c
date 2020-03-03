#include "cu_stack.h"
#include "cu_arraylist.h"

#include <stdlib.h>

#define cast(x) ((CU_STACK*)(x))


typedef struct CU_STACK {
	CUArrayList list;
}CU_STACK;


CUStack cu_stack_init(unsigned int bytesPer, unsigned int initialCapacity) {
	CU_STACK *stack = (CU_STACK*)malloc(sizeof(CU_STACK));
	if (stack == NULL)
		return NULL;

	stack->list = cu_arraylist_init(bytesPer, initialCapacity);
	if (stack->list == NULL) {
		free(stack);
		return NULL;
	}

	return (CUStack)stack;
}

Status cu_stack_pop(CUStack stack) {
	if(stack == NULL || cu_arraylist_isEmpty(cast(stack)->list))
		return FAILURE;
	
	int index = cu_arraylist_length(cast(stack)->list) - 1;
	
	if(index < 0)
		return FAILURE;
	
	if (cu_arraylist_remove(cast(stack)->list, index) == FAILURE)
		return FAILURE;

	return SUCCESS;
}

Status cu_stack_push(CUStack stack, byte *item) {
	if (stack == NULL)
		return FAILURE;

	return cu_arraylist_append(cast(stack)->list, item);
}


byte* cu_stack_peek(CUStack stack) {
	if (stack == NULL)
		return NULL;
	int index = cu_arraylist_length(cast(stack)->list) - 1;

	if (index < 0)
		return NULL;

	return cu_arraylist_get(cast(stack)->list, index);
}


Status cu_stack_clear(CUStack stack) {
	if (stack == NULL)
		return FAILURE;
	return cu_arraylist_clear(cast(stack)->list);
}


int cu_stack_length(CUStack stack) {
	if (stack == NULL)
		return -3;
	return cu_arraylist_length(cast(stack)->list);
}


Boolean cu_stack_isEmpty(CUStack stack) {
	if (stack == NULL)
		return TRUE;
	return cu_arraylist_isEmpty(cast(stack)->list);
}


void cu_stack_destroy(CUStack *stack) {
	if (stack == NULL || *stack == NULL)
		return;
    	cu_arraylist_destroy(&cast(*stack)->list);
	free(*stack);

	return;
}
