#include "../cutils.h"
#include <stdio.h>

void print_array(int *array, unsigned int count){
	for(unsigned int i = 0; i < count; i++)
		printf("%d ", array[i]);
}

int main(){

	int array[] = {4, -2, 9, 12, 2, 10, 10, 24, -7, 15};
	unsigned int arrayCount = sizeof(array) / sizeof(int);
	
	puts("Array before:");
	print_array(array, arrayCount);

	cusort_merge_int(array, arrayCount);

	puts("Array after:");
	print_array(array, arrayCount);

	return 0;
}
