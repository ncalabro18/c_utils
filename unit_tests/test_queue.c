#include "structures/cu_queue.h"
#include "cu_tests.h"


Status testfunc_queue1(CUTests);

int main(void){

	CUTests unit = cu_tests_init();

	cu_tests_addTest(unit, testfunc_queue1);
	
	cu_tests_test(unit);

	cu_tests_destroy(&unit);
	

	return 0;
}

Status testfunc_queue1(CUTests t){
	CUQueue q = cu_queue_initialize(sizeof(int));
	if(!q) return FAILURE;

	
	int randArray[] = {10, -2, 6, 12, 7, 3, 9, -124, 702, 187, -89531, 10242, 3525, 57362, -26235, -236236, 931, 92, -53, 7, 72, 55, -3,  79, -4, 96, 65, -41, -83, 2, 1, -3, 12, -55, 1241, -66};
	unsigned int randArraySize = sizeof(randArray) / sizeof(int);

	for(int i = 0; i < randArraySize; i++)
        	cu_queue_push(q, (byte *) &randArray[i]);


	for(int i = 0; i < randArraySize; i++){
		int *num = (int*) cu_queue_peek(q);
		if(!num) return FAILURE;
		if(*num != randArray[i]){

			cu_tests_log_cstr(t, "testfunc_queue1: wrong val");
			cu_tests_log_newline(t);

			cu_tests_log_cstr(t, "Got: ");
			cu_tests_log_int(t, *num);
			cu_tests_log_newline(t);

			cu_tests_log_cstr(t, "Expected: ");
			cu_tests_log_int(t, randArray[i]);

		       	return FAILURE;
		}
		if(cu_queue_pop(q) == FAILURE){
			cu_tests_log_cstr(t, "cu_testfunc_queue1: cu_queue_pop FAILURE");
			return FAILURE;
		}
	}

	cu_queue_destroy(&q);

	return SUCCESS;
}
