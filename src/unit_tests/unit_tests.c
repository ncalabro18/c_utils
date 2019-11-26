#include "unit_tests.h"
#include "../structures/arraylist.h"
#include <stdlib.h>

#define cast(x) ((struct unit_tests*)(x))
#define ERROR_BUFFER_LENGTH 1028
#define INITIAL_FUNCTION_CAPACITY 8
#define UT_VERSION 0.20

typedef struct unit_tests{
	FILE *output;
	ArrayList functions;
	char *errorMessage;
	Boolean initError;
} unit_tests;

UnitTests ut_init(){
	struct unit_tests *ut = (struct unit_tests*) malloc(sizeof(unit_tests));
	if(!ut) return NULL;

	ut->errorMessage = calloc(sizeof(char), ERROR_BUFFER_LENGTH);
	if(!ut->errorMessage){
		free(ut);
		return NULL;
	}
	
	ut->functions = al_initialize(sizeof(Status (*)(char*,unsigned int)),  INITIAL_FUNCTION_CAPACITY);
	if(!ut->functions){
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
	
	if(!al_append(cast(ut)->functions, (byte*)&function)){
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

	int funcCount = al_size(ut->functions);
	Status(**functions)(char*, unsigned int) = (Status(**)(char*, unsigned int)) al_viewRaw(ut->functions);

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
		if((functions[i]) (ut->errorMessage, ERROR_BUFFER_LENGTH) == FAILURE){
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

void ut_destroy(UnitTests* p_ut){
	if(!p_ut || !*p_ut)
		return;
	free(cast(*p_ut)->errorMessage);
	al_destroy(&cast(*p_ut)->functions);
	*p_ut = NULL;
}

