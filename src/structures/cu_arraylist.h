#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "../util.h"


typedef void* CUArrayList;

//function to create a handle to an CUArrayList object
CUArrayList cu_arraylist_init(unsigned int bytesPer, unsigned int initialMaxAmount);

//returns the address of the data stored at the index, returns NULL if out of bounds or on failure
byte* cu_arraylist_get(CUArrayList list, unsigned int index);

//sets the data at the index to the memory data points to, overwriting it
Status cu_arraylist_set(CUArrayList list, const byte *data, unsigned int index);

//adds data to the beginning of the list
//NOTE this requires all data to be shifted in the array, O(n) runtime
Status cu_arraylist_prepend(CUArrayList list, const  byte* data);

//appends the given data to the end of the array
Status cu_arraylist_append(CUArrayList list, const byte* data);

//finds index of the given data, returns -1 if not found
int cu_arraylist_search(CUArrayList list, const byte* data);

//inserts the data at the given index, NOT overwriting the data, rather pushing data forward
Status cu_arraylist_insertAt(CUArrayList list, const byte *data, unsigned int index);

//removes the data from the CUArrayList
//will shift all data left of the index to fill its position
Status cu_arraylist_remove(CUArrayList list, unsigned int index);

//clears all elements from the CUArrayList. but does not deallocate the object or the data it stores
Status cu_arraylist_clear(CUArrayList list);

//returns TRUE if the CUArrayList is empty
Boolean cu_arraylist_isEmpty(CUArrayList list);

//returns the length of the CUArrayList
int cu_arraylist_length(CUArrayList list);

//returns the address of the block of data which holds all the elements
//returning type should be a pointer to the stored type
byte* cu_arraylist_viewRaw(CUArrayList list);

//frees all data from memory associated with the CUArrayList
//NOTE pass the address of the handle, not the handle itself
void cu_arraylist_destroy(CUArrayList *list);

#endif 
