#include "arraylist.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define cast(x) ((ARRAYLIST*)x)

typedef struct arraylist {
	unsigned int bytesPerItem;
	unsigned int itemCount;
	unsigned int itemCapacity;
	byte *data;
} ARRAYLIST;

#define RESIZE_MODIFIER 2
Status al_resize(ARRAYLIST *list, unsigned int newItemCapacity);

ArrayList al_initialize(unsigned int bytesPerItem, unsigned int initialItemCapacity) {
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

	return (ArrayList) list;
}


byte* al_get(ArrayList list, unsigned int index) {
	if (list == NULL)
		return NULL;
	
	return &(cast(list)->data[ index * cast(list)->bytesPerItem ]);
}

Status al_set(ArrayList list, const byte *data, unsigned int index) {
	if (list == NULL || data == NULL)
		return FAILURE;

	if (al_resize(list, index + 1) == FAILURE)
		return FAILURE;

	if(index == cast(list)->itemCount)
        	cast(list)->itemCount++;
	
	memmove(cast(list)->data +(index * cast(list)->bytesPerItem), data, cast(list)->bytesPerItem);


	return SUCCESS;
}

Status al_prepend(ArrayList list, const byte* data) {
	return al_insertAt(list, data, 0);
}


Status al_append(ArrayList list, const byte* data) {
	return al_set(list, data, al_size(list));
}

int al_search(ArrayList l, const byte* data) {
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


Status al_insertAt(ArrayList l, const byte *data, unsigned int index) {
	if (l == NULL || data == NULL)
		return FAILURE;

	ARRAYLIST *list = cast(l);

	if (index >= list->itemCount) 
		return al_set(l, data, index);



	int signed_index = (int) index;

	for (int i = list->itemCount - 1; i >= signed_index; i--) 
		al_set(list, &(list->data[i * list->bytesPerItem]), i + 1);
	


	return al_set(list, data, index);
}



Status al_remove(ArrayList l, unsigned int index) {
	if (l == NULL)
		return FAILURE;

	ARRAYLIST *list = cast(l);

	if (index >= list->itemCount) 
		return FAILURE;
	

	for (int i = index + 1; i < list->itemCount; i++) 
		for (int j = 0; j < list->bytesPerItem; j++) 
			list->data[((i - 1) * list->bytesPerItem) + j] = list->data[(i * list->bytesPerItem) + j];
	

	list->itemCount--;

	return SUCCESS;
}


Status al_clear(ArrayList list) {
	if (list == NULL)
		return FAILURE;

	cast(list)->itemCount = 0;

	return SUCCESS;
}

Boolean al_isEmpty(ArrayList list) {
	if (list == NULL)
		return TRUE;

	return cast(list)->itemCount == 0 ? TRUE : FALSE;
}


int al_size(ArrayList list) {
	if (list == NULL)
		return -1;

	return cast(list)->itemCount;
}


Status al_resize(ARRAYLIST *list, unsigned int newItemCapacity) {
	if (list->itemCapacity >= newItemCapacity)
		return SUCCESS;


    byte *temp = realloc(list->data,
            RESIZE_MODIFIER * list->itemCapacity * list->bytesPerItem);
    if (temp == NULL)
	    return FAILURE;

    list->data = temp;
	list->itemCapacity *= RESIZE_MODIFIER;

	return al_resize(list, newItemCapacity);
}

byte* al_viewRaw(ArrayList list){
	if(list == NULL)
		return NULL;
	return cast(list)->data;
}


void al_destroy(ArrayList *list) {
	if (list == NULL || *list == NULL)
		return;

	free(cast((*list))->data);
	free(*list);


	*list = NULL;
	return;
}
