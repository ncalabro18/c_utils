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

	UnitTests ut = ut_init();
	if(!ut)
		return -1;

	ut_addTest(ut, testfunc_selection);
	ut_addTest(ut, testfunc_bubble);
	ut_addTest(ut, testfunc_merge);
	ut_test(ut);

	ut_destroy(&ut);
	return 0;
}

Status testfunc_selection(char *buffer, unsigned int length){
	return test_sort(cusort_selection_int, buffer, length);
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

