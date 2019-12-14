#include "cu_string.h"
#include "../cu_utils.h"
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define cast(x) ((CU_STRING*)(x))
#define RESIZE_MODIFIER 2

typedef struct CU_STRING{
    unsigned int length;
    unsigned int capacity;
    char *data;
} CU_STRING;



CUString cu_string_init(){
    return cu_string_init_cstr("");
}

CUString cu_string_init_cstr(const char *c_str){
    int length = strlen(c_str);
    CU_STRING *str = (CU_STRING*) cu_string_init_capacity(
            length < NSTRING_DEFAULT_CAPACITY ? NSTRING_DEFAULT_CAPACITY : length + 1);
    if(!str) return NULL;

    memcpy(str->data, c_str, length);

    str->length = length;

    return (CUString) str;
}

CUString cu_string_init_capacity(unsigned int capacity){
    CU_STRING *str = (CU_STRING*) malloc(sizeof(CU_STRING));
    if(!str) return NULL;

    str->data = (char*) malloc(capacity);
    if(!(str->data)){
        free(str);
        return NULL;
    }
    str->capacity = capacity;
    str->length = 0;

    return (CUString) str;
}

CUString cu_string_init_char(char c){
    CU_STRING *str = (CU_STRING*) cu_string_init_capacity(NSTRING_DEFAULT_CAPACITY);
    if(!str) return NULL;

    str->data[0] = c;
    str->length = 1;

    return (CUString) str;
}

CUString cu_string_init_charArray(const char *charArray, unsigned int length){
	CU_STRING *str = (CU_STRING*) cu_string_init_capacity(length + 1);
	if(!str) return NULL;
	
	memcpy(str->data, charArray, length);
	str->length = length;
	str->capacity = length + 1;

	return str;
}


CUString cu_string_init_custring(const CUString copy){
    return cu_string_substring(copy, 0, cu_string_length(copy));
}

CUString cu_string_init_int(int num){
	if(num == 0)
		return cu_string_init_char('0');
	Boolean is_signed = num < 0;
	CUString str = cu_string_init();
	if(!str) return NULL;
	

	while(num != 0){
		int c = num % 10;
		if(is_signed) c *= -1;
		

		if(cu_string_concat_char(str, (char)(c + '0')) == FAILURE){
			return NULL;
		}
		num /= 10;
	}
	if(is_signed)
		if(cu_string_concat_char(str, '-') == FAILURE){
			return NULL;
		}
	if(cu_string_reverse(str) == FAILURE) return NULL;

	return str;
}

CUString cu_string_init_uint(unsigned int num){
	CUString str = cu_string_init();
	if(!str) return NULL;

	while(num > 0){
		if(cu_string_concat_char(str, (char)((num % 10) + '0')) == FAILURE){
			return NULL;
		}
		num /= 10;
	}
	if(cu_string_reverse(str) == FAILURE) return NULL;

	return str;
}

CUString cu_string_init_float(float num){
	return cu_string_init_double(num);
}
CUString cu_string_init_double(double num){
	CUString str = cu_string_init_capacity(0x10);
	Boolean is_signed = FALSE;
	if(num < 0.0)
		is_signed = TRUE;
	long whole = (long) num;
	double f = num - whole;
	
	while(whole > 0){
		if(cu_string_concat_char(str, (whole % 10) + '0') == FAILURE)
			return NULL;
		whole /= 10;
	}
	if(is_signed)
		if(cu_string_concat_char(str, '-') == FAILURE)
			return NULL;

	if(cu_string_reverse(str) == FAILURE)
		return NULL;

	if(f > 0.001)
		if(cu_string_concat_char(str, '.') == FAILURE)
			return NULL;

	while(f > 0.001){
		f *= 10;
		int digit = ((int)f) % 10;
		f -= digit;
		if(cu_string_concat_char(str, (char) digit + '0') == FAILURE)
			return NULL;
	}
	return str;
}

CUString cu_string_substring(const CUString str, unsigned int a, unsigned int b){
	if(!str || a >= cast(str)->length || b > cast(str)->length)
		return NULL;
	if(a == b)
		return cu_string_init();
	if(a > b)
       		cuswap_uint(&a, &b);

    
	unsigned int len = b - a;
	CU_STRING *substr = cast(cu_string_init_capacity(len + 1));
	
	memcpy(substr->data, cast(str)->data + a, len);
	
	substr->length = len;
	
	return (CUString) substr;
}

CUString cu_string_extract(FILE *file){
	if(!file)
		return NULL;

	CUString str = cu_string_init();
	int c = fgetc(file);
	do{
		if(c == EOF){
			cu_string_destroy(&str);
			return NULL;
		}
		if(!isspace((char)c))
			break;
		c = fgetc(file);
	}while(1);
	
	do{
		if(isspace((char)c))
			break;
			
		if(c == EOF){
			cu_string_destroy(&str);
			return NULL;
		}

		if(cu_string_concat_char(str, (char) c) == FAILURE){
			cu_string_destroy(&str);
			return NULL;
		}
		c = fgetc(file);
	}while(1);


	ungetc(c, file);
	return str;
}

