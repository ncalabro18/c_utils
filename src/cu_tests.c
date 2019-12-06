#include "cu_tests.h"
#include <stdlib.h>

#define cast(x) ((struct CU_TESTS*)(x))
#define CU_TESTS_INITIAL_FUNCTION_CAPACITY 8
#define CU_TESTS_VERSION 0.30


typedef struct CU_TESTS{
	FILE *output;
	CUArrayList functions;
	CUString errorLog;

	//contains all the indices of the tests that failed after cu_tests_test run
	CUArrayList results;

	Boolean initError;
} CU_TESTS;


CUTests cu_tests_init(){
	CU_TESTS *ut = (struct CU_TESTS*) malloc(sizeof(CU_TESTS));
	if(!ut) return NULL;


	ut->errorLog = cu_string_init_capacity(1 << 10);
	if(!ut->errorLog){
		free(ut);
		return NULL;
	}
	

	ut->results = cu_arraylist_init(sizeof(Status), 10);
	if(!ut->results){
		cu_string_destroy(&ut->errorLog);
		free(ut);
		return NULL;
	}

	ut->functions = cu_arraylist_init(sizeof(Status (*)(char *, unsigned int)), CU_TESTS_INITIAL_FUNCTION_CAPACITY);
	if(!ut->functions){
        cu_arraylist_destroy(&ut->results);
		cu_string_destroy(&ut->errorLog);
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


void cu_tests_addTest(CUTests ut, Status(*function)(CUTests)){
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
		perror("CUTests passed as NULL\n");
		return FAILURE;
	}
	if(ut->initError){
		perror("CUTests initialization error\n");
		return FAILURE;
	}
    	if(cu_arraylist_clear(ut->results) == FAILURE){
		perror("CUTests cu_arraylist_clear FAILURE");
		return FAILURE;
	}


	int funcCount = cu_arraylist_size(ut->functions);
	Status(**functions)(CUTests) = (Status(**)(CUTests)) cu_arraylist_viewRaw(ut->functions);

	if(funcCount <= 0){
		fprintf(ut->output, "No functions found.\n");
		return FAILURE;
	}


	fprintf(ut->output, "\nCUTests Version %.2f\n", CU_TESTS_VERSION);
	fprintf(ut->output, "Beginning %d tests...\n", funcCount);

	//runs all the functions
	int failed = 0;
	for(int i = 0; i < funcCount; i++){
		cu_string_clear(ut->errorLog);

		Status result =  functions[i]((CUTests) ut );

		if(cu_arraylist_append(ut->results, (byte *) &result) == FAILURE)
			return FAILURE;
		if(result == FAILURE){
			fprintf(ut->output, "\t<Test %d>: Failed\n", i);
			if(cu_string_length(ut->errorLog) > 0){
				fprintf(ut->output, "\t<Test %d>: %s\n", i, cu_string_cstr(ut->errorLog));
			}
			else
				fprintf(ut->output, "\t<Test %d>: No error log\n", i);
			fprintf(ut->output, "\t<Test %d>: Continuing...\n", i);
			failed++;
		}
	}

	if(failed == 0) fputc('\n', ut->output);

	fprintf(ut->output, "...%d/%d tests passed.\n\n",  funcCount - failed, funcCount);

	if(failed == 0){
		fprintf(ut->output, "Nice!\n");
		return SUCCESS;
	}

	return FAILURE;
}

void cu_tests_log(CUTests t, const char *msg){
	if(!t || !msg) return;

	if(cu_string_concat_cstr(cast(t)->errorLog, msg) == FAILURE){
		perror("cu_tests_log: cu_string_concat_cstr FAILURE");
		exit(-1);
	}
}


CUArrayList cu_tests_results(CUTests t){
	if(!t)
		return NULL;
	return cast(t)->results;
}

void cu_tests_destroy(CUTests* pt){
	if(!pt || !*pt)
		return;

	cu_string_destroy(&cast(*pt)->errorLog);
 	cu_arraylist_destroy(&cast(*pt)->results);
    	cu_arraylist_destroy(&cast(*pt)->functions);
	free(*pt);
	*pt = NULL;
}

