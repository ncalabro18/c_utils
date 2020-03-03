#include "cu_arraylist.h"
#include <stdlib.h>
#include <string.h>

#define cast(x) ((ARRAYLIST*)x)

typedef struct arraylist {
	unsigned int bytesPerItem;
	unsigned int itemCount;
	unsigned int itemCapacity;
	byte *data;

} ARRAYLIST;

#define RESIZE_MODIFIER 2
Status cu_arraylist_resize(ARRAYLIST *list, unsigned int newItemCapacity);

CUArrayList cu_arraylist_init(unsigned int bytesPerItem, unsigned int initialItemCapacity) {
	ARRAYLIST *list = (ARRAYLIST*)malloc(sizeof(ARRAYLIST));
	if (list == NULL)
		return NULL;


	list->data = (byte*)malloc(bytesPerItem * initialItemCapacity);
	if (list->data == NULL) {
		free(list);
		return NULL;
	}

	list->bytesPerItem = bytesPerItem;
	list->itemCapacity = initialItemCapacity;
	list->itemCount = 0;

	return (CUArrayList) list;
}


byte* cu_arraylist_get(CUArrayList list, unsigned int index) {
	if (list == NULL)
		return NULL;
	
	return &(cast(list)->data[ index * cast(list)->bytesPerItem ]);
}

Status cu_arraylist_set(CUArrayList list, const byte *data, unsigned int index) {
	if (list == NULL || data == NULL)
		return FAILURE;

	if (cu_arraylist_resize(list, index + 1) == FAILURE)
		return FAILURE;

	if(index == cast(list)->itemCount)
        	cast(list)->itemCount++;
	
	memmove(cast(list)->data +(index * cast(list)->bytesPerItem), data, cast(list)->bytesPerItem);


	return SUCCESS;
}

Status cu_arraylist_prepend(CUArrayList list, const byte* data) {
	return cu_arraylist_insertAt(list, data, 0);
}


Status cu_arraylist_append(CUArrayList list, const byte* data) {
	return cu_arraylist_set(list, data, cu_arraylist_length(list));
}

int al_search(CUArrayList l, const byte* data) {
	if (l == NULL || data == NULL)
		return -2;

	ARRAYLIST *list = cast(l);

	Boolean found;

	for (int i = 0; i < list->itemCount; i++) {
		found = TRUE;
		for (int j = 0; j < list->bytesPerItem; j++) {
			if (list->data[(i * list->bytesPerItem) + j] != data[j]) {
				found = FALSE;
				break;
			}
		}
		if (found == TRUE)
			return i;
	}


	return -1;
}


Status cu_arraylist_insertAt(CUArrayList l, const byte *data, unsigned int index) {
	if (l == NULL || data == NULL)
		return FAILURE;

	ARRAYLIST *list = cast(l);

	if (index >= list->itemCount) 
		return cu_arraylist_set(list, data, index);


	int signed_index = (int) index;
	for (int i = list->itemCount - 1; i >= signed_index; i--)
        	cu_arraylist_set(list, &(list->data[i * list->bytesPerItem]), i + 1);
	

	return cu_arraylist_set(l, data, index);
}



Status cu_arraylist_remove(CUArrayList l, unsigned int index) {
	if (l == NULL)
		return FAILURE;

	ARRAYLIST *list = cast(l);

	if (index >= list->itemCount) 
		return FAILURE;

	//itemCount updated for size calculation and for the operation
	list->itemCount--;
	
	size_t size = list->bytesPerItem * (list->itemCount - index);
	if(size > 0)
		//memmove is safe with overlapping memory addresses
		memmove( 
			list->data + (index + 0) * list->bytesPerItem,
		       	list->data + (index + 1) * list->bytesPerItem,
		       	size);
	

	return SUCCESS;
}


Status cu_arraylist_clear(CUArrayList list) {
	if (list == NULL)
		return FAILURE;

	cast(list)->itemCount = 0;

	return SUCCESS;
}

Boolean cu_arraylist_isEmpty(CUArrayList list) {
	if (list == NULL)
		return TRUE;

	return cast(list)->itemCount == 0 ? TRUE : FALSE;
}


int cu_arraylist_length(CUArrayList list) {
	if (list == NULL)
		return -1;

	return cast(list)->itemCount;
}


Status cu_arraylist_resize(ARRAYLIST *list, unsigned int newItemCapacity) {
	if (list->itemCapacity >= newItemCapacity)
		return SUCCESS;


    	byte *temp = realloc(list->data,
		RESIZE_MODIFIER * list->itemCapacity * list->bytesPerItem);
    	if (temp == NULL)
	    return FAILURE;

    	list->data = temp;
	list->itemCapacity *= RESIZE_MODIFIER;

	return cu_arraylist_resize(list, newItemCapacity);
}

byte* cu_arraylist_viewRaw(CUArrayList list){
	if(list == NULL)
		return NULL;
	return cast(list)->data;
}


void cu_arraylist_destroy(CUArrayList *list) {
	if (list == NULL || *list == NULL)
		return;

	free(cast((*list))->data);
	free(*list);


	*list = NULL;
	return;
}

