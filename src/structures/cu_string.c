#include "cu_string.h"
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define cast(x) ((NSTRING*)(x))
#define RESIZE_MODIFIER 2

typedef struct _nstring{
    unsigned int length;
    unsigned int capacity;
    char *data;
} NSTRING;



NString cu_nstirng_init(){
    return nstr_initialize_cstr("");
}

NString cu_nstirng_init_cstr(const char *c_str){
    int length = strlen(c_str);
    NSTRING *str = (NSTRING*) cu_nstirng_init_capacity(
            length < NSTRING_DEFAULT_CAPACITY ? NSTRING_DEFAULT_CAPACITY : length + 1);
    if(!str) return NULL;

    memcpy(str->data, c_str, length);

    str->length = length;

    return (NString) str;
}

NString cu_nstirng_init_capacity(unsigned int capacity){
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

NString cu_nstring_init_char(char c){
    NSTRING *str = (NSTRING*) cu_nstirng_init_capacity(NSTRING_DEFAULT_CAPACITY);
    if(!str) return NULL;

    *(str->data) = c;
    str->length++;

    return (NString) str;
}

NString cu_nstring_init_nstring(const NString copy){
    return cu_nstring_substring(copy, 0, cu_nstring_length(copy));
}

NString cu_nstring_substring(const NString str, unsigned int a, unsigned int b){
    if(a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    if(!str || a >= cast(str)->length || b > cast(str)->length)
        return NULL;

    NSTRING *substr = cast(cu_nstirng_init_capacity(b - a));
    NSTRING *orgstr = cast(str);

    memcpy(substr->data, orgstr->data, substr->capacity);

    substr->length = substr->capacity;

    return (NString) substr;
}

Status cu_nstring_concat_char(NString str, char c){
    if(!str) return FAILURE;

    return SUCCESS;
}


Status cu_nstring_concat_cstr(NString str, const char *cstr){
    if(!str || !cstr) return FAILURE;

    unsigned int length = strlen(cstr);
    if(!cu_nstring_resize(cast(str), cast(str)->length + length))
        return FAILURE;

    memcpy(cast(str)->data + cast(str)->length, cstr, length);

    cast(str)->length += length;

    return SUCCESS;
}


Status cu_nstring_concat_nstring(NString left, const NString right){
    if(left == NULL || right == NULL)
        return FAILURE;

    if(!cu_nstring_resize(cast(left), cast(left)->length + cast(right)->length))
        return FAILURE;

    memcpy(cast(left)->data + cast(left)->length, cast(right)->data, cast(right)->length);
    cast(left)->length += cast(right)->length;

    return SUCCESS;
}


char* cu_nstring_cstr(NString str){
    if(!str) return NULL;

    if(!cu_nstring_resize(cast(str), cast(str)->length + 1)) return NULL;

    cast(str)->data[cast(str)->length] = '\0';

    return cast(str)->data;
}


Boolean cu_nstring_contains(const NString str1, const NString str2){
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

Status cu_nstring_print(const NString str, FILE* file){
    if(!str || !file)
        return FAILURE;

    fwrite(cast(str)->data, 1, cast(str)->length, file);

    return SUCCESS;
}

int cu_nstring_cmp(const NString str1, const NString str2){
    //NULL check for str1 is covered from the function calls
    char *cstr1 = cu_nstring_cstr(str1);
    char *cstr2 = cu_nstring_cstr(str2);

    if(!cstr1 || !cstr2)
        return INT_MAX;
    return strcmp(cstr1, cstr2);
}

int cu_nstring_getChar(const NString str, unsigned int index){
    if(!str || index >= cast(str)->length)
        return -1;

    return cast(str)->data[index];
}

Status cu_nstring_setChar(NString str, char c, unsigned int index){
    if(!str || index >= cast(str)->length) return FAILURE;

    cast(str)->data[index] = c;

    return SUCCESS;
}

int cu_nstring_length(const NString str) {
    if(!str) return -1;
    return cast(str)->length;
}


Status cu_nstring_resize(NString str, unsigned int minimumCapacity){

        while(cast(str)->capacity < minimumCapacity) {
            char *tempData = (char*) realloc(cast(str)->data, cast(str)->capacity * RESIZE_MODIFIER);
            if (!tempData) return FAILURE;
            cast(str)->data = tempData;
            cast(str)->capacity *= RESIZE_MODIFIER;
        }
        return SUCCESS;
}

void cu_nstring_destroy(NString *s){
    if(!s || !*s) return;

    free(cast(*s)->data);
    free(*s);
    *s = NULL;
}
