#include "cu_tests.h"
#include "structures/cu_stack.h"


Status testfunc_stack1(CUTests);

int main(){

	CUTests tests = cu_tests_init();

	cu_tests_addTest(tests, testfunc_stack1);

	cu_tests_test(tests);

	cu_tests_destroy(&tests);

	return 0;
}

Status testfunc_stack1(CUTests t){
	
	int array[] = {10, -2, 6, 12, 7, 7, 72, 55, -3, -4, 96, -41, -83};
	unsigned int arrayCount = sizeof(array) / sizeof(int);

	CUStack stack =  cu_stack_init(sizeof(int), 25);

	for(unsigned int i = 0; i < arrayCount; i++){
		if(cu_stack_push(stack, (byte*) &array[i]) == FAILURE){
			cu_tests_log(t, "stack1: cu_stack_push FAILURE");
			return FAILURE;
		}
	}

	for(unsigned int i = 0; i < arrayCount; i++){
		int *temp = (int*) cu_stack_peek(stack);
		if(temp == NULL){
			cu_tests_log(t, "stack1: cu_stack_peek NULL");
		       	return FAILURE;
		}
		if(*temp != array[arrayCount - i - 1]){
			cu_tests_log(t, "stack1: *temp != array[i]");
			return FAILURE;
		}
		if(cu_stack_pop(stack) == FAILURE){
			cu_tests_log(t, "stack1: cu_stack_pop FAILURE");
			return FAILURE;
		}
	}

	cu_stack_destroy(&stack);

	return SUCCESS;
}
	
