#include "structures/cu_heap.h"
#include "cu_tests.h"

Status testfunc_heap1(CUTests);
Status testfunc_heap2(CUTests);

int main(void){

	CUTests t = cu_tests_init();

	cu_tests_addTest(t, testfunc_heap1);
	cu_tests_addTest(t, testfunc_heap2);

	cu_tests_test(t);

	cu_tests_destroy(&t);

	return 0;
}

Status testfunc_heap1(CUTests t){

	int array[] = {-12984,81264, 17,89326, -1284, 98352, -8325, -32523, 67150, 856,10,-10,735,4087,745, 
		-124, 84353, 462,-25325,500932 -821, -39521, 38732, -912601, -7766501, -9583, 0xbce71, 85783, -86782, 10, -3901, -997219, 98};

	unsigned int arrayCount = sizeof(array) / sizeof(int);
	CUHeap h = cu_heap_init(sizeof(int), 2, cu_heap_cmpfunc_MIN_INT);
	if(h == NULL){
		cu_tests_log_cstr(t, "testfunc_heap1: cu_heap_init NULL");
		return FAILURE;
	}

	for(unsigned int i = 0 ; i < arrayCount; i++)
		if(cu_heap_push(h,(byte*) &array[i]) == FAILURE){
			cu_tests_log_cstr(t, "testfunc_heap11: cu_heap_push FAILURE");
			return FAILURE;
		}

	int *last = (int*) cu_heap_peek(h);
	if(last == NULL){
		cu_tests_log_cstr(t, "testfunc_heap1: cu_heap_peek NULL");
		return FAILURE;
	}
	if(cu_heap_pop(h) == FAILURE){
		cu_tests_log_cstr(t, "testfunc_heap1: cu_heap_pop FAILURE");
		return FAILURE;
	}

	for(unsigned int i = 0; i < arrayCount - 1; i++){
		int *cur = (int*) cu_heap_peek(h);
		if(cur == NULL){
			cu_tests_log_cstr(t, "testfunc_heap1: cu_heap_peek NULL");
			return FAILURE;
		}
		if(cu_heap_pop(h) == FAILURE){
			cu_tests_log_cstr(t, "testfunc_heap1: cu_heap_pop FAILURE");
			return FAILURE;
		}
		if(*cur < *last){
			cu_tests_log_cstr(t, "*cur < last");
			return FAILURE;
		}
	}
	
	cu_heap_destroy(&h);
	return SUCCESS;
}

Status testfunc_heap2(CUTests t){
	

	int array[] = {-12984,81264, 17,89326, -1284, 98352, -8325, -32523, 67150, 856,10,-10,735,4087,745, -68,215,4643,30875,-2385,97325,-23582,
		-124, 84353, 462,-25325,500932 -821, -39521, 38732, -912601, -7766501, -9583, 0xbce71, 8573, 656, -86782, 10, -3901, -997219, 98};

	unsigned int arrayCount = sizeof(array) / sizeof(int);
	CUHeap h = cu_heap_init(sizeof(int), 2, cu_heap_cmpfunc_MIN_INT);
	if(h == NULL){
		cu_tests_log_cstr(t, "testfunc_heap2: cu_heap_init NULL");
		return FAILURE;
	}

	if(cu_heap_buildHeap(h, (byte*) array, arrayCount) == FAILURE){
		cu_tests_log_cstr(t, "testfunc_heap2: cu_heap_buildHeap FAILURE");
		return FAILURE;
	}

	int *last = (int*) cu_heap_peek(h);
	if(last == NULL){
		cu_tests_log_cstr(t, "testfunc_heap2: 1st cu_heap_peek NULL");
		return FAILURE;
	}
	if(cu_heap_pop(h) == FAILURE){
		cu_tests_log_cstr(t, "testfunc_heap2: cu_heap_pop FAILURE");
		return FAILURE;
	}

	for(unsigned int i = 0; i < arrayCount - 1; i++){
		int *cur = (int*) cu_heap_peek(h);
		if(cur == NULL){
			cu_tests_log_cstr(t, "testfunc_heap2: cu_heap_peek NULL");
			return FAILURE;
		}
		if(cu_heap_pop(h) == FAILURE){
			cu_tests_log_cstr(t, "testfunc_heap2: cu_heap_pop FAILURE");
			return FAILURE;
		}
		if(*cur < *last){
			cu_tests_log_cstr(t, "*testfunc_heap2L cur < last");
			return FAILURE;
		}
	}
	
	cu_heap_destroy(&h);
	return SUCCESS;
}

