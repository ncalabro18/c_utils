#include <string.h>
#include "structures/cu_arraylist.h"
#include "cu_tests.h"

Status testfunc_arraylist1(char * buffer, unsigned int length);
Status testfunc_arraylist2(char * buffer, unsigned int length);
Status testfunc_arraylist3(char * buffer, unsigned int length);


int main(){

	CUTests t = cu_tests_init();

	cu_tests_addTest(t, testfunc_arraylist1);	
	cu_tests_addTest(t, testfunc_arraylist2);
	cu_tests_addTest(t, testfunc_arraylist3);
	
	cu_tests_test(t);

	cu_tests_destroy(&t);

	return 0;
}


Status testfunc_arraylist1(char * buffer, unsigned int length){

	CUArrayList list = cu_arraylist_init(sizeof(int), 3);

	if(list == NULL){
		strcpy(buffer, "arraylist1: init");
		return FAILURE;
	}
	


	int data[] = {-2, 17, -43, -4, 36, 25, 29, -5, 2, 3, 7};
	
	unsigned int count = sizeof(data) / sizeof(int);
	
	for(unsigned int i = 0; i < count; i++){
		if(cu_arraylist_set(list, (byte*) &data[i], i) == FAILURE){
			strcpy(buffer, "arraylist1: set FAILURE");
			return FAILURE;
		}
	}
	
	if(cu_arraylist_size(list) != count){
	 	strcpy(buffer, "arraylist1: size != cout");      
		return FAILURE;
	}
	
	for(unsigned int i = 0; i < count; i++){
		byte *ret = cu_arraylist_get(list, i);
		if(ret == NULL){
			strcpy(buffer, "arraylist1: get returned NULL");
		       	return FAILURE;
		}
		if(*((int*)ret) != data[i]){
			strcpy(buffer, "arraylist1: get return not equal");			
			return FAILURE;	
		}
	}

	cu_arraylist_destroy(&list);
	return SUCCESS;
}

Status testfunc_arraylist2(char * buffer, unsigned int length){

	CUArrayList list = cu_arraylist_init(sizeof(char), 2);
	CUString str = cu_string_init("hello, world\n");

	int str_len = cu_string_length(str);
	if(str_len < 0){
		strcpy(buffer, "arraylist2: str_len < 0");
		return FAILURE;
	}

	for(int i = 0; i < str_len; i++){
		int c = cu_string_getChar(str, (unsigned int) i);
		if(cu_arraylist_append(list, (byte*) &c) == FAILURE){
			strcpy(buffer, "arraylist2: cu_arraylist_append failure");
			return FAILURE;
		}
	}

	for(int i = 0; i < str_len; i++){
		char *c = cu_arraylist_get(list, i);
		if(c == FAILURE){
			strcpy(buffer, "arraylist2: cu_arraylist_get NULL return");
			return FAILURE;
		}
		if(*c != cu_string_getChar(str, i)){
			strcpy(buffer, "arraylist2: *c != cu_string_charAt");
			return FAILURE;
		}
	}

	cu_arraylist_destroy(&list);
	cu_string_destroy(&str);

	return SUCCESS;
}


Status testfunc_arraylist3(char * buffer, unsigned int length){


	int array[] = {10, -2, 6, 12, 7, 7, 72, 55, -3, -4, 96, -41, -83};
	unsigned int arrayCount = sizeof(array) / sizeof(int);

	
	CUArrayList list = cu_arraylist_init(sizeof(int), 1);


	for(unsigned int i = 0; i < arrayCount; i++){
		if(cu_arraylist_append(list, (byte*) &array[i]) == FAILURE){
			strcpy(buffer, "arraylist3: cu_arraylist_append FAILURE");
			return FAILURE;
		}
	}

	int preNum = -223;
	if(cu_arraylist_prepend(list, (byte*) &preNum) == FAILURE){
		strcpy(buffer, "arraylist3: cu_arryalist_prepend FAILURE");
		return FAILURE;
	}
	for(unsigned int i = 1; i < (1 + arrayCount); i++){
		int *num = (int*) cu_arraylist_get(list, i);
		if(num == NULL){
			strcpy(buffer, "arraylist3: cu_arraylist_get NULL");
			return FAILURE;
		}
		if(*num != array[i - 1]){
			strcpy(buffer, "arraylist3: *num != array[i - 1]");
			return FAILURE;
		}
		
	}


	int *num = (int*) cu_arraylist_get(list, 0);
	if(num == NULL){
		strcpy(buffer, "arraylist3: cu_arraylist_get NULL @ 0");
		return FAILURE;
	}
	if(*num != preNum){
		strcpy(buffer, "arraylist3: *num != preNum");
	}

	cu_arraylist_destroy(&list);

	return SUCCESS;
}
