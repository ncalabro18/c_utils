#include "cu_string.h"
#include <stdlib.h>
#include <limits.h>
#include <string.h>

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

    *(str->data) = c;
    str->length++;

    return (CUString) str;
}

CUString cu_string_init_custring(const CUString copy){
    return cu_string_substring(copy, 0, cu_string_length(copy));
}

CUString cu_string_substring(const CUString str, unsigned int a, unsigned int b){
    if(a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    if(!str || a >= cast(str)->length || b > cast(str)->length)
        return NULL;

    CU_STRING *substr = cast(cu_string_init_capacity(b - a));
    CU_STRING *orgstr = cast(str);

    memcpy(substr->data, orgstr->data, substr->capacity);

    substr->length = substr->capacity;

    return (CUString) substr;
}

Status cu_string_concat_char(CUString str, char c){
    if(!str) return FAILURE;

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


Status cu_string_concat_string(CUString left, const CUString right){
    if(left == NULL || right == NULL)
        return FAILURE;

    if(!cu_string_resize(cast(left), cast(left)->length + cast(right)->length))
        return FAILURE;

    memcpy(cast(left)->data + cast(left)->length, cast(right)->data, cast(right)->length);
    cast(left)->length += cast(right)->length;

    return SUCCESS;
}


char* cu_string_cstr(CUString str){
    if(!str) return NULL;

    if(!cu_string_resize(cast(str), cast(str)->length + 1)) return NULL;

    cast(str)->data[cast(str)->length] = '\0';

    return cast(str)->data;
}


Boolean cu_string_contains(const CUString str1, const CUString str2){
    if(!str1 || !str2)
        return FALSE;

    for(int i = 0; i < cast(str1)->length - cast(str2)->length; i++){
        int j;
        for(j = 0; j < cast(str2)->length; j++) {
            if (cast(str1)->data[i + j] != cast(str2)->data[j])
                break;
        }
        if(j == cast(str2)->length)
            return TRUE;
    }

    return FALSE;
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
