//called NString for Nick's String, mostly for concern over compatibility
#ifndef N_String_H
#define N_String_H

#define NSTRING_DEFAULT_CAPACITY 8

#include <stdio.h>
#include "util.h"


typedef void* NString;



NString nstr_initialize();

NString nstr_initialize_cstr(const char *c_str);

NString nstr_initialize_capacity(unsigned int capacity);

NString nstr_initialize_char(char c);

NString nstr_initialize_nstring( NString copy);

NString nstr_substring( NString, unsigned int a, unsigned int b);

Status nstr_concat_nstring(NString left,  NString right);
Status nstr_concat_char(NString str, char c);
Status nstr_concat_cstr(NString str, const char *string);

char* nstr_cstr(NString);

Boolean nstr_contains(NString,  NString);

Status nstr_print(NString str, FILE* file);

int nstr_cmp( NString str1, NString str2);

int nstr_getChar(NString, unsigned int index);

Status nstr_setChar(NString, char c, unsigned int index); //index must be in bounds

int nstr_length(NString);


Status nstr_resize(NString str, unsigned int minimumCapacity);

void nstr_destroy(NString*); //NOTE pass the address of the opaque object for nstr_destroy function

#endif