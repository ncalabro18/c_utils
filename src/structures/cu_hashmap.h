#ifndef CU_HASHMAP_H
#define CU_HASHMAP_H

#include <stdio.h>
#include "../util.h"

typedef void* CUHashMap;
//user defined function to indicate the "index" to be hased; works the same way as the Java implementaion
//passed the pointer to the key; this function is meant to return a unique integer identifier to that key
typedef int (*HashCode)(byte*);

//creates an empty hashmap structure
//capacity: number of chains to store
//keyItemLength: sizeof(<key>)
//valueItemLength: sizeof(<value>)
//HashCode: function which returns a consistent value based on the key
//function takes a byte* as param, the key, and returns an int, the code
CUHashMap cu_hashmap_init(unsigned int capacity, unsigned int keyItemLength, unsigned int valueItemLength, HashCode function);

//adds the key/value pair to the hashmap
Status cu_hashmap_push(CUHashMap, byte* key, byte* val);
//pops the specified key from the hashmap
Status cu_hashmap_pop (CUHashMap, byte* key);
//views the value at the specified key
//NULL on failure or no value found
byte*  cu_hashmap_peek(CUHashMap, byte* key);

//returns the total number of PAIRs stored in the hashmap
int cu_hashmap_length(CUHashMap);

//returns if the key is found in the hashmap
Boolean cu_hashmap_contains(CUHashMap, byte *key);

//loadfactor indicates when resizing should occur; 
//a loadfactor of 0.75f (default) will resize when a pair exists at 3/4s of the entrees.
Status cu_hashmap_loadfactor(CUHashMap, float);

//clears all the elements in the hashmap; does not deallocate any memory
Status cu_hashmap_clear(CUHashMap);

//prints the hashmap, pretty useless for anythihg except debugging & viewing how evenly spaced the pairs are
Status cu_hashmap_print(CUHashMap, FILE*);

//deallocates all memory from the hashmap, opaque object is no longer valid and is set to NULL
void cu_hashmap_destroy(CUHashMap*);


#endif

