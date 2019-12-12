#ifndef CU_HEAP_H
#define CU_HEAP_H

#include "../util.h"

typedef void* CUHeap;


//the function is used to maintain the heap
//when the function returns TRUE, the first parameter is set as the parent
CUHeap cu_heap_init(unsigned int itemSize, unsigned int itemCapacity, Boolean(*setToRoot)(byte*, byte*));

Status cu_heap_buildHeap(CUHeap, byte *array, unsigned int arrayCount);

//basic heap operations
Status cu_heap_push(CUHeap, byte *item);
byte* cu_heap_peek(CUHeap);
Status cu_heap_pop(CUHeap);

//returns the number of items stored int the heap
int cu_heap_length(CUHeap);


Boolean cu_heap_isEmpty(CUHeap);

//frees all memory associated with the heap
void cu_heap_destroy(CUHeap*);

//basic compare functions
//ex, to create a max heap for ints, use 
//CUHeap heap = cu_heap_init(sizeof(int), 8, cu_heap_cmpfunc_MAX_INT);
Boolean cu_heap_cmpfunc_MIN_INT    (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MIN_UINT   (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MIN_CHAR   (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MIN_UCHAR  (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MIN_SHORT  (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MIN_USHORT (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MIN_LONG   (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MIN_ULONG  (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MIN_FLOAT  (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MIN_DOUBLE (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MIN_LDOUBLE(byte *a, byte *b);


Boolean cu_heap_cmpfunc_MAX_INT    (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MAX_UINT   (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MAX_CHAR   (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MAX_UCHAR  (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MAX_SHORT  (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MAX_USHORT (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MAX_LONG   (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MAX_ULONG  (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MAX_FLOAT  (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MAX_DOUBLE (byte *a, byte *b);
Boolean cu_heap_cmpfunc_MAX_LDOUBLE(byte *a, byte *b);

#endif
