#ifndef C_UTILS_H
#define C_UTILS_H

#include "cu_tests.h"
#include "structures/cu_arraylist.h"
#include "structures/cu_string.h"
#include "structures/cu_stack.h"
#include "structures/cu_queue.h"
#include <stdio.h>
#include <string.h>


//returns the first occurence of the number in the array of length arrayCount
//returns a negative value if number was not found
int cusearch_linear_int(int *array, unsigned int arrayCount, int number);
int cusearch_linear_uint(unsigned int *array, unsigned int arrayCount, unsigned int number);
int cusearch_linear_char(char *array, unsigned int arrayCount, int number);
int cusearch_linear_uchar(unsigned char*array, unsigned int arrayCount, int number);
int cusearch_linear_short(short *array, unsigned int arrayCount, short number);
int cusearch_linear_ushort(unsigned short *array, unsigned int arrayCount, unsigned short number);
int cusearch_linear_long(long *array, unsigned int arrayCount, long number);
int cusearch_linear_ulong(unsigned long *array, unsigned int arrayCount, unsigned long number);
int cusearch_linear_float(float *array, unsigned int arrayCount, float number);
int cusearch_linear_double(double *array, unsigned int arrayCount, double number);
int cusearch_linear_ldouble(long double *array, unsigned int arrayCount, long double number);


int cusearch_binary_int(int *array, unsigned int arrayCount, int number);
int cusearch_binary_uint(unsigned int *array, unsigned int arrayCount, unsigned int number);
int cusearch_binary_char(char *array, unsigned int arrayCount, char number);
int cusearch_binary_uchar(unsigned char *array, unsigned int arrayCount, unsigned char number);
int cusearch_binary_short(short *array, unsigned int arrayCount, short number);
int cusearch_binary_ushort(unsigned short *array, unsigned int arrayCount, unsigned short number);
int cusearch_binary_long(long *array, unsigned int arrayCount, long number);
int cusearch_binary_ulong(unsigned long *array, unsigned int arrayCount, unsigned long knumber);
int cusearch_binary_float(float *array, unsigned int arrayCount, float number);
int cusearch_binary_double(double *array, unsigned int arrayCount, double number);
int cusearch_binary_ldouble(long double *array, unsigned int arrayCount, long double number);

void cusort_bubble_int(int *array, unsigned int arrayCount);
void cusort_bubble_uint(unsigned int *array, unsigned int arrayCount);
void cusort_bubble_char(char *array, unsigned int arrayCount);
void cusort_bubble_uchar(unsigned char *array, unsigned int arrayCount);
void cusort_bubble_short(short *array, unsigned int arrayCount);
void cusort_bubble_ushort(unsigned short *array, unsigned int arrayCount);
void cusort_bubble_long(long *array, unsigned int arrayCount);
void cusort_bubble_ulong(unsigned long*array, unsigned int arrayCount);
void cusort_bubble_float(float *array, unsigned int arrayCount);
void cusort_bubble_double(double *array, unsigned int arrayCount);
void cusort_bubble_ldouble(long double *array, unsigned int arrayCount);

void cusort_selection_int(int *array, unsigned int arrayCount);
void cusort_selection_uint(unsigned int *array, unsigned int arrayCount);
void cusort_selection_char(char *array, unsigned int arrayCount);
void cusort_selection_uchar(unsigned char *array, unsigned int arrayCount);
void cusort_selection_short(short *array, unsigned int arrayCount);
void cusort_selection_ushort(unsigned short *array, unsigned int arrayCount);
void cusort_selection_long(long *array, unsigned int arrayCount);
void cusort_selection_ulong(unsigned long *array, unsigned int arrayCount);
void cusort_selection_float(float *array, unsigned int arrayCount);
void cusort_selection_double(double *array, unsigned int arrayCount);
void cusort_selection_ldouble(long double *array, unsigned int arrayCount);

void cusort_merge_int(int *array, unsigned int arrayCount);

/*
void cusort_merge_uint(unsigned int *array, unsigned int arrayCount);
void cusort_merge_char(char *array, unsigned int arrayCount);
void cusort_merge_uchar(unsigned char *array, unsigned int arrayCount);
void cusort_merge_short(short *array, unsigned int arrayCount);
void cusort_merge_ushort(unsigned short *array, unsigned int arrayCount);
void cusort_merge_long(long *array, unsigned int arrayCount);
void cusort_merge_ulong(unsigned logn*array, unsigned int arrayCount);
void cusort_merge_float(float *array, unsigned int arrayCount);
void cusort_merge_double(double *array, unsigned int arrayCount);
void cusort_merge_ldouble(long double *array, unsigned int arrayCount);
*/

//swaps the values at the pointers a and b
void cuswap_int(int *a, int *b);
void cuswap_uint(unsigned int *a, unsigned int *b);
void cuswap_char(char *a, char *b);
void cuswap_uchar(unsigned char *a, unsigned char *b);
void cuswap_short(short *a, short *b);
void cuswap_ushort(unsigned short *a, unsigned short *b);
void cuswap_long(long *a, long *b);
void cuswap_ulong(unsigned long *a, unsigned long *b);
void cuswap_float(float *a, float *b);
void cuswap_double(double *a, double *b);
void cuswap_ldouble(long double *a, long double *b);

void cuswap_memory(byte *a, byte *b, unsigned int size);
void cuswap_memory_safe(byte *a, byte *b, unsigned int size);

//change output for cuprint functions to the given file stream
void cuprint_setOutput(FILE*);

//prints the given array
void cuprint_array_int(int *array, unsigned int arrayCount);
void cuprint_array_uint(unsigned int *array, unsigned int arrayCount);
void cuprint_array_char(char *array, unsigned int arrayCount);
void cuprint_array_uchar(unsigned char *array, unsigned int arrayCount);
void cuprint_array_short(short *array, unsigned int arrayCount);
void cuprint_array_ushort(unsigned short *array, unsigned int arrayCount);
void cuprint_array_long(long *array, unsigned int arrayCount);
void cuprint_array_ulong(unsigned long *array, unsigned int arrayCount);
void cuprint_array_float(float *array, unsigned int arrayCount);
void cuprint_array_double(double *array, unsigned int arrayCount);
void cuprint_array_ldouble(long double *array, unsigned int arrayCount);

/*
int* cumake_randomArray_int(unsigned int arrayCount);
unsigned int* cumake_randomArray_uint(unsigned int arrayCount);
char* cumake_randomArray_char(unsigned int arrayCount);
cumake_randomArray_uchar(unsigned int arrayCount);
cumake_randomArray_short(unsigned int arrayCount);
cumake_randomArray_ushort(unsigned int arrayCount);
cumake_randomArray_long(unsigned int arrayCount);
cumake_randomArray_ulong(unsigned int arrayCount);
cumake_randomArray_float(unsigned int arrayCount);
cumake_randomArray_double(unsigned int arrayCount);
cumake_randomArray_ldouble(unsigned int arrayCount);
*/

//accurate equivalence testing for floating types
Boolean cucmp_float(float a, float b);
Boolean cucmp_double(double a, double b);
Boolean cucmp_ldouble(long double a, long double b);


#endif
