#include "nstring.h"
#include <stdlib.h>

#include <ctype.h>
#include <string.h>

#define cast(x) ((NSTRING*)(x))
#define RESIZE_MODIFIER 2

typedef struct _nstring{
    unsigned int length;
    unsigned int capacity;
    char *data;
} NSTRING;



NString nnstr_initialize(){
    return nstr_initialize_cstr("");
}

NString nstr_initialize_cstr(const char *c_str){
    int length = strlen(c_str);
    NSTRING *str = (NSTRING*) nstr_initialize_capacity(
            length < NSTRING_DEFAULT_CAPACITY ? NSTRING_DEFAULT_CAPACITY : length);
    if(!str) return NULL;

    memcpy(str->data, c_str, length);

    str->length = length;

    return (NString) str;
}

NString nstr_initialize_capacity(unsigned int capacity){
    NSTRING *str = (NSTRING*) malloc(sizeof(NSTRING));
    if(!str) return NULL;

    str->data = (char*) malloc(capacity);
    if(!(str->data)){
        free(str);
        return NULL;
    }
    str->capacity = capacity;
    str->length = 0;

    return (NString) str;
}

NString nstr_initialize_char(char c){
    NSTRING *str = (NSTRING*) nstr_initialize_capacity(NSTRING_DEFAULT_CAPACITY);
    if(!str) return NULL;

    *(str->data) = c;
    str->length++;

    return (NString) str;
}

NString nstr_initialize_nstring(const NString copy){
    return nstr_substring(copy, 0, nstr_length(copy));
}

NString nstr_substring(const NString str, unsigned int a, unsigned int b){
    if(a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    if(!str || a >= cast(str)->length || b > cast(str)->length)
        return NULL;

    NSTRING *substr = cast(nstr_initialize_capacity(b - a));
    NSTRING *orgstr = cast(str);

    memcpy(substr->data, orgstr->data, substr->capacity);

    substr->length = substr->capacity;

    return (NString) substr;
}

Status nstr_concat_char(NString str, char c){
    if(!str) return FAILURE;

    return SUCCESS;
}


Status nstr_concat_cstr(NString str, const char *cstr){
    if(!str || !cstr) return FAILURE;

    unsigned int length = strlen(cstr);
    if(!nstr_resize(cast(str), cast(str)->length + length))
        return FAILURE;

    memcpy(cast(str)->data + cast(str)->length, cstr, length);

    cast(str)->length += length;

    return SUCCESS;
}


Status nstr_concat_nstring(NString left, const NString right){
    if(left == NULL || right == NULL)
        return FAILURE;

    if(!nstr_resize(cast(left), cast(left)->length + cast(right)->length))
        return FAILURE;

    memcpy(cast(left)->data + cast(left)->length, cast(right)->data, cast(right)->length);
    cast(left)->length += cast(right)->length;

    return SUCCESS;
}


char* nstr_cstr(NString str){
    if(!str) return NULL;

    if(!nstr_resize(cast(str), cast(str)->length + 1)) return NULL;

    cast(str)->data[cast(str)->length] = '\0';

    return cast(str)->data;
}


Boolean nstr_contains(const NString str1, const NString str2){
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

Status nstr_print(const NString str, FILE* file){
    if(!str || !file)
        return FAILURE;

    fwrite(cast(str)->data, 1, cast(str)->length, file);

    return SUCCESS;
}

int nstr_cmp(const NString str1, const NString str2){
    //NULL check for str1 is covered from the function calls
    char *cstr1 = nstr_cstr(str1);
    char *cstr2 = nstr_cstr(str2);

    if(!cstr1 || !cstr2)
        return INT_MAX;
    return strcmp(cstr1, cstr2);
}

int nstr_getChar(const NString str, unsigned int index){
    if(!str || index >= cast(str)->length)
        return -1;

    return cast(str)->data[index];
}

Status nstr_setChar(NString str, char c, unsigned int index){
    if(!str || index >= cast(str)->length) return FAILURE;

    cast(str)->data[index] = c;

    return SUCCESS;
}

int nstr_length(const NString str) {
    if(!str) return -1;
    return cast(str)->length;
}


Status nstr_resize(NString str, unsigned int minimumCapacity){

        while(cast(str)->capacity < minimumCapacity) {
            char *tempData = (char*) realloc(cast(str)->data, cast(str)->capacity * RESIZE_MODIFIER);
            if (!tempData) return FAILURE;
            cast(str)->data = tempData;
            cast(str)->capacity *= RESIZE_MODIFIER;
        }
        return SUCCESS;
}

void nstr_destroy(NString *str){
    if(!str || !*str) return;

    free(cast(*str)->data);
    free(*str);
    *str = NULL;
}
