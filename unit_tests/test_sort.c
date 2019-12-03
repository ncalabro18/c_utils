#include "cu_utils.h"
#include "cu_tests.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



//returns status determining whether or not the given function sorts arrays
Status test_sort(void(*)(int*, unsigned int), char*, unsigned int);
//runs merge sort on array and tests if its sorted
Status testfunc_merge(char *buffer, unsigned int length);
Status testfunc_bubble(char *buffer, unsigned int length);
Status testfunc_selection(char *buffer, unsigned int length);


int main(){

	CUTests ut = cu_tests_init();
	if(!ut)
		return -1;

    	cu_tests_addTest(ut, testfunc_selection);
    	cu_tests_addTest(ut, testfunc_bubble);
	//ut_addTest(ut, testfunc_merge);
    	cu_tests_test(ut);

    	cu_tests_destroy(&ut);
	return 0;
}

Status testfunc_selection(char *buffer, unsigned int length){
	if(test_sort(cusort_selection_int, buffer, length) == FAILURE) return FAILURE;

	return SUCCESS;
}

Status testfunc_bubble(char *buffer, unsigned int length){
	return test_sort(cusort_bubble_int, buffer, length);
}

Status testfunc_merge(char *buffer, unsigned int length){
	return test_sort(cusort_merge_int, buffer, length);
}


Status test_sort(void(*sort_func)(int*, unsigned int), char *buffer, unsigned int length){
	int *array = (int*) malloc(sizeof(int) * 400);
	if(!array)
		return FAILURE;

	srand(time(0));
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 400; j++)
			array[j] = rand();

		sort_func(array, 400);
		
		int last = array[0];
		for(int i = 1; i < 400; i++){
			if(last > array[i]) {
				strcpy(buffer, "test_sort: array is not sorted\n");	
				return FAILURE;
			}
		}
	}
	free(array);
	return SUCCESS;
}

int* cumake_randomArray_int(unsigned int arrayCount){
	if(arrayCount == 0) return NULL;

	int* array = (int*) malloc(sizeof(int) * arrayCount);
	if(!array) return NULL;

	srand(time(0));
	for(int i = 0; i < arrayCount; i++)
		array[i] = rand() ;

	return array;
}

unsigned int* cumake_randomArray_uint(unsigned int arrayCount, unsigned int max){
	if(arrayCount == 0) return NULL;

	unsigned int *array = malloc(sizeof(unsigned int) * arrayCount);
	if(!array) return NULL;

	srand(time(0));
	for(int i = 0; i < arrayCount; i++)
		array[i] = (unsigned int) rand() % max;

	return array;
}

float* cumake_randomArray_float(unsigned int arrayCount, float max){
	if(arrayCount == 0) return NULL;

	float *array = malloc(sizeof(float) * arrayCount);
	if(!array) return NULL;

	srand(time(0));
	for(int i = 0; i < arrayCount; i++)
		array[i] = max * (float) (rand() / RAND_MAX);

	return array;
}

