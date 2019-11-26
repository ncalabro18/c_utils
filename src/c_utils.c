#include "c_utils.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CUSWAP_CODE(type, a, b)\
	{type _temp = *a;\
	*a = *b;\
	*b = _temp;}

//CUTILS_LINEAR_CODE refers to code that is the exact same for each linear seach function
#define CUSEARCH_LINEAR_CODE(array, arrayCount, number)\
	{unsigned int i;\
	if(!(array)) return -2;\
	for(i = 0; i < (arrayCount); i++)\
		if(array[i] == (number))\
			return i;\
	return -1;}

#define CUSEARCH_BINARY_CODE(array, arrayCount, number)


#define CUSORT_SELECTION_CODE(type, array, arrayCount)\
	for(unsigned int i = 0; i < arrayCount - 1; i++){\
		unsigned int min = i;\
		for(int j = i; j < arrayCount; j++)\
			if(array[j] < array[min])\
				min = j;\
	}


#define CUSORT_BUBBLE_CODE(type, array, arrayCount)\
	{unsigned int swaps;\
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





int cusearch_linear_int(int *array, unsigned int arrayCount, int number){
	 CUSEARCH_LINEAR_CODE(array, arrayCount, number)
}

int cusearch_linear_uint(unsigned int *array, unsigned int arrayCount, unsigned int number){
	 CUSEARCH_LINEAR_CODE(array, arrayCount, number)
}

int cusearch_linear_float(float *array, unsigned int arrayCount, float number){
	 CUSEARCH_LINEAR_CODE(array, arrayCount, number)
}

int cusearch_binary_int(int *array, unsigned int arrayCount, int number);
int cusearch_binary_uint(unsigned int *array, unsigned int arrayCount, unsigned int number);
int cusearch_binary_float(float *array, unsigned int arrayCount, float number);



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

void cusort_merge_uint(unsigned int *array, unsigned int arrayCount);
void cusort_merge_float(float *array, unsigned int arrayCount);




void cuswap_int(int *a, int *b){
	CUSWAP_CODE(int,a,b)
}
void cuswap_uint(unsigned int *a, unsigned int *b){
	CUSWAP_CODE(unsigned int,a,b)
}
void cuswap_float(float *a, float *b){
	CUSWAP_CODE(float,a,b)
}

Boolean cucmp_float(float a, float b){
	return fabs(a - b) < 0.0001f;
}
Boolean cucmp_double(double a, double b){
	return fabs(a - b) < 0.0000001;
}
