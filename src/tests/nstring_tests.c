#include "nstring.h"
#include "nstring_tests.h"
#include <string.h>


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

Status test_cmp(TEST_FUNCTION_PARAMETERS){

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


Status test_substring(TEST_FUNCTION_PARAMETERS){

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

Status test_concat(TEST_FUNCTION_PARAMETERS){

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