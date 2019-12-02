#include "cu_tests.h"
#include <stdlib.h>

#define cast(x) ((struct unit_tests*)(x))
#define ERROR_BUFFER_LENGTH 1028
#define INITIAL_FUNCTION_CAPACITY 8
#define UT_VERSION 0.30


typedef struct unit_tests{
	FILE *output;
	ArrayList functions;
	char *errorMessage;
	Boolean initError;

	//contains all the indices of the tests that failed after ut_test run
	ArrayList results;
} unit_tests;


UnitTests ut_init(){
	struct unit_tests *ut = (struct unit_tests*) malloc(sizeof(unit_tests));
	if(!ut) return NULL;

	ut->errorMessage = calloc(sizeof(char), ERROR_BUFFER_LENGTH);
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

	ut->functions = cu_arraylist_init(sizeof(Status (*)(char *, unsigned int)), INITIAL_FUNCTION_CAPACITY);
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
	

void ut_setOutput(UnitTests ut, FILE* file){
	if(!ut || !file) return;

	cast(ut)->output = file;
}


void ut_addTest(UnitTests ut, Status(*function)(char*,unsigned int)){
	if(!ut || !function || cast(ut)->initError == TRUE)
		return;
	
	if(!cu_arraylist_append(cast(ut)->functions, (byte *) &function)){
		cast(ut)->initError = TRUE;		
		return;
	}

	cast(ut)->initError = FALSE;
}
		
Status ut_test(UnitTests unitTests){
	struct unit_tests *ut = cast(unitTests);
	if(!ut){
		fprintf(stderr, "Unitests passed as NULL\n");
		return FAILURE;
	}

	if(ut->initError){
		fprintf(stderr, "Unitests initialization error");
		return FAILURE;
	}
    cu_arraylist_clear(ut->results);

	int funcCount = cu_arraylist_size(ut->functions);
	Status(**functions)(char*, unsigned int) = (Status(**)(char*, unsigned int)) cu_arraylist_viewRaw(ut->functions);

	if(funcCount <= 0){
		fprintf(ut->output, "No functions found.\n");
		return FAILURE;
	}

	fprintf(ut->output, "\nUnit Tests Version %.2f\n", UT_VERSION);
	fprintf(ut->output, "Beginning %d tests...\n", funcCount);
	int failed = 0;
	for(int i = 0; i < funcCount; i++){
		//gets and casts the function
		//runs the function and tests for errors
		Status result =  functions[i](ut->errorMessage, ERROR_BUFFER_LENGTH);

		if(cu_arraylist_append(ut->results, (byte *) &result) == FAILURE)
			return FAILURE;
		if(result == FAILURE){
			fprintf(ut->output, "\tTest %d failed...\n", i);
			fprintf(ut->output, "\t%s\n", ut->errorMessage);
			fprintf(ut->output, "...continuing...\n");
			failed++;
		}
	}

	fprintf(ut->output, "...%d/%d tests passed.\n\n",  funcCount - failed, funcCount);

	if(failed == 0)
		return SUCCESS;

	return FAILURE;
}

ArrayList ut_results(UnitTests ut){
	if(!ut) 
		return NULL;
	return cast(ut)->results;
	
}

void ut_destroy(UnitTests* p_ut){
	if(!p_ut || !*p_ut)
		return;

    cu_arraylist_destroy(&cast(*p_ut)->results);
	free(cast(*p_ut)->errorMessage);
    cu_arraylist_destroy(&cast(*p_ut)->functions);
	*p_ut = NULL;
}

