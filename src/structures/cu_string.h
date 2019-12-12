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

//creates a string object with the text representation of the data type
CUString cu_string_init_int(int);
CUString cu_string_init_uint(unsigned int);
CUString cu_string_init_float(float);
CUString cu_string_init_double(double);

//returns new string object from str[a], inclusive, to str[b], exclusive
CUString cu_string_substring(CUString str, unsigned int a, unsigned int b);

//ignores any leading whitespace characters, then puts the following non-whitespace characters into the string
//the stream after will be set to the first whitespace character following the extracted characters
CUString cu_string_extract(FILE *file);

//sets the string segment between a(inclusive) and b(exclusive) to newSegment cstr
Status cu_string_setSegment(CUString str, unsigned int a, unsigned int b, const char *newSegment);

//performs string concatination left parameter CUString is destination string
Status cu_string_concat_custring(CUString left, CUString right);
Status cu_string_concat_cstr(CUString str, const char *cstr);
Status cu_string_concat_char(CUString str, char c);


Status cu_string_reverse(CUString str);

//clears the string to the empty string
//does not unallocate any data
void cu_string_clear(CUString str);

//returns the string as a C string with a null charater at the end
char* cu_string_cstr(CUString s);

//returns Boolean whether str2 is contained in str1
int cu_string_contains_custring(CUString str1, CUString str2);
int cu_string_contains_cstr(CUString str1, const char *cstr);
int cu_string_contains_char(CUString str1, char c);


//prints the string to the given file stream
Status cu_string_print(CUString str, FILE* file);

//compares the 2 strings, returning 0 if theyire equal
int cu_string_cmp(CUString str1, CUString str2);

//returns the character at the givden index
int cu_string_getChar(CUString str, unsigned int index);

//sets the character at index to c
Status cu_string_setChar(CUString str, char c, unsigned int index); //index must be in bounds

//returns the number of characters stored in the string
int cu_string_length(CUString str);

//on SUCCESS, resizes the given string to at least minimumCapacity
Status cu_string_resize(CUString str, unsigned int minimumCapacity);


//clears all memory associated with the string
//NOTE pass the address of the opaque object
void cu_string_destroy(CUString* s);


#endif
