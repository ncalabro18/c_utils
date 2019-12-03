#include "cu_tests.h"
#include <stdlib.h>

#define cast(x) ((struct CU_TESTS*)(x))
#define CU_TESTS_ERROR_BUFFER_LENGTH 1028
#define CU_TESTS_INITIAL_FUNCTION_CAPACITY 8
#define CU_TESTS_VERSION 0.30


typedef struct CU_TESTS{
	FILE *output;
	CUArrayList functions;
	char *errorMessage;
	Boolean initError;

	//contains all the indices of the tests that failed after cu_tests_test run
	CUArrayList results;
} CU_TESTS;


CUTests cu_tests_init(){
	CU_TESTS *ut = (struct CU_TESTS*) malloc(sizeof(CU_TESTS));
	if(!ut) return NULL;

	ut->errorMessage = calloc(sizeof(char), CU_TESTS_ERROR_BUFFER_LENGTH);
	if(!ut->errorMessage){
		free(ut);
		return NULL;
	}
	

	ut->results = cu_arraylist_init(sizeof(Status), 10);
	if(!ut->results){
		free(ut->errorMessage);
		free(ut);
		return NULL;
	}

	ut->functions = cu_arraylist_init(sizeof(Status (*)(char *, unsigned int)), CU_TESTS_INITIAL_FUNCTION_CAPACITY);
	if(!ut->functions){
        cu_arraylist_destroy(&ut->results);
		free(ut->errorMessage);
		free(ut);
		return NULL;
	}

		
	ut->output = stdout;
	ut->initError = FALSE;
	return ut;
}
	

void cu_tests_setOutput(CUTests ut, FILE* file){
	if(!ut || !file) return;

	cast(ut)->output = file;
}


void cu_tests_addTest(CUTests ut, Status(*function)(char*, unsigned int)){
	if(!ut || !function || cast(ut)->initError == TRUE)
		return;
	
	if(!cu_arraylist_append(cast(ut)->functions, (byte *) &function)){
		cast(ut)->initError = TRUE;		
		return;
	}

	cast(ut)->initError = FALSE;
}
		
Status cu_tests_test(CUTests t){
	struct CU_TESTS *ut = cast(t);
	if(!ut){
		fprintf(stderr, "CUTests passed as NULL\n");
		return FAILURE;
	}

	if(ut->initError){
		fprintf(stderr, "CUTests initialization error\n");
		return FAILURE;
	}
    	cu_arraylist_clear(ut->results);

	int funcCount = cu_arraylist_size(ut->functions);
	Status(**functions)(char*, unsigned int) = (Status(**)(char*, unsigned int)) cu_arraylist_viewRaw(ut->functions);

	if(funcCount <= 0){
		fprintf(ut->output, "No functions found.\n");
		return FAILURE;
	}




	fprintf(ut->output, "\nCUTests Version %.2f\n", CU_TESTS_VERSION);
	fprintf(ut->output, "Beginning %d tests...\n", funcCount);
	int failed = 0;
	for(int i = 0; i < funcCount; i++){
		//gets and casts the function
		//runs the function and tests for errors
		Status result =  functions[i](ut->errorMessage, CU_TESTS_ERROR_BUFFER_LENGTH);

		if(cu_arraylist_append(ut->results, (byte *) &result) == FAILURE)
			return FAILURE;
		if(result == FAILURE){
			fprintf(ut->output, "\tTest %d failed\n", i);
			if(ut->errorMessage[0] == '\0')
				fprintf(ut->output, "\tNo error message");
			fprintf(ut->output, "\t%s\n", ut->errorMessage);
			fprintf(ut->output, "\tcontinuing...\n");
			failed++;
		}
	}

	if(failed == 0) fputc('\n', ut->output);

	fprintf(ut->output, "...%d/%d tests passed.\n\n",  funcCount - failed, funcCount);

	if(failed == 0)
		return SUCCESS;

	return FAILURE;
}

CUArrayList cu_tests_results(CUTests t){
	if(!t)
		return NULL;
	return cast(t)->results;
}

void cu_tests_destroy(CUTests* pt){
	if(!pt || !*pt)
		return;

    cu_arraylist_destroy(&cast(*pt)->results);
	free(cast(*pt)->errorMessage);
    cu_arraylist_destroy(&cast(*pt)->functions);
	*pt = NULL;
}

