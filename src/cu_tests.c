#include "cu_tests.h"
#include <stdlib.h>

#define cast(x) ((struct CU_TESTS*)(x))
#define CU_TESTS_INITIAL_FUNCTION_CAPACITY 8
#define CU_TESTS_VERSION 0.30

void clearbuffer(FILE *f);

typedef struct CU_TESTS{
	FILE *input;
	FILE *output;
	CUArrayList functions;
	CUString errorLog;

	CUArrayList results;

	Boolean initError;

	int currentTest;
} CU_TESTS;


CUTests cu_tests_init(){
	CU_TESTS *ut = (struct CU_TESTS*) malloc(sizeof(CU_TESTS));
	if(!ut) return NULL;

	//1 << 10 ~= 1000
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

		
	ut->input = stdin;
	ut->output = stdout;
	ut->currentTest = -1;
	ut->initError = FALSE;
	return ut;
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
	if(funcCount <= 0){
		perror("No functions found.\n");
		return FAILURE;
	}
	Status(**functions)(CUTests) = (Status(**)(CUTests)) cu_arraylist_viewRaw(ut->functions);


	fprintf(ut->output, "\nCUTests Version %.2f\n", CU_TESTS_VERSION);
	fprintf(ut->output, "Beginning %d tests...\n", funcCount);

	//runs all the functions
	int failed = 0;
	for(ut->currentTest = 0; ut->currentTest < funcCount; ut->currentTest++){
		cu_string_clear(ut->errorLog);

		Status result =  functions[ut->currentTest] ((CUTests) ut );

		if(cu_arraylist_append(ut->results, (byte *) &result) == FAILURE)
			return FAILURE;
		if(result == FAILURE){
			fprintf(ut->output, "\t<Test %d>: Failed\n", ut->currentTest);
			if(cu_string_length(ut->errorLog) > 0){
				fprintf(ut->output, "\t<Test %d>: %s\n", ut->currentTest, cu_string_cstr(ut->errorLog));
			}
			else
				fprintf(ut->output, "\t<Test %d>: No error log\n", ut->currentTest);
			fprintf(ut->output, "\t<Test %d>: Continuing...\n", ut->currentTest);
			failed++;
		}
	}

	if(failed == 0) fputc('\n', ut->output);

	fprintf(ut->output, "...%d/%d tests passed.\n",  funcCount - failed, funcCount);


	fprintf(ut->output, "\n");
	return FAILURE;
}

void cu_tests_log(CUTests t){
	if(!t) return;

	cu_string_print(cast(t)->errorLog, cast(t)->output);
	cu_tests_log_clear(t);
}

void cu_tests_log_custring(CUTests t, CUString str){
	if(!t || !str) return;

	if(cu_string_concat_custring(cast(t)->errorLog, str) == FAILURE)
		perror("cu_tests_log_custring: cu_string_concat_custring FAILURE");
}
void cu_tests_log_cstr(CUTests t, const char *msg){
	if(!t || !msg) return;

	if(cu_string_concat_cstr(cast(t)->errorLog, msg) == FAILURE){
		perror("cu_tests_log: cu_string_concat_cstr FAILURE");
		exit(-2);
	}
}

void cu_tests_log_int(CUTests t, int num){
	if(!t) return;
	CUString s = cu_string_init_int(num);
	if(cu_string_concat_custring(cast(t)->errorLog, s) == FAILURE){
		perror("cu_tests_log_int: cu_string_concat_cstr FAILURE");
		exit(-2);
	}
	cu_string_destroy(&s);
}
void cu_tests_log_uint(CUTests t, unsigned int num){
	if(!t) return;
	CUString s = cu_string_init_uint(num);
	if(cu_string_concat_cstr(cast(t)->errorLog, s) == FAILURE){
		perror("cu_tests_log_uint: cu_string_concat_cstr FAILURE");
		exit(-2);
	}
	cu_string_destroy(&s);
}

void cu_tests_log_char(CUTests t, char c){
	if(!t) return;	
	if(cu_string_concat_char(cast(t)->errorLog, c) == FAILURE){
		perror("cu_tests_log_char: cu_string_concat_char FAILURE");
		exit(-2);
	}
}
void cu_tests_log_float(CUTests t, float num){
	if(!t) return;
	CUString s = cu_string_init_float(num);
	if(cu_string_concat_custring(cast(t)->errorLog, s) == FAILURE){
		perror("cu_tests_log_float: cu_string_concat_custring");
		exit(-2);
	}
	cu_string_destroy(&s);
}
void cu_tests_log_double(CUTests t, double num){
	if(!t) return;
	CUString s = cu_string_init_double(num);
	if(cu_string_concat_custring(cast(t)->errorLog, s) == FAILURE){
		perror("cu_tests_log_float: cu_string_concat_custring");
		exit(-2);
	}
	cu_string_destroy(&s);
}

void cu_tests_log_newline(CUTests t){
	if(!t) return;
	cu_tests_log_cstr(t, "\n\t<Test ");
	cu_tests_log_uint(t, cast(t)->currentTest);
	cu_tests_log_cstr(t, ">: ");
}

void cu_tests_log_clear(CUTests t){
	if(!t) return;
	cu_string_clear(cast(t)->errorLog);
}

Status cu_tests_log_verify(CUTests t){
	if(!t) return FAILURE;
	cu_tests_log(t);
	while(1){
		cu_tests_log_newline(t);
		cu_tests_log_cstr(t, "veriy( y/n or s/f ): ");
		cu_tests_log(t);
	
		int c = fgetc(cast(t)->input);
		clearbuffer(cast(t)->input);
		if(c != 'y' && c != 'Y' && c != 'n' && c != 'N' &&
		   c != 's' && c != 'S' && c != 'f' && c != 'F')
			continue;

		return (c == 'y' || c == 'Y' || c == 's' || c == 'S') ? SUCCESS : FAILURE;
	}

	return FAILURE;
}


CUArrayList cu_tests_results(CUTests t){
	if(!t)
		return NULL;
	return cast(t)->results;
}

void cu_tests_setOutput(CUTests ut, FILE* file){
	if(!ut || !file) return;
	cast(ut)->output = file;
}
void cu_tests_setInput(CUTests ut, FILE* file){
	if(!ut || !file) return;
	cast(ut)->input = file;
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

void clearbuffer(FILE *f){
	while(fgetc(f) != '\n') {}
}
