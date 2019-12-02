#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#include <stdio.h>
#include "cu_utils.h"
#include "structures/cu_arraylist.h"

typedef void* UnitTests;

UnitTests ut_init();

void ut_setOutput(UnitTests, FILE*);

void ut_addTest(UnitTests, Status(*function)(char*,unsigned int));
		
Status ut_test(UnitTests);

ArrayList ut_results(UnitTests);

void ut_destroy(UnitTests*);

#endif
