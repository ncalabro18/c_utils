#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "../util.h"

typedef void* ArrayList;

//function to create a handle to an ArrayList object
ArrayList al_initialize(unsigned int bytesPer, unsigned int initialMaxAmount);

//returns the address of the data stored at the index, returns NULL if out of bounds or on failure
byte* al_get(ArrayList list, unsigned int index);

//sets the data at the index to the memory data points to, overwriting it
Status al_set(ArrayList list, const byte *data, unsigned int index);

//adds data to the beginning of the list
//NOTE this requires all data to be shifted in the array
Status al_prepend(ArrayList list, const  byte* data);

//appends the given data to the end of the array
Status al_append(ArrayList list, const byte* data);

//finds index of the given data, returns -1 if not found
int al_search(ArrayList list, const byte* data);

//inserts the data at the given index, NOT overwriting the data, rather pushing data forward
Status al_insertAt(ArrayList list, const byte *data, unsigned int index);


//removes the given data from the ArrayList
//will shift all data left to fill its position
Status al_remove(ArrayList list, unsigned int index);

//clears all elements from the ArrayList. but does not deallocate the object or the data it stores
Status al_clear(ArrayList list);

//returns TRUE if the ArrayList is empty
Boolean al_isEmpty(ArrayList list);

//returns the length of the ArrayList
int al_size(ArrayList list);

//returns the address of the block of data which holds all the elements
//returning type should be a pointer to the stored type
byte* al_viewRaw(ArrayList list);

//frees all data from memory associated with the ArrayList
//NOTE pass the address of the handle, not the handle itself
void al_destroy(ArrayList *list);

#endif 
