#ifndef CU_TESTS_H
#define CU_TESTS_H

#include <stdio.h>
#include "cu_utils.h"
#include "structures/cu_arraylist.h"
#include "structures/cu_string.h"


typedef void* CUTests;


CUTests cu_tests_init();

//adds the function to the list
void cu_tests_addTest(CUTests ut, Status(*function)(CUTests));		

//tests all the functions that were passed from cu_tests_addTest
//produces informative output messages in the set output file stream
Status cu_tests_test(CUTests t);

//prints the log buffer to CUTests's set output stream
void cu_tests_log(CUTests t);

//saves the specified type to the log buffer in 
//a string representation
void cu_tests_log_custring(CUTests t, CUString str);
void cu_tests_log_cstr(CUTests t, const char *str);
void cu_tests_log_int(CUTests t, int num);
void cu_tests_log_uint(CUTests t, unsigned int num);
void cu_tests_log_char(CUTests t, char num);
void cu_tests_log_float(CUTests t, float num);
void cu_tests_log_double(CUTests t, double num);

//adds newline with test prefix to the buffer
void cu_tests_log_newline(CUTests t);
//clears the log buffer
void cu_tests_log_clear(CUTests t);
//prints the log and verify the output from the input stream
Status cu_tests_log_verify(CUTests t);

void cu_tests_setOutput(CUTests ut, FILE *file);
void cu_tests_setInput(CUTests ut, FILE *file);

//returns an array containing the status of each tests result corrisponding to the index
CUArrayList cu_tests_results(CUTests t);

void cu_tests_destroy(CUTests* pt);


#endif
