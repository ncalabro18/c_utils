#ifndef N_String_H
#define N_String_H

#define NSTRING_DEFAULT_CAPACITY 8

#include <stdio.h>
#include "../util.h"

typedef void* CUString;


CUString cu_string_init();

CUString cu_string_init_cstr(const char *c_str);

CUString cu_string_init_capacity(unsigned int capacity);

CUString cu_string_init_char(char c);

CUString cu_string_init_custring(CUString copy);

CUString cu_string_init_int(int);

//returns new string object from str[a], inclusive, to str[b], exclusive
CUString cu_string_substring(CUString str, unsigned int a, unsigned int b);

//ignores any leading whitespace characters, then puts the following non-whitespace characters into the string
//the stream after will be set to the first whitespace character following the extracted characters
CUString cu_string_extract(FILE *file);

//sets the string segment between a(inclusive) and b(exclusive) to newSegment cstr
Status cu_string_setSegment(CUString str, unsigned int a, unsigned int b, const char *newSegment);

//performs string concatination left parameter CUString is destination string
Status cu_string_concat_custring(CUString left, CUString right);
Status cu_string_concat_char(CUString str, char c);
Status cu_string_concat_cstr(CUString str, const char *cstr);


Status cu_string_reverse(CUString str);

//clears the string to the empty string ""
//does not unallocate data
void cu_string_clear(CUString str);

char* cu_string_cstr(CUString s);

Boolean cu_string_contains(CUString str1, CUString str2);

Status cu_string_print(CUString str, FILE* file);

int cu_string_cmp(CUString str1, CUString str2);

int cu_string_getChar(CUString str, unsigned int index);

Status cu_string_setChar(CUString str, char c, unsigned int index); //index must be in bounds

int cu_string_length(CUString str);

Status cu_string_resize(CUString str, unsigned int minimumCapacity);

void cu_string_destroy(CUString* s); //NOTE pass the address of the opaque object


#endif
