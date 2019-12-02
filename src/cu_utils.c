#include "cu_utils.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//macros to reuse code for different types (who needs templates)
//may  move them to above their respective functions
#define CUSWAP_CODE(type, a, b)\
	{type _temp = *a;\
	*a = *b;\
	*b = _temp;}

#define CUSEARCH_LINEAR_CODE(array, arrayCount, number)\
	{unsigned int i;\
	if(!(array)) return -2;\
	for(i = 0; i < (arrayCount); i++)\
		if(array[i] == (number))\
			return i;\
	return -1;}

#define CUSEARCH_BINARY_CODE(type, array, arrayCount, number){\
	unsigned int left = 0, right = (arrayCount);\
	do{\
		unsigned int count = left - right;\
		unsigned int mid = (count > 1) + left;\
		if((number) == array[mid])\
			return mid;\
		else{\
			if((number) < array[mid]){\
				right = mid;\
			}else\
				left = mid;\
		}\
	}while(left < right);\
	return -1;}


#define CUSORT_SELECTION_CODE(type, array, arrayCount)\
	for(unsigned int i = 0; i < arrayCount - 1; i++){\
		unsigned int min = i;\
		for(int j = i; j < arrayCount; j++)\
			if(array[j] < array[min])\
				min = j;\
		CUSWAP_CODE(type, &array[min], &array[i]);\
	}


#define CUSORT_BUBBLE_CODE(type, array, arrayCount){\
	unsigned int swaps;\
	unsigned int i;\
	if(!(array)) return;\
	do{\
		swaps = 0;\
		for(i = 0; i < (arrayCount) - 1; i++){\
			if((array)[i] > (array)[i + 1]){\
				CUSWAP_CODE(type, &array[i], &array[i + 1]);\
				swaps = 1;\
			}\
		}\
	}while(swaps != 0);}


#define CUPRINT_ARRAY_CODE(type, array, arrayCount, format)\
	\
	for(int i = 0; i < arrayCount; i++)\
		if(fprintf(_cu_globals.cuprint_output, format, array[i]) != 1){\
			const char* str = "cuprint_array_" #type;\
		       	perror(str);\
		}
	
	

//this structure holds any global variables/options needed by functions
struct cu_globals{
	FILE *cuprint_output;
} _cu_globals = { .cuprint_output = NULL };
//only instance is _cu_globals



