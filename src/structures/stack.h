#ifndef STACK_H
#define STACK_H
#include "util.h"


typedef void* Stack;


//creates a new stack with the internal settings set to bytesPer
//and allocated enough space to hold initialCapacity items (not bytes)
Stack st_initialize(unsigned int bytesPer, unsigned int initialCapacity);


//pops the stack, removing the top item and returning it
//returns NULL on failure
byte* st_pop(Stack stack);


//pushes the stack, adding the new item to the data structure
Status st_push(Stack stack, byte *item);


//examines the top item from the stack and returns the adress of it
byte* st_peek(Stack stack);


//clears all items stored in the stack
Status st_clear(Stack stack);


//returns the number of items stored in the stack
int st_size(Stack stack);


//returns whether or not the stack is empty
//returns true if there is one or more item stored, false otherwise
Boolean st_isEmpty(Stack stack);


//frees allocated memory associated with the Stack
//NOTE pass in the adress of the Stack handle
void st_destroy(Stack *stack);

#endif