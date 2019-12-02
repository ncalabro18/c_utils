#ifndef C_UTILS_H
#define C_UTILS_H

#include "cu_tests.h"
#include "structures/cu_arraylist.h"
#include "structures/cu_string.h"
#include "structures/cu_stack.h"
#include "structures/cu_queue.h"

#include <stdio.h>


//creates random arrays for the specified datatype with arrayCount
//if return value is non-null, the pointer is dynamic and must be deallocated w/ free()
int*          cumake_randomArray_int(unsigned int arrayCount, int max);
unsigned int* cumake_randomArray_uint(unsigned int arrayCount, unsigned int max);
float*        cumake_randomArray_float(unsigned int arrayCount, float max);


//returns the first occurence of the number in the array of length arrayCount
//returns a negative value if number was not found
int cusearch_linear_int(int *array, unsigned int arrayCount, int number);
int cusearch_linear_uint(unsigned int *array, unsigned int arrayCount, unsigned int number);
int cusearch_linear_short(short *array, unsigned int arrayCount, short number);
int cusearch_linear_ushort(unsigned short *array, unsigned int arrayCount, unsigned short number);
int cusearch_linear_long(long *array, unsigned int arrayCount, long number);
int cusearch_linear_ulong(unsigned long *array, unsigned int arrayCount, unsigned long number);
int cusearch_linear_float(float *array, unsigned int arrayCount, float number);
int cusearch_linear_double(double *array, unsigned int arrayCount, double number);
int cusearch_linear_ldouble(long double *array, unsigned int arrayCount, long double number);


//given a sorted array,
int cusearch_binary_int(int *array, unsigned int arrayCount, int number);
int cusearch_binary_uint(unsigned int *array, unsigned int arrayCount, unsigned int number);
int cusearch_binary_short(short *array, unsigned int arrayCount, short number);
int cusearch_binary_ushort(unsigned short *array, unsigned int arrayCount, unsigned short number);
int cusearch_binary_long(long *array, unsigned int arrayCount, long number);
int cusearch_binary_ulong(unsigned long *array, unsigned int arrayCount, unsigned long knumber);
int cusearch_binary_float(float *array, unsigned int arrayCount, float number);
int cusearch_binary_double(double *array, unsigned int arrayCount, double number);
int cusearch_binary_ldouble(long double *array, unsigned int arrayCount, long double number);

void cusort_bubble_int(int *array, unsigned int arrayCount);
void cusort_bubble_uint(unsigned int *array, unsigned int arrayCount);
void cusort_bubble_float(float *array, unsigned int arrayCount);

void cusort_selection_int(int *array, unsigned int arrayCount);
void cusort_selection_uint(unsigned int *array, unsigned int arrayCount);
void cusort_selection_float(float *array, unsigned int arrayCount);

void cusort_merge_int(int *array, unsigned int arrayCount);

//swaps the values at the pointers a and b
void cuswap_int(int *a, int *b);
void cuswap_uint(unsigned int *a, unsigned int *b);
void cuswap_short(short *a, short *b);
void cuswap_ushort(unsigned short *a, unsigned short *b);
void cuswap_long(long *a, long *b);
void cuswap_ulong(unsigned long *a, unsigned long *b);
void cuswap_float(float *a, float *b);
void cuswap_double(double *a, double *b);
void cuswap_ldouble(long double *a, long double *b);

//change output for cuprint functions to the given file stream
void cuprint_setOutput(FILE*);

//prints the given array
void cuprint_array_int(int *array, unsigned int arrayCount);
void cuprint_array_uint(unsigned int *array, unsigned int arrayCount);
void cuprint_array_short(short *array, unsigned int arrayCount);
void cuprint_array_ushort(unsigned short *array, unsigned int arrayCount);
void cuprint_array_long(long *array, unsigned int arrayCount);
void cuprint_array_ulong(unsigned long *array, unsigned int arrayCount);
void cuprint_array_float(float *array, unsigned int arrayCount);
void cuprint_array_double(double *array, unsigned int arrayCount);
void cuprint_array_ldouble(long double *array, unsigned int arrayCount);


//accurate equivalence testing for floating types
Boolean cucmp_float(float a, float b);
Boolean cucmp_double(double a, double b);
Boolean cucmp_ldouble(long double a, long double b);


#endif
