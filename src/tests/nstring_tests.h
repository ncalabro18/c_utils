#ifndef N_STRING_TESTS_H
#define N_STRING_TESTS_H

//define to allow easily adding an error message parameter if I require one
#define TEST_FUNCTION_PARAMETERS void

//test functions
Status test_cmp(TEST_FUNCTION_PARAMETERS);
Status test_substring(TEST_FUNCTION_PARAMETERS);
Status test_concat(TEST_FUNCTION_PARAMETERS);

#endif