int* cumake_randomArray_int(unsigned int arrayCount, int max){
	if(arrayCount == 0) return NULL;

	int* array = (int*) malloc(sizeof(int) * arrayCount);
	if(!array) return NULL;

	srand(time(0));
	for(int i = 0; i < arrayCount; i++)
		array[i] = rand() % max;

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



int cusearch_linear_int(int *array, unsigned int arrayCount, int number){
	CUSEARCH_LINEAR_CODE(array, arrayCount, number)
}
int cusearch_linear_uint(unsigned int *array, unsigned int arrayCount, unsigned int number){
	CUSEARCH_LINEAR_CODE(array, arrayCount, number)
}
int cusearch_linear_short(short *array, unsigned int arrayCount, short number){
	CUSEARCH_LINEAR_CODE(array, arrayCount, number)
}
int cusearch_linear_ushort(unsigned short *array, unsigned int arrayCount, unsigned short number){
	CUSEARCH_LINEAR_CODE(array, arrayCount, number)
}
int cusearch_linear_long(long *array, unsigned int arrayCount, long number){
	CUSEARCH_LINEAR_CODE(array, arrayCount, number)
}
int cusearch_linear_ulong(unsigned long *array, unsigned int arrayCount, unsigned long number){
	CUSEARCH_LINEAR_CODE(array, arrayCount, number)
}
int cusearch_linear_float(float *array, unsigned int arrayCount, float number){
	CUSEARCH_LINEAR_CODE(array, arrayCount, number)
}
int cusearch_linear_double(double *array, unsigned int arrayCount, double number){
	CUSEARCH_LINEAR_CODE(array, arrayCount, number)
}
int cusearch_linear_ldouble(long double *array, unsigned int arrayCount, long double number){
	CUSEARCH_LINEAR_CODE(array, arrayCount, number)
}



int cusearch_binary_int(int *array, unsigned int arrayCount, int number){
	CUSEARCH_BINARY_CODE(int, array, arrayCount, number)
}
int cusearch_binary_uint(unsigned int *array, unsigned int arrayCount, unsigned int number){
	CUSEARCH_BINARY_CODE(unsigned  int, array, arrayCount, number)
}
int cusearch_binary_short(short *array, unsigned int arrayCount, short number){
	CUSEARCH_BINARY_CODE(short, array, arrayCount, number)
}
int cusearch_binary_ushort(unsigned short *array, unsigned int arrayCount, unsigned short number){
	CUSEARCH_BINARY_CODE(unsigned short, array, arrayCount, number)
}
int cusearch_binary_long(long *array, unsigned int arrayCount, long number){
	CUSEARCH_BINARY_CODE(long, array, arrayCount, number)
}	
int cusearch_binary_ulong(unsigned long*array, unsigned int arrayCount, unsigned long number){
	CUSEARCH_BINARY_CODE(unsigned long, array, arrayCount, number)
}
int cusearch_binary_float(float *array, unsigned int arrayCount, float number){
	CUSEARCH_BINARY_CODE(float, array, arrayCount, number)
}
int cusearch_binary_double(double*array, unsigned int arrayCount, double number){
	CUSEARCH_BINARY_CODE(double, array, arrayCount, number)
}
int cusearch_binary_ldouble(long double *array, unsigned int arrayCount, long double number){
	CUSEARCH_BINARY_CODE(long double, array, arrayCount, number)
}



void cusort_bubble_int(int *array, unsigned int arrayCount){
	 CUSORT_BUBBLE_CODE(int, array, arrayCount)	
}
void cusort_bubble_uint(unsigned int *array, unsigned int arrayCount){
	 CUSORT_BUBBLE_CODE(unsigned int, array, arrayCount)
}

void cusort_bubble_float(float *array, unsigned int arrayCount){
	 CUSORT_BUBBLE_CODE(float, array, arrayCount)
}
void cusort_selection_int(int *array, unsigned int arrayCount){
	CUSORT_SELECTION_CODE(int, array, arrayCount);
}
void cusort_selection_uint(unsigned int *array, unsigned int arrayCount){
	CUSORT_SELECTION_CODE(unsigned int, array, arrayCount);
}
void cusort_selection_float(float *array, unsigned int arrayCount){
	CUSORT_SELECTION_CODE(float, array, arrayCount)
}


//more testing on merge needed before converted to macro
void cusort_merge_int_merge(int *array, unsigned int low, unsigned int mid, unsigned int high){
	if(low + 1 < high){
		cusort_merge_int_merge(array, low, ((low + mid ) >> 1), mid);
		cusort_merge_int_merge(array, mid, ((mid + high) >> 1), high);
	}
	else 
		return;


	if(high - low == 2){
		if(array[low] > array[mid])
			cuswap_int(&array[low], &array[mid]);	
	}else{
		//allocates enough space for left array
		int *leftArray = malloc(sizeof(int) * (mid - low));
		if(!leftArray){
			perror("cusort_merge allocation fail");
		}
		memcpy(leftArray, &array[low], mid - low);
		for(unsigned int i = low; i < high; i++){
			if(leftArray[i - low] > array[mid]){
				array[i] = array[mid];
				mid++;
			}else{
				array[i] = leftArray[i - low];
				low++;
			}
		}
		free(leftArray);
	}
}
	
void cusort_merge_int(int *array, unsigned int arrayCount){
	if(!array) return;
	cusort_merge_int_merge(array, 0, arrayCount / 2, arrayCount);
}



void cuswap_int(int *a, int *b){
	CUSWAP_CODE(int,a,b)
}
void cuswap_uint(unsigned int *a, unsigned int *b){
	CUSWAP_CODE(unsigned int,a,b)
}
void cuswap_short(short *a, short *b){
	CUSWAP_CODE(short,a,b)
}
void cuswap_ushort(unsigned short *a, unsigned short *b){
	CUSWAP_CODE(unsigned short,a,b)
}
void cuswap_long(long *a, long *b){
	CUSWAP_CODE(long,a,b)
}
void cuswap_ulong(unsigned long *a, unsigned long *b){
	CUSWAP_CODE(unsigned long,a,b)
}
void cuswap_float(float *a, float *b){
	CUSWAP_CODE(float,a,b)
}
void cuswap_double(double *a, double *b){
	CUSWAP_CODE(double,a,b)
}
void cuswap_ldouble(long double *a, long double *b){
	CUSWAP_CODE(long double,a,b)
}


void cuprint_setOutput(FILE *filePtr){
	_cu_globals.cuprint_output = filePtr;
}
void cuprint_array_int(int *array, unsigned int arrayCount){	
	CUPRINT_ARRAY_CODE(int, array, arrayCount, "%d ")
}
void cuprint_array_uint(unsigned int *array, unsigned int arrayCount){
	CUPRINT_ARRAY_CODE(unsigned int, array, arrayCount, "%u ")
}
void cuprint_array_short(short *array, unsigned int arrayCount){
	CUPRINT_ARRAY_CODE(short, array, arrayCount, "%d ")
}
void cuprint_array_ushort(unsigned short *array, unsigned int arrayCount){
	CUPRINT_ARRAY_CODE(unsigned short, array, arrayCount, "%u ")
}
void cuprint_array_long(long *array, unsigned int arrayCount){
	CUPRINT_ARRAY_CODE(long, array, arrayCount, "%ld ")
}
void cuprint_array_ulong(unsigned long *array, unsigned int arrayCount){
	CUPRINT_ARRAY_CODE(unsigned long, array, arrayCount, "%lu ")
}
void cuprint_array_float(float *array, unsigned int arrayCount){
	CUPRINT_ARRAY_CODE(float , array, arrayCount, "%f ")
}
void cuprint_array_double(double *array, unsigned int arrayCount){
	CUPRINT_ARRAY_CODE(double , array, arrayCount, "%lf ")
}
void cuprint_array_ldouble(long double *array, unsigned int arrayCount){
	CUPRINT_ARRAY_CODE(long double , array, arrayCount, "%Lf ")
}



Boolean cucmp_float(float a, float b){
	return fabs(a - b) < 0.0001f;
}
Boolean cucmp_double(double a, double b){
	return fabs(a - b) < 0.0000001;
}
Boolean cucmp_ldouble(long double a, long double b){
	long double dif = a - b;
	return (dif < 0.0) ? (dif > 0.000001) : (dif < 0.000001);
}

