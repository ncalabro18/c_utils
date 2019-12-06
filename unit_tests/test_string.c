#include "cu_tests.h"
#include "structures/cu_string.h"
#include <string.h>


Status testfunc_string_init_int(CUTests t);

int main(void){

	CUTests tests = cu_tests_init();

	cu_tests_addTest(tests, testfunc_string_init_int);

	cu_tests_test(tests);

	cu_tests_destroy(&tests);

	return 0;
}


Status testfunc_string_init_int(CUTests t){


	CUString s1 = cu_string_init_int(5);
	CUString s2 = cu_string_init_int(572);
	CUString s3 = cu_string_init_int(65);
	CUString s4 = cu_string_init_int(22);
	CUString s5 = cu_string_init_int(1);
	CUString s6 = cu_string_init_int(78653);
	CUString s7 = cu_string_init_int(928142);


	cu_tests_log(t, "s1:");

	if(cu_string_getChar(s1, 0) != '5') return FAILURE;

	cu_tests_log(t, "s2:");
	cu_tests_log(t, cu_string_cstr(s2));

	if(cu_string_getChar(s2, 0) != '5') return FAILURE;
	if(cu_string_getChar(s2, 1) != '7') return FAILURE;
	if(cu_string_getChar(s2, 2) != '2') return FAILURE;

	cu_tests_log(t, "s3:");

	if(cu_string_getChar(s3, 0) != '6') return FAILURE;
	if(cu_string_getChar(s3, 1) != '5') return FAILURE;

	cu_tests_log(t, "s4:");
	
	if(cu_string_getChar(s4, 0) != '2') return FAILURE;
	if(cu_string_getChar(s4, 1) != '2') return FAILURE;


	cu_tests_log(t, "s5:");

	if(cu_string_getChar(s5, 0) != '1') return FAILURE;

	cu_tests_log(t, "s6:");

	if(cu_string_getChar(s6, 0) != '7') return FAILURE;
	if(cu_string_getChar(s6, 1) != '8') return FAILURE;
	if(cu_string_getChar(s6, 2) != '6') return FAILURE;
	if(cu_string_getChar(s6, 3) != '5') return FAILURE;
	if(cu_string_getChar(s6, 4) != '3') return FAILURE;


	cu_tests_log(t, "s7:");

	if(cu_string_getChar(s7, 0) != '9') return FAILURE;
	if(cu_string_getChar(s7, 1) != '2') return FAILURE;
	if(cu_string_getChar(s7, 2) != '8') return FAILURE;
	if(cu_string_getChar(s7, 3) != '1') return FAILURE;
	if(cu_string_getChar(s7, 4) != '4') return FAILURE;
	if(cu_string_getChar(s7, 5) != '2') return FAILURE;


	cu_string_destroy(&s1);
	cu_string_destroy(&s2);
	cu_string_destroy(&s3);
	cu_string_destroy(&s4);
	cu_string_destroy(&s5);
	cu_string_destroy(&s6);
	cu_string_destroy(&s7);


	return SUCCESS;
}

/*
Status testCase_nstr_cmp(const char *a, const char *b){
    NString str1 = nstr_initialize_cstr(a);
    NString str2 = nstr_initialize_cstr(b);

    int n = nstr_cmp(str1, str2);
    int c = strcmp(a, b);

    int returnVal = (c == n) ? SUCCESS : FAILURE;

    nstr_destroy(&str1);
    nstr_destroy(&str2);

    return returnVal;
}

Status testCase_nstr_substring(const char *cstr, unsigned int a, unsigned int b){
    NString str = nstr_initialize_cstr(cstr);
    NString substr = nstr_substring(str, a, b);
    for(unsigned int i = a; i < b; i++)
        if(nstr_charAt(str, i) != nstr_charAt(substr, i - a))
            return FAILURE;
    nstr_destroy(&str);
    nstr_destroy(&substr);
    return SUCCESS;
}

Status testCase_nstr_concat(const char *a, const char *b){
    NString str1 = nstr_initialize_cstr(a);
    NString str2 = nstr_initialize_cstr(b);

    int original_length = nstr_length(str1);
    nstr_concat(str1, str2);
    int new_length = nstr_length(str1);

    for(int i = 0; i < original_length; i++)
        if(nstr_charAt(str1, i) != a[i])
            return FAILURE;

    for(int i = original_length; i < new_length; i++)
        if(nstr_charAt(str1, i) != b[i])
            return FAILURE;

    nstr_destroy(&str1);
    nstr_destroy(&str2);
    return SUCCESS;
}

Status test_cmp(char *buffer, unsigned int length){

    if(!testCase_nstr_cmp("","")) return FAILURE;
    if(!testCase_nstr_cmp("hello, world","hello, world")) return FAILURE;
    if(!testCase_nstr_cmp("jf8172o3md","jf7ha")) return FAILURE;
    if(!testCase_nstr_cmp("abcdefghijklmnopqrstuvwxyz","abcdefghijklmnopqrstuvwxyz")) return FAILURE;
    if(!testCase_nstr_cmp("asdf","asdf")) return FAILURE;
    if(!testCase_nstr_cmp("world, hello","world, he")) return FAILURE;
    if(!testCase_nstr_cmp("-+=_","-+=_")) return FAILURE;
    if(!testCase_nstr_cmp("hello","hello")) return FAILURE;
    if(!testCase_nstr_cmp("this seems excessive","this idk\n\t")) return FAILURE;
    if(!testCase_nstr_cmp("asdf","jkl;")) return FAILURE;

    return SUCCESS;
}


Status test_substring(char *buffer, unsigned int length){

    if(!testCase_nstr_substring("", 5, 7)) return FAILURE;
    if(!testCase_nstr_substring("hello, world", 3, 6)) return FAILURE;
    if(!testCase_nstr_substring("jf8172o3md", 2, 5)) return FAILURE;
    if(!testCase_nstr_substring("abcdefghijklmnopqrstuvwxyz", 17, 20)) return FAILURE;
    if(!testCase_nstr_substring("asdf",0, 3)) return FAILURE;
    if(!testCase_nstr_substring("world, hello", 0, 1)) return FAILURE;
    //next should just be a copy of the string
    if(!testCase_nstr_substring("-+=_", 0, strlen("-+=_"))) return FAILURE;
    if(!testCase_nstr_substring("hello", 2, 4)) return FAILURE;

    //no negation for the following; they should return FAILURE
    //wrong order
    if(testCase_nstr_substring("this seems excessive", 1, 0)) return FAILURE;
    //out of bounds
    if(testCase_nstr_substring("asdf", 0, 20)) return FAILURE;

    return SUCCESS;
}

Status test_concat(char *buffer, unsigned int length){

    if(!testCase_nstr_concat("","")) return FAILURE;
    if(!testCase_nstr_concat("hello, world","hello, world")) return FAILURE;
    if(!testCase_nstr_concat("jf8172o3md","jf7ha")) return FAILURE;
    if(!testCase_nstr_concat("abcdefghijklmnopqrstuvwxyz","abcdefghijklmnopqrstuvwxyz")) return FAILURE;
    if(!testCase_nstr_concat("asdf","asdf")) return FAILURE;
    if(!testCase_nstr_concat("world, hello","world, he")) return FAILURE;
    if(!testCase_nstr_concat("-+=_","-+=_")) return FAILURE;
    if(!testCase_nstr_concat("hello","hello")) return FAILURE;
    if(!testCase_nstr_concat("this seems excessive","this idk\n\t")) return FAILURE;
    if(!testCase_nstr_concat("asdf","jkl;")) return FAILURE;

    return SUCCESS;
}
*/

