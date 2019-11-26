#include "../c_utils.h"
#include "../unit_tests/unit_tests.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//test function if merge sort actually...sorts
Status testArray(int *array, int count, char*, unsigned int);
//runs merge sort on array and tests if its sorted
Status testfunc_merge(char *buffer, unsigned int length);
Status testfunc_buble(char *buffer, unsigned int length);
Status testfunc_selection(char *buffer, unsigned int length);


int main(){

	UnitTests ut = ut_init();
	if(!ut)
		return -1;

	ut_addTest(ut, testfunc_selection);
	ut_addTest(ut, testfunc_bubble);
	//ut_addTest(ut, testfunc_merge);
	ut_test(ut);

	ut_destroy(&ut);
	return 0;
}

Status testfunc_selection(char *buffer, unsigned int length){
	return test_sort(cusort_selection_it, buffer, length);
}

Status testfunc_bubble(char *buffer, unsigned int length){
	return test_sort(cusort_bubble_int, buffer, length);
}

Status testfunc_merge(char *buffer, unsigned int length){
	return test_sort(cusort_merge_int, buffer, length);
}


Status test_sort(Status(*sort_func)(int*, unsigned int), char *buffer, unsigned int length){
	int *array = (int*) malloc(sizeof(int) * 400);

	srand(time(0));
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 400; j++)
			array[j] = rand();

		if(sort_func(array, 400) == FAILURE){
			if(count <= 0){
				strncpy("testfunc_merge: array count <= 0... error in test func?\n", buffer, length);
				return FAILURE;
			}
			int last = array[0];
			for(int i = 1; i < count; i++){
				if(last > array[i]) {
					strncpy("testfunc_merge: array is not sorted\n", buffer, length);	
					return FAILURE;
				}
			}
		}
	}
	return SUCCESS;
}

