#include "cu_avl.h"

#include <stdlib.h>
#include <string.h>

#define cast(x) ((struct CU_AVL_TREE*)(x))


struct Node* avl_makeNode(byte *data, unsigned int dataSize);
struct Node* avl_rotateLeft(struct Node *head, unsigned int dataSize);
struct Node* avl_rotateRight(struct Node *head, unsigned int dataSize);

struct CU_AVL_TREE{
	int (*valueCallBack)(byte*);
	unsigned int ize;

	struct Node *root;
};

struct Node{
	byte* data;
	struct Node *left;
	struct Node *right;
};

CUAVLTree cu_avl_init(unsigned int dataSize, int (*valueCallBack)(byte*)){
	if(dataSize < 4 && valueCallBack == NULL)
		return NULL;

	struct CU_AVL_TREE *avl = (struct CU_AVL_TREE*) malloc(sizeof(struct CU_AVL_TREE));
	if(avl == NULL)
		return NULL;
	if(dataSize < 4 && valueCallBack == NULL)
		return NULL;
	
	avl->dataSize = dataSize;


	return (CUAVLTree) avl;
}

Status cu_avl_push(CUAVLTree t, byte *data){
	if(t == NULL || data == NULL)
		return FAILURE;
	struct CU_AVL_TREE *avl = cast(t);

	int value;
	if(avl->valueCallBack != NULL)
		value = avl->valueCallBack(data, avl->dataSize);
	else
		value = *(int*) data;
	

	//insert the Node into the tree
	struct Node *newNode = avl_makeNode(data, avl->dataSize);
	struct Node *current = avl->root;
	if(current = NULL){
		avl->root = newNode;
		return SUCCESS;
	}
	while(current->next != NULL){
		
	}

	return SUCCESS;
}

Status cu_avl_pop(CUAVLTree t, byte *data){
	
	
}

byte* cu_avl_peek(CUAVLTree);

Boolean cu_avl_contains(CUAVLTree, byte*);

Status cu_avl_clear(CUAVLTree);

void cu_val_destroy(CUAVLTree* tptr){

}


struct Node* avl_makeNode(byte *data, unsigned int dataSize){
	struct Node *n = (struct Node*) malloc(sizeof(struct Node*) + dataSize);

	n->left  = NULL;
	n->right = NULL;
	n->data  = (byte*) n[1];
	memcpy(n->data, data, dataSize);

	return n;
}

struct Node* avl_rotateLeft(struct Node *head, unsigned int dataSize){
	
}

struct Node* avl_rotateRight(struct Node *head, unsigned int dataSize){

}

