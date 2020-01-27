#ifndef CU_AVL_H
#define CU_AVL_H

#include "../util.h"

typedef void* CUAVLTree;


//initializes an empty avl tree data stucture
//the function callback is meant to determine the value if passed a pointer or some other data type
//pass NULL to the callback to force integer representation
//passing NULL with a dataSize < 4 will cause failure, NULL return val
CUAVLTree cu_avl_init(unsigned int dataSize, int (*valueCallBack)(byte*));

//pushes the data on the avl tree, 
Status cu_avl_push(CUAVLTree, byte *data);

//removes the data from the avl tree
//pass NULL to remove the root node
Status cu_avl_pop(CUAVLTree, byte *data);

//returns a pointer to the data at the root of the avl tree
byte* cu_avl_peek(CUAVLTree);

//returns boolean value whether or not the avl tree contains the data
Boolean cu_avl_contains(CUAVLTree, byte*);

Status cu_avl_clear(CUAVLTree);

//deallocates all memory associated with the avl tree
void cu_val_destroy(CUAVLTree*);

#endif