//Status cu_string_resize(CUString str, unsigned int minimumCapacity);
//2 memory operations:
//	first memmove to account for the new size
//	then memcpy to copy the newSegment into the string object
//	ex. ("hello, world", 3, 6, "foobar")
//	1st: "hel...... world" //value of dots insignificant
//	2nd: "helfoobar world
Status cu_string_setSegment(CUString str, unsigned int a, unsigned int b, const char *newSegment){
	if(!str || !newSegment) return FAILURE;	
	if(a > b || b > cast(str)->length) return FAILURE;

	//size refers to the segment
	int size_old = b - a;
	int size_new = strlen(newSegment);

	//new length for the string
	int length_new = (size_new - size_old) + cast(str)->length;

	if(size_old != size_new){
		if(cu_string_resize(str, length_new) == FAILURE)
			return FAILURE;

		memmove(
			cast(str)->data + a + size_new, 
			cast(str)->data + b,
		       	cast(str)->length - b);
	}

	memcpy(cast(str)->data + a, newSegment, size_new);
	cast(str)->length = length_new;

	return SUCCESS;
}

Status cu_string_concat_char(CUString str, char c){
    if(!str) return FAILURE;

    cast(str)->data[cast(str)->length] = c;
    cast(str)->length++;

    return SUCCESS;
}


Status cu_string_concat_cstr(CUString str, const char *cstr){
    if(!str || !cstr) return FAILURE;

    unsigned int length = strlen(cstr);
    if(!cu_string_resize(cast(str), cast(str)->length + length))
        return FAILURE;

    memcpy(cast(str)->data + cast(str)->length, cstr, length);

    cast(str)->length += length;

    return SUCCESS;
}


Status cu_string_concat_custring(CUString left, const CUString right){
    if(left == NULL || right == NULL)
        return FAILURE;

    if(!cu_string_resize(cast(left), cast(left)->length + cast(right)->length))
        return FAILURE;

    memcpy(cast(left)->data + cast(left)->length, cast(right)->data, cast(right)->length);
    cast(left)->length += cast(right)->length;

    return SUCCESS;
}

Status cu_string_reverse(CUString str){
	if(!str) return FAILURE;

	for(int i = 0, j = cast(str)->length - 1; i < j; i++, j--)
		cuswap_char(cast(str)->data + i, cast(str)->data + j);

	return SUCCESS;
}

void cu_string_clear(CUString str){
	if(!str || cast(str)->length == 0) return;
	cast(str)->length = 0;	
}


char* cu_string_cstr(CUString str){
    if(!str) return NULL;

    if(!cu_string_resize(cast(str), cast(str)->length + 1)) return NULL;

    cast(str)->data[cast(str)->length] = '\0';

    return cast(str)->data;
}

#define CU_STRING_CONTAINS_CODE(str1, str2, str2_length, str2jget)\
	if(!str1 || !str2) return -2;\
	for(unsigned int i = 0; i < cast(str1)->length - str2_length; i++){\
        for(j = 0; j < str2_length; j++) {\
        	if (cast(str1)->data[i + j] != str2jget)\
                break;\
        }\
        if(j == str2_length)\
            return i;\
	}\
	return -1;\


int cu_string_contains_custring(const CUString str1, const CUString str2){
	unsigned int j;
	CU_STRING_CONTAINS_CODE(str1, str2, cast(str2)->length, cast(str2)->data[j])
}

int cu_string_contains_cstr(const CUString str, const char *cstr){	
	unsigned int j;
	CU_STRING_CONTAINS_CODE(str, cstr, strlen(cstr), cstr[j])
}

int cu_string_contains_char(CUString str, char c){
	if(!str) return -2;
	for(unsigned int i = 0; i < cast(str)->length; i++)
		if(cast(str)->data[i] == c)
			return i;
	return -1;
}


Status cu_string_print(const CUString str, FILE* file){
    if(!str || !file)
        return FAILURE;

    fwrite(cast(str)->data, 1, cast(str)->length, file);

    return SUCCESS;
}

int cu_string_cmp(const CUString str1, const CUString str2){
    //NULL check for str1 is covered from the function calls
    char *cstr1 = cu_string_cstr(str1);
    char *cstr2 = cu_string_cstr(str2);

    if(!cstr1 || !cstr2)
        return INT_MAX;
    return strcmp(cstr1, cstr2);
}

int cu_string_getChar(const CUString str, unsigned int index){
    if(!str || index >= cast(str)->length)
        return -1;

    return cast(str)->data[index];
}

Status cu_string_setChar(CUString str, char c, unsigned int index){
    if(!str || index >= cast(str)->length) return FAILURE;

    cast(str)->data[index] = c;

    return SUCCESS;
}

int cu_string_length(const CUString str) {
    if(!str) return -1;
    return cast(str)->length;
}


Status cu_string_resize(CUString str, unsigned int minimumCapacity){

        while(cast(str)->capacity < minimumCapacity) {
            char *tempData = (char*) realloc(cast(str)->data, cast(str)->capacity * RESIZE_MODIFIER);
            if (!tempData) return FAILURE;
            cast(str)->data = tempData;
            cast(str)->capacity *= RESIZE_MODIFIER;
        }
        return SUCCESS;
}

void cu_string_destroy(CUString *s){
    if(!s || !*s) return;

    free(cast(*s)->data);
    free(*s);
    *s = NULL;
}
