#include "cu_heap.h"
#include "../cu_utils.h"
#include <stdlib.h>
#include <string.h>

#define cast(x) ((CU_HEAP*)(x))

typedef struct CU_HEAP{

	unsigned int itemCapacity;
	unsigned int itemSize;
	unsigned int itemCount;
	byte *data;

	Boolean (*setToRoot ) (byte*,byte*);
}CU_HEAP;


unsigned int getLeft(unsigned int root);
unsigned int getRight(unsigned int root);
unsigned int getRoot(unsigned int lr);

//tests if the given heap has space for another item
//will resize the array if no space is found
Status cu_heap_resize(CUHeap h, unsigned int minimumIndex);
void memswap(byte*,byte*,unsigned int size);

CUHeap cu_heap_init(unsigned int itemSize, unsigned int itemCapacity, Boolean (*function)(byte*, byte*)){
	CU_HEAP *heap = (CU_HEAP*) malloc(sizeof(CU_HEAP));
	if(heap == NULL) return NULL;

	heap->data = (byte*) malloc(itemSize * itemCapacity);
	if(heap->data == NULL) return NULL;
	
	heap->itemCapacity = itemCapacity;
	heap->itemSize = itemSize;
	heap->itemCount = 0;
	heap->setToRoot = function;
	return heap;
}

Status cu_heap_buildHeap(CUHeap h, byte *array, unsigned int arrayCount){
	if(!h || !cu_heap_isEmpty(h)) return FAILURE;
	CU_HEAP *heap = cast(h);
	if(cu_heap_resize(h, arrayCount) == FAILURE) return FAILURE;

	memcpy(heap->data, array, arrayCount);
	heap->itemCount = arrayCount;
	
	//start at the last element
	unsigned int currentIndex;
	for(unsigned int i = arrayCount - 1; i > 0; i--){
		currentIndex = getRoot(i);
		unsigned int left = getLeft(currentIndex);
		unsigned int right = getRight(currentIndex);
		
		if(heap->setToRoot(
		heap->data + heap->itemSize * left,
		heap->data + heap->itemSize + currentIndex))
		{	
			if(heap->setToRoot(
			heap->data + heap->itemSize * right,
			heap->data + heap->itemSize * left))
			
				cuswap_memory(
				heap->data + heap->itemSize * right,
				heap->data + heap->itemSize * currentIndex,
				heap->itemSize);

			else
				cuswap_memory(	
				heap->data + heap->itemSize * left,
				heap->data + heap->itemSize * currentIndex,
				heap->itemSize);
		}
		else
		{
			if(heap->setToRoot(
			heap->data + heap->itemSize * right,
			heap->data + heap->itemSize * currentIndex))
				cuswap_memory(
				heap->data + heap->itemSize * right,
				heap->data + heap->itemSize * currentIndex,
				heap->itemSize);
		}
	}	

	return SUCCESS;
}

Status cu_heap_push(CUHeap h, byte *item){
	if(!h || !item) return FAILURE;

	if(cu_heap_resize(h, cast(h)->itemCount) == FAILURE)
		return FAILURE;

	memcpy(cast(h)->data + cast(h)->itemSize * cast(h)->itemCount, item, cast(h)->itemSize);

	unsigned int index = cast(h)->itemCount;

	while(index > 0){
		unsigned int parent = getRoot(index);
		if(cast(h)->setToRoot (
			cast(h)->data + cast(h)->itemSize * index,
			cast(h)->data + cast(h)->itemSize * parent))
		{	
			cuswap_memory(	cast(h)->data + cast(h)->itemSize * index,
				       	cast(h)->data + cast(h)->itemSize * parent,
				  	cast(h)->itemSize);
			index = parent;
		}
		else
			break;
	}

	cast(h)->itemCount++;
	return SUCCESS;
}

byte* cu_heap_peek(CUHeap h){
	if(!h || cu_heap_isEmpty(h)) return NULL;

	return cast(h)->data;
}		

Status cu_heap_pop(CUHeap h){
	if(!h || cu_heap_isEmpty(h)) return FAILURE;

		
	memcpy(cast(h)->data, cast(h)->data + (cast(h)->itemCount - 1) * cast(h)->itemSize, cast(h)->itemSize);
	cast(h)->itemCount--;	

	unsigned int index = 0;
	unsigned int left = getLeft(index);
	unsigned int right = getRight(index);
	while(index < cast(h)->itemCount){
		if(cast(h)->setToRoot(
		cast(h)->data + cast(h)->itemSize * left,	
		cast(h)->data + cast(h)->itemSize * index)){

			if(cast(h)->setToRoot(
			cast(h)->data + cast(h)->itemSize * right,
			cast(h)->data + cast(h)->itemSize * left))

				cuswap_memory(	cast(h)->data + cast(h)->itemSize * right,
						cast(h)->data + cast(h)->itemSize * index,
						cast(h)->itemSize);
			else
				cuswap_memory(	cast(h)->data + cast(h)->itemSize * left,
						cast(h)->data + cast(h)->itemSize * index,
						cast(h)->itemSize);
		}
		else
			if(cast(h)->setToRoot(
			cast(h)->data + cast(h)->itemSize * right,
			cast(h)->data + cast(h)->itemSize * index))
			{
				cuswap_memory(	cast(h)->data + cast(h)->itemSize * right,
						cast(h)->data + cast(h)->itemSize * index,
						cast(h)->itemSize);				
			}
			else
				break;
	}

	return SUCCESS;
}

