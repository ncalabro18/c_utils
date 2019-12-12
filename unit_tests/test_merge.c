#include "cu_utils.h"
#include "cu_tests.h"


Status testfunc_merge1(CUTests);

int main(void){

	CUTests t = cu_tests_init();

	cu_tests_addTest(t, testfunc_merge1);

	cu_tests_test(t);

	cu_tests_destroy(&t);

	return 0;
}


Status testfunc_merge1(CUTests t){
	if(!t) return FAILURE;

	int array[] = {10, -19251, 1,1,1,1,1,1,241121,1,1,1,1,1,1,3211,1111,17,21,-61,1,114,-615,1111111,15,21,-1,1,11111,11,1,1,124373, -2369, -646, 986, 75, -456, 86, -42157, 24396, 2496, 735739, 923857, 91298, 98, -9128, -24};
	unsigned int arrayCount = sizeof(array) / sizeof(int);

	cusort_merge_int(array, arrayCount);
	

	for(unsigned int i = 1; i < arrayCount; i++)
		if(array[i - 1] > array[i]){
			cu_tests_log_cstr(t, "testfunc_merge1: wrong value");
			return FAILURE;
		}	
	

	return SUCCESS;
}
