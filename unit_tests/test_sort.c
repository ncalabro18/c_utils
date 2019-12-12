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


Status test_sort_int(CUTests,     void(*sort_func)(int*, unsigned int));
Status test_sort_uint(CUTests,    void(*sort_func)(unsigned int*, unsigned int));
Status test_sort_char(CUTests,    void(*sort_func)(char*, unsigned int));
Status test_sort_uchar(CUTests,   void(*sort_func)(unsigned char*, unsigned int));
Status test_sort_short(CUTests,   void(*sort_func)(short*, unsigned int));
Status test_sort_ushort(CUTests,  void(*sort_func)(unsigned short*, unsigned int));
Status test_sort_long(CUTests,    void(*sort_func)(long*, unsigned int));
Status test_sort_ulong(CUTests,   void(*sort_func)(unsigned long));
Status test_sort_float(CUTests,   void(*sort_func)(float*, unsigned int));
Status test_sort_double(CUTests,  void(*sort_func)(double*, unsigned int));
Status test_sort_ldouble(CUTests, void(*sort_func)(long double*, unsigned int));


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

#define TEST_SORT_CODE(type, t, sortfunc, arrayfunc)\
	unsigned int arrayCount = 400;\
	type *array = arrayfunc(arrayCount);\
	if(array == NULL) {\
		cu_tests_log_cstr(t, "test function failure :" #arrayfunc);\
		return FAILURE;\
	}\
	srand(time(0))\
	for(unsigned int i = 0; i < 20; i++){\
		for(unsigned int j = 0; j < arrayCount; j++)\
			array[j] = rand();\
		sortfunc(array, arrayCount);\
		for(unsigned int j = 1; j < arrayCount; j++)\
			if(array[j - 1] > array[j]){\
				cu_tests_log_cstr(t, "random array not sorted after function call:");\
				cu_tests_log_cstr(t, #sortfunc);\
			}\
	}\
	free(array);\
	return SUCCESS;


Status test_sort_int(CUTests t, void(*sort_func)(int*, unsigned int)){
	TEST_SORT_CODE(int, t, sort_func)
}
Status test_sort_uint(CUTests t, void(*sort_func)(unsigned int*, unsigned int)){
	TEST_SORT_CODE(unsigned int, t, sort_func)
}
Status test_sort_char(CUTests t, void(*sort_func)(char*, unsigned int)){
	TEST_SORT_CODE(char, t, sort_func)
}
Status test_sort_uchar(CUTests t, void(*sort_func)(unsigned char*, unsigned int)){
	TEST_SORT_CODE(unsigned char, t, sort_func)
}
Status test_sort_short(CUTests t, void(*sort_func)(short*, unsigned int)){
	TEST_SORT_CODE(short, t, sort_func)
}
Status test_sort_ushort(CUTests t, void(*sort_func)(unsigned short*, unsigned int)){
	TEST_SORT_CODE(unsigned short, t, sort_func)
}
Status test_sort_long(CUTests t, void(*sort_func)(long*, unsigned int)){
	TEST_SORT_CODE(long, t, sort_func)
}
Status test_sort_ulong(CUTests t, void(*sort_func)(unsigned long)){
	TEST_SORT_CODE(unsigned long, t, sort_func)
}
Status test_sort_float(CUTests t, void(*sort_func)(float*, unsigned int)){
	TEST_SORT_CODE(float, t, sort_func)
}
Status test_sort_double(CUTests t, void(*sort_func)(double*, unsigned int)){
	TEST_SORT_CODE(double, t, sort_func)
}
Status test_sort_ldouble(CUTests t, void(*sort_func)(long double*, unsigned int)){
	TEST_SORT_CODE(long double, t, sort_func)
}


int* cumake_randomArray_int(unsigned int arrayCount){
	if(arrayCount == 0) return NULL;

	int* array = (int*) malloc(sizeof(int) * arrayCount);
	if(!array) return NULL;

	srand(time(0));
	for(int i = 0; i < arrayCount; i++)
		array[i] = rand();


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