int cu_heap_length(CUHeap h){
	if(!h) return -1;
	return cast(h)->itemCount;
}

Boolean cu_heap_isEmpty(CUHeap h){
	if(!h || cast(h)->itemCount == 0)
		return TRUE;
	return FALSE;
}

void cu_heap_destroy(CUHeap* hp){
	if(!hp || !*hp) return;
	free(cast(*hp)->data);
	free(*hp);
	*hp = NULL;
}


unsigned int getLeft(unsigned int root){
	return root * 2 + 1;
}
unsigned int getRight(unsigned int root){
	return root * 2 + 2;
}
unsigned int getRoot(unsigned int lr){
	return (lr + 1) / 2;
}

Status cu_heap_resize(CUHeap h, unsigned int minimumIndex){
	if(!h) return FAILURE;
	if( minimumIndex >= cast(h)->itemCapacity){
		byte *temp = (byte*) realloc(cast(h)->data, cast(h)->itemSize * cast(h)->itemCapacity * 2);
		if(!temp) return FAILURE;

		cast(h)->itemCapacity *= 2;
		cast(h)->data = temp;
		//buildheap may require more space tha twice the ammount
		return cu_heap_resize(h, minimumIndex);
	}
	return SUCCESS;
}


Boolean cu_heap_cmpfunc_MIN_INT(byte *a, byte *b){
	return *((int*)a) < *((int*)b);
}
Boolean cu_heap_cmpfunc_MIN_UINT(byte *a, byte *b){
	return *((unsigned int*)a) < *((unsigned int*)b);
}
Boolean cu_heap_cmpfunc_MIN_CHAR(byte *a, byte *b){
	return *((char*)a) < *((char*)b);
}
Boolean cu_heap_cmpfunc_MIN_UCHAR(byte *a, byte *b){
	return *((unsigned char*)a) < *((unsigned char*)b);
}
Boolean cu_heap_cmpfunc_MIN_SHORT(byte *a, byte *b){
	return *((short*)a) < *((short*)b);
}
Boolean cu_heap_cmpfunc_MIN_USHORT(byte *a, byte *b){
	return *((unsigned short*)a) < *((unsigned short*)b);
}
Boolean cu_heap_cmpfunc_MIN_LONG(byte *a, byte *b){
	return *((long*)a) < *((long*)b);
}
Boolean cu_heap_cmpfunc_MIN_ULONG(byte *a, byte *b){
	return *((unsigned long*)a) < *((unsigned long*)b);
}
Boolean cu_heap_cmpfunc_MIN_FLOAT(byte *a, byte *b){
	return *((float*)a) < *((float*)b);
}
Boolean cu_heap_cmpfunc_MIN_DOUBLE(byte *a, byte *b){
	return *((double*)a) < *((double*)b);
}
Boolean cu_heap_cmpfunc_MIN_LDOUBLE(byte *a, byte *b){
	return *((long double*)a) < *((long double*)b);
}


Boolean cu_heap_cmpfunc_MAX_INT(byte *a, byte *b){
	return *((int*)a) > *((int*)b);
}
Boolean cu_heap_cmpfunc_MAX_UINT(byte *a, byte *b){
	return *((unsigned int*)a) > *((unsigned int*)b);
}
Boolean cu_heap_cmpfunc_MAX_CHAR(byte *a, byte *b){
	return *((char*)a) > *((char*)b);
}
Boolean cu_heap_cmpfunc_MAX_UCHAR(byte *a, byte *b){
	return *((unsigned char*)a) > *((unsigned char*)b);
}
Boolean cu_heap_cmpfunc_MAX_SHORT(byte *a, byte *b){
	return *((short*)a) > *((short*)b);
}
Boolean cu_heap_cmpfunc_MAX_USHORT(byte *a, byte *b){
	return *((unsigned short*)a) > *((unsigned short*)b);
}
Boolean cu_heap_cmpfunc_MAX_LONG(byte *a, byte *b){
	return *((long*)a) > *((long*)b);
}
Boolean cu_heap_cmpfunc_MAX_ULONG(byte *a, byte *b){
	return *((unsigned long*)a) > *((unsigned long*)b);
}
Boolean cu_heap_cmpfunc_MAX_FLOAT(byte *a, byte *b){
	return *((float*)a) > *((float*)b);
}
Boolean cu_heap_cmpfunc_MAX_DOUBLE(byte *a, byte *b){
	return *((double*)a) > *((double*)b);
}
Boolean cu_heap_cmpfunc_MAX_LDOUBLE(byte *a, byte *b){
	return *((long double*)a) > *((long double*)b);
}
