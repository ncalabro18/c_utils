#ifndef CU_TESTS_H
#define CU_TESTS_H

#include <stdio.h>
#include "cu_utils.h"
#include "structures/cu_arraylist.h"
#include "structures/cu_string.h"


typedef void* CUTests;

CUTests cu_tests_init();

void cu_tests_setOutput(CUTests ut, FILE *file);

void cu_tests_addTest(CUTests ut, Status(*function)(CUTests));
		
Status cu_tests_test(CUTests t);

void cu_tests_log(CUTests t, CUString msg);
void cu_tests_log_cstr(CUTests t, const char *msg);
void cu_tests_log_int(CUTests t, int num);
void cu_tests_log_uint(CUTests t, unsigned int num);
void cu_tests_log_char(CUTests t, char num);
void cu_tests_log_float(CUTests t, float num);
void cu_tests_log_double(CUTests t, double num);
void cu_tests_log_newline(CUTests t);
void cu_tests_log_clear(CUTests t);

CUArrayList cu_tests_results(CUTests t);

void cu_tests_destroy(CUTests* pt);


#endif
