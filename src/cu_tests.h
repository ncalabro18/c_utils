#ifndef CU_TESTS_H
#define CU_TESTS_H

#include <stdio.h>
#include "cu_utils.h"
#include "structures/cu_arraylist.h"

typedef void* CUTests;

CUTests cu_tests_init();

void cu_tests_setOutput(CUTests ut, FILE *file);

void cu_tests_addTest(CUTests ut, Status(*function)(char*, unsigned int));
		
Status cu_tests_test(CUTests t);

void cu_tests_log(CUTests t, const char *);

CUArrayList cu_tests_results(CUTests t);

void cu_tests_destroy(CUTests* pt);

#endif
