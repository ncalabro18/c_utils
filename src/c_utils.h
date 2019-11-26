#ifndef C_UTILS_H
#define C_UTILS_H
#include "util.h"

int cusearch_linear_int(int *array, unsigned int arrayCount, int number);
int cusearch_linear_uint(unsigned int *array, unsigned int arrayCount, unsigned int number);
int cusearch_linear_float(float *arrray, unsigned int arrayCount, float num);

int cusearch_binary_int(int *array, unsigned int arrayCount, int number);
int cusearch_binary_uint(unsigned int *array, unsigned int arrayCount, unsigned int number);
int cusearch_binary_float(float *array, unsigned int arrayCount, float number);

void cusort_bubble_int(int *array, unsigned int arrayCount);
void cusort_bubble_uint(unsigned int *array, unsigned int arrayCount);
void cusort_bubble_float(float *array, unsigned int arrayCount);

void cusort_selection_int(int *array, unsigned int arrayCount);
void cusort_selection_uint(unsigned int *array, unsigned int arrayCount);
void cusort_selection_float(float *array, unsigned int arrayCount);

void cusort_merge_int(int *array, unsigned int arrayCount);
void cusort_merge_uint(unsigned int *array, unsigned int arrayCount);
void cusort_merge_float(float *array, unsigned int arrayCount);


void cuswap_int(int *a, int *b);
void cuswap_uint(unsigned int *a, unsigned int *b);
void cuswap_float(float *a, float *b);

Boolean cucmp_float(float a, float b);
Boolean cucmp_double(double a, double b);

#endif
