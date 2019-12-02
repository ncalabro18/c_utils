//called NString for Nick's String, mostly for concern over compatibility
#ifndef N_String_H
#define N_String_H

#define NSTRING_DEFAULT_CAPACITY 8

#include <stdio.h>
#include "../util.h"


typedef void* NString;



NString nstr_initialize();

NString nstr_initialize_cstr(const char *c_str);

NString cu_nstirng_init_capacity(unsigned int capacity);

NString cu_nstring_init_char(char c);

NString nstr_initialize_nstring( NString copy);

NString cu_nstring_substring(NString const str, unsigned int a, unsigned int b);

Status cu_nstring_concat_nstring(NString left, NString const right);
Status cu_nstring_concat_char(NString str, char c);
Status cu_nstring_concat_cstr(NString str, const char *cstr);

char* nstr_cstr(NString);

Boolean cu_nstring_contains(NString const str1, NString const str2);

Status cu_nstring_print(NString const str, FILE* file);

int cu_nstring_cmp(NString const str1, NString const str2);

int cu_nstring_getChar(NString const str, unsigned int index);

Status cu_nstring_setChar(NString str, char c, unsigned int index); //index must be in bounds

int cu_nstring_length(NString const str);


Status cu_nstring_resize(NString str, unsigned int minimumCapacity);

void cu_nstring_destroy(NString* s); //NOTE pass the address of the opaque object for// cu_nstring_destroy function

#endif
