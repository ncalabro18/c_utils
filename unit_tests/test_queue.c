#include "structures/cu_queue.h"
#include "cu_tests.h"


Status testfunc_queue(char *, unsigned int);

int main(void){

	CUTests unit = cu_tests_init();

    cu_tests_addTest(unit, testfunc_queue);

    cu_tests_test(unit);

    cu_tests_destroy(&unit);
	

	return 0;
}

Status testfunc_queue(char *buffer, unsigned int length){
	CUQueue q = cu_queue_initialize(sizeof(int));
	if(!q) return FAILURE;

	
	int* randArray = cumake_randomArray_int(100, 64);
	if(!randArray) return FAILURE;

	for(int i = 0; i < 100; i++)
        cu_queue_push(q, (byte *) &randArray[i]);


	for(int i = 0; i < 100; i++){
		int *num = (int*) cu_queue_peek(q);
		if(!num) return FAILURE;
		if(*num != (randArray[100 - i - 1])) return FAILURE;
	}


    cu_queue_destroy(&q);


	return SUCCESS;
}
