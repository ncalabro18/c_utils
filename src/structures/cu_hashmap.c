#include "cu_hashmap.h"
#include <stdlib.h>
#include <string.h>

#define HASHMAP_RESIZE_FACTOR 2
#define cast(x) ((struct CU_HASHMAP*)(x))


struct link;
struct CU_HASHMAP{
	struct link **data;

	int length;//total number of pairs
	int filledPositions;//number of non-NULL link heads
	int capacity;

	int c_key;//bytes needed for each key and value
	int c_val;

	float loadFactor;

	HashCode  hashcodeFunc;
};

struct link{
	byte *key;
	byte *val;
	int  code;

	struct link *next;
};


struct link* makeLink(byte*, byte*, unsigned int, unsigned int, int code);

int cu_hashmap_hashfunction(struct CU_HASHMAP*, int);

CUHashMap cu_hashmap_init(unsigned int capacity, unsigned int keyItemLength, unsigned int valueItemLength, HashCode function){
	struct CU_HASHMAP *map = (struct CU_HASHMAP*) malloc(sizeof(struct CU_HASHMAP));
	if(map == NULL)
		return FAILURE;

	map->data = (struct link**) calloc(sizeof(struct link*), capacity);
	if(map->data == NULL){
		free(map);
		return FAILURE;
	}
	
	map->length = 0;
	map->filledPositions = 0;
	map->loadFactor = 0.75f;

	map->capacity = capacity;
	map->c_key = keyItemLength;
	map->c_val = valueItemLength;

	map->hashcodeFunc = function;

	return map;
}


Status cu_hashmap_push(CUHashMap m, byte* key, byte* val){
	if(m == NULL)
		return FAILURE;
	struct CU_HASHMAP *map = cast(m);
	int code = map->hashcodeFunc(key);
	int pos = cu_hashmap_hashfunction(map, code);
	struct link *l = makeLink(key, val, map->c_key, map->c_val, code);
	if(l == NULL)
		return FAILURE;

	
	if(map->data[pos] == NULL){
		map->data[pos] = l;
		map->filledPositions++;	
		//check resize//
		if((((float)map->filledPositions) / ((float)map->capacity)) > map->loadFactor){
			struct link **old_data = map->data;
			map->data = (struct link**) calloc(sizeof(struct link*),  map->capacity * HASHMAP_RESIZE_FACTOR);
			if(map->data == NULL){
				map->data = old_data;
				return FAILURE;
			}
			int old_capacity = map->capacity;
			map->capacity *= HASHMAP_RESIZE_FACTOR;
			//must recalculate filed positions
			map->filledPositions = 0;
			
			//O(n) resize runtime
			for(int i = 0; i < old_capacity; i++){
				struct link *current = old_data[i];
				while(current != NULL){
					//uses the ca
					int new_pos = cu_hashmap_hashfunction(map, current->code);
					struct link *temp = current->next;

					if(map->data[new_pos] == NULL)
						map->filledPositions++;

					current->next = map->data[new_pos];//for non-collisions, will just reasign to NULL
					map->data[new_pos] = current;

					current = temp;
				}
			}
			free(old_data);
		}
	}else{
		//collision, chain it to beginning
		l->next = map->data[pos];
		map->data[pos] = l;
	}
	
	map->length++;
	return SUCCESS;
}


Status cu_hashmap_pop(CUHashMap m, byte* key){
	if(m == NULL || key == NULL)
		return FAILURE;
	struct CU_HASHMAP *map = cast(m);
	int code = map->hashcodeFunc(key);
	int pos = cu_hashmap_hashfunction(map, code);

	struct link *last = map->data[pos];
	struct link *current = map->data[pos];
	while(current != NULL){
		if(memcmp(current->key, key, map->c_key) == 0){
			last->next = current->next;
			map->length--;
			if(last == current){
				map->data[pos] = NULL;
				map->filledPositions--;
			}
			free(current);
		}
		last = current;
		current = current->next;
	}

	return FAILURE;
}


byte*  cu_hashmap_peek(CUHashMap m, byte* key){
	if(m == NULL || key == NULL)
		return NULL;
	struct CU_HASHMAP *map = cast(m);
	int code = map->hashcodeFunc(key);
	int pos = cu_hashmap_hashfunction(map, code);
	struct link *current = map->data[pos];

	while(current != NULL)
		if(memcmp(current->key, key, map->c_key) == 0)
			return current->val;
	

	return NULL;
}


Status cu_hashmap_loadfactor(CUHashMap m, float f){
	if(m == NULL || f < 0.0f || f > 1.0f)
		return FAILURE;

	cast(m)->loadFactor = f;
	return SUCCESS;
}


int cu_hashmap_length(CUHashMap m){
	if(m == NULL)
		return -1;
	
	return cast(m)->length;
}

Boolean cu_hashmap_contains(CUHashMap m, byte *key){
	struct CU_HASHMAP *map = cast(m);
	int code = map->hashcodeFunc(key);
	int pos = cu_hashmap_hashfunction(map, code);
	
	struct link *current = map->data[pos];
	while(current != NULL){
		if(memcmp(current->key, key, map->c_key) == 0)
			return TRUE;
		current = current->next;		
	}
	return FALSE;
}


Status cu_hashmap_clear(CUHashMap m){
	if(m == NULL)
		return FAILURE;
	struct CU_HASHMAP *map = cast(m);
	for(int i = 0; i < map->capacity; i++)
		while(map->data[i] != NULL){
			struct link *current = map->data[i];
			map->data[i] = current->next;
			free(current);	
		}
	
	return SUCCESS;
}

Status cu_hashmap_print(CUHashMap m, FILE* file){
	if(m == NULL || file == NULL)
		return FAILURE;
	struct CU_HASHMAP *map = cast(m);
	
	for(int i = 0; i < map->capacity; i++){
		struct link *current = map->data[i];
		if(current == NULL){
			fprintf(file, "[___]");
		}
		while(current != NULL){
			fprintf(file, "[_%p_]->[_%p_]", current->key, current->val);
			if(current->next != NULL)
				fprintf(file, " | ");
			current = current->next;
		}
		fprintf(file, "\n");
	}

	return SUCCESS;
}

void cu_hashmap_destroy(CUHashMap* map){
	if(cu_hashmap_clear(*map) == FAILURE) 
		return;

	free(cast(*map)->data);
	free(*map);

	*map = NULL;
}


struct link* makeLink(byte* k, byte* v, unsigned int ck, unsigned int cv, int code){
	//uses one malloc; creates enough space to store the key and value after the link data
	struct link *l = (struct link*) malloc(sizeof(struct link) + ck + cv);
	if(l == NULL)
		return NULL;

	memcpy(&l[1], k, ck);
	memcpy((((byte*)&l[1]) + ck), v, cv);

	l->code = code;
	l->next = NULL;
	l->key = ((byte*) &l[1]);
	l->val = ((byte*) &l[1]) + ck;//cast to avoid pointer arithmetic misinterpretation
				    //offset by capacity of k, these comments applies to the memcpy's above
	return l;	
}


int cu_hashmap_hashfunction(struct CU_HASHMAP *map, int code){
	return code % map->capacity;
}

