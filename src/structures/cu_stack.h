#ifndef STACK_H
#define STACK_H
#include "../util.h"


typedef void* CUStack;


//creates a new stack with the internal settings set to bytesPer
//and allocated enough space to hold initialCapacity items (not bytes)
CUStack cu_stack_init(unsigned int bytesPer, unsigned int initialCapacity);


//pops the stack, removing the top item
Status cu_stack_pop(CUStack stack);


//pushes the stack, adding the new item to the data structure
Status cu_stack_push(CUStack stack, byte *item);


//examines the top item from the stack and returns the adress of it
byte* cu_stack_peek(CUStack stack);


//clears all items stored in the stack
Status cu_stack_clear(CUStack stack);


//returns the number of items stored in the stack
int cu_stack_size(CUStack stack);


//returns whether or not the stack is empty
//returns true if there is one or more item stored, false otherwise
Boolean cu_stack_isEmpty(CUStack stack);


//frees allocated memory associated with the CUStack
//NOTE pass in the address of the CUStack handle
void cu_stack_destroy(CUStack *stack);

#endif
