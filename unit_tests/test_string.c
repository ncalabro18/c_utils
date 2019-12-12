#include "cu_tests.h"
#include "structures/cu_string.h"
#include <string.h>


Status testfunc_string_init_int1(CUTests t);
Status testfunc_string_init_int2(CUTests t);
Status testfunc_string_init_uint1(CUTests t);
Status testfunc_string_setSegment(CUTests t);
Status testfunc_string_cmp(CUTests t);
Status testfunc_string_substring(CUTests t);
Status testfunc_string_concat(CUTests t);

int main(void){

	CUTests tests = cu_tests_init();

	
	cu_tests_addTest(tests, testfunc_string_setSegment);
	cu_tests_addTest(tests, testfunc_string_cmp);
	cu_tests_addTest(tests, testfunc_string_substring);
  	cu_tests_addTest(tests, testfunc_string_concat);
	cu_tests_addTest(tests, testfunc_string_init_int1);
	cu_tests_addTest(tests, testfunc_string_init_int2);
	cu_tests_addTest(tests, testfunc_string_init_uint1);
	 

	cu_tests_test(tests);

	cu_tests_destroy(&tests);


	return 0;
}


Status testfunc_string_init_int1(CUTests t){


	CUString s1 = cu_string_init_int(5);
	CUString s2 = cu_string_init_int(572);
	CUString s3 = cu_string_init_int(65);
	CUString s4 = cu_string_init_int(22);
	CUString s5 = cu_string_init_int(1);
	CUString s6 = cu_string_init_int(78653);
	CUString s7 = cu_string_init_int(928142);


	cu_tests_log_cstr(t, "s1:");

	if(cu_string_getChar(s1, 0) != '5') return FAILURE;

	cu_tests_log_cstr(t, "s2:");
	cu_tests_log_cstr(t, cu_string_cstr(s2));

	if(cu_string_getChar(s2, 0) != '5') return FAILURE;
	if(cu_string_getChar(s2, 1) != '7') return FAILURE;
	if(cu_string_getChar(s2, 2) != '2') return FAILURE;

	cu_tests_log_cstr(t, "s3:");

	if(cu_string_getChar(s3, 0) != '6') return FAILURE;
	if(cu_string_getChar(s3, 1) != '5') return FAILURE;

	cu_tests_log_cstr(t, "s4:");
	
	if(cu_string_getChar(s4, 0) != '2') return FAILURE;
	if(cu_string_getChar(s4, 1) != '2') return FAILURE;


	cu_tests_log_cstr(t, "s5:");

	if(cu_string_getChar(s5, 0) != '1') return FAILURE;

	cu_tests_log_cstr(t, "s6:");

	if(cu_string_getChar(s6, 0) != '7') return FAILURE;
	if(cu_string_getChar(s6, 1) != '8') return FAILURE;
	if(cu_string_getChar(s6, 2) != '6') return FAILURE;
	if(cu_string_getChar(s6, 3) != '5') return FAILURE;
	if(cu_string_getChar(s6, 4) != '3') return FAILURE;


	cu_tests_log_cstr(t, "s7:");

	if(cu_string_getChar(s7, 0) != '9') return FAILURE;
	if(cu_string_getChar(s7, 1) != '2') return FAILURE;
	if(cu_string_getChar(s7, 2) != '8') return FAILURE;
	if(cu_string_getChar(s7, 3) != '1') return FAILURE;
	if(cu_string_getChar(s7, 4) != '4') return FAILURE;
	if(cu_string_getChar(s7, 5) != '2') return FAILURE;


	cu_string_destroy(&s1);
	cu_string_destroy(&s2);
	cu_string_destroy(&s3);
	cu_string_destroy(&s4);
	cu_string_destroy(&s5);
	cu_string_destroy(&s6);
	cu_string_destroy(&s7);


	return SUCCESS;
}

Status testfunc_string_setSegment(CUTests t){
	if(!t) return FAILURE;
	CUString s1, compare;

	s1 = cu_string_init_cstr("hello, world");
	if(cu_string_setSegment(s1, 3, 6, "foobar") == FAILURE){
		cu_tests_log_cstr(t, "cu_string_setSegment FAILURE");
		return FAILURE;
	}
	compare = cu_string_init_cstr("helfoobar world");
	if(cu_string_cmp(s1, compare) != 0){
		cu_tests_log_cstr(t, "cu_string_cmp != 0");
		return FAILURE;
	}
	cu_string_destroy(&s1);
	cu_string_destroy(&compare);

	s1 = cu_string_init_cstr("test_[3]_test");
	if(cu_string_setSegment(s1, 5, 8, "hello, world") == FAILURE){
		cu_tests_log_cstr(t, "cu_string_setSegment FAILURE");
		return FAILURE;
	}
	compare = cu_string_init_cstr("test_hello, world_test");
	if(cu_string_cmp(s1, compare) != 0){
		cu_tests_log_cstr(t, "cu_string_cmp != 0");
		return FAILURE;
	}
	cu_string_destroy(&s1);
	cu_string_destroy(&compare);


	s1 = cu_string_init_cstr("1234567890");
	if(cu_string_setSegment(s1, 2, 8, "ar") == FAILURE){
		cu_tests_log_cstr(t, "cu_string_setSegment FAILURE");
		return FAILURE;
	}
	compare = cu_string_init_cstr("12ar90");
	if(cu_string_cmp(s1, compare) != 0){
		cu_tests_log_cstr(t, "cu_string_cmp != 0");
		return FAILURE;
	}

	cu_string_destroy(&s1);
	cu_string_destroy(&compare);

	return SUCCESS;
}

Status testfunc_string_cmp_helper(const char *a, const char *b){
    CUString str1 = cu_string_init_cstr(a);
    CUString str2 = cu_string_init_cstr(b);

    int n = cu_string_cmp(str1, str2);
    int c = strcmp(a, b);

    int returnVal = (c == n) ? SUCCESS : FAILURE;

    cu_string_destroy(&str1);
    cu_string_destroy(&str2);

    return returnVal;
}

Status testfunc_string_cmp(CUTests t){

    if(!testfunc_string_cmp_helper("","")) return FAILURE;
    if(!testfunc_string_cmp_helper("hello, world","hello, world")) return FAILURE;
    if(!testfunc_string_cmp_helper("jf8172o3md","jf7ha")) return FAILURE;
    if(!testfunc_string_cmp_helper("abcdefghijklmnopqrstuvwxyz","abcdefghijklmnopqrstuvwxyz")) return FAILURE;
    if(!testfunc_string_cmp_helper("asdf","asdf")) return FAILURE;
    if(!testfunc_string_cmp_helper("world, hello","world, he")) return FAILURE;
    if(!testfunc_string_cmp_helper("-+=_","-+=_")) return FAILURE;
    if(!testfunc_string_cmp_helper("hello","hello")) return FAILURE;
    if(!testfunc_string_cmp_helper("this seems excessive","this idk\n\t")) return FAILURE;
    if(!testfunc_string_cmp_helper("asdf","jkl;")) return FAILURE;

    return SUCCESS;
}

Status testfunc_string_substring_helper(CUTests t, const char *cstr, unsigned int a, unsigned int b){
	CUString str = cu_string_init_cstr(cstr);
	if(str == NULL){
		cu_tests_log_cstr(t, "cu_string_init_ctr NULL");
		return FAILURE;
	}

	CUString substr = cu_string_substring(str, a, b);
	if(substr == NULL){
		cu_tests_log_cstr(t, "cu_string_substring NULL");
		return FAILURE;
	}

	Status ret = SUCCESS;
	for(unsigned int i = a; i < b; i++){
		int charstr = cu_string_getChar(str, i);
		int charsub = cu_string_getChar(substr, i - a);

		if(charstr != charsub){
			cu_tests_log_cstr(t, ":Incorrect character found:");
			cu_tests_log_cstr(t, cstr);
			cu_tests_log_cstr(t, ":");
			cu_tests_log_cstr(t, cu_string_cstr(substr));
			ret = FAILURE;

			break;
		}
	}

	cu_string_destroy(&str);
	cu_string_destroy(&substr);
	return ret;
}

Status testfunc_string_substring(CUTests t){

    if(!testfunc_string_substring_helper(t, "hello, world", 3, 6)) return FAILURE;
    if(!testfunc_string_substring_helper(t, "jf8172o3md", 2, 5)) return FAILURE;
    if(!testfunc_string_substring_helper(t, "abcdefghijklmnopqrstuvwxyz", 17, 20)) return FAILURE;
    if(!testfunc_string_substring_helper(t, "asdf", 0, 3)) return FAILURE;
    if(!testfunc_string_substring_helper(t, "world, hello", 0, 1)) return FAILURE;
    if(!testfunc_string_substring_helper(t, "-+=_", 0, strlen("-+=_"))) return FAILURE;
    if(!testfunc_string_substring_helper(t, "hello", 2, 4)) return FAILURE;

    if(!testfunc_string_substring_helper(t, "kj4124j1f48171242o3md", 0, 9)) return FAILURE;

    return SUCCESS;
}


Status testfunc_string_concat_helper(CUTests t, const char *a, const char *b){
	CUString str1 = cu_string_init_cstr(a);
	CUString str2 = cu_string_init_cstr(b);
	
	int original_length = cu_string_length(str1);
	if(cu_string_concat_custring(str1, str2) == FAILURE){
		cu_tests_log_cstr(t, "cu_string_concat_custring FAILURE");
		return FAILURE;
	}
	
	int new_length = cu_string_length(str1);
	if(new_length < 0){
		cu_tests_log_cstr(t, "new_length < 0");
		return FAILURE;
	}
	for(int i = 0; i < original_length; i++)
		if(cu_string_getChar(str1, i) != a[i]){
			cu_tests_log_cstr(t, "cu_string_getChar(str1,i) != a[i]");
			return FAILURE;
		}
	for(int i = original_length; i < new_length; i++)
		if(cu_string_getChar(str1, i) != b[i - original_length]){		
			cu_tests_log_cstr(t, "cu_string_getChar(str1,i) != b[i]");
			return FAILURE;
		}
	cu_string_destroy(&str1);
	cu_string_destroy(&str2);
	return SUCCESS;
}


Status testfunc_string_concat(CUTests t){

    if(!testfunc_string_concat_helper(t, "","")) return FAILURE;
    if(!testfunc_string_concat_helper(t, "aljfl","")) return FAILURE;
    if(!testfunc_string_concat_helper(t, "","li721lkj")) return FAILURE;
    if(!testfunc_string_concat_helper(t, "hello, world","hello, world")) return FAILURE;
    if(!testfunc_string_concat_helper(t, "jf8172o3md","jf7ha")) return FAILURE;
    if(!testfunc_string_concat_helper(t, "abcdefghijklmnopqrstuvwxyz","abcdefghijklmnopqrstuvwxyz")) return FAILURE;
    if(!testfunc_string_concat_helper(t, "asdf","asdf")) return FAILURE;
    if(!testfunc_string_concat_helper(t, "world, hello","world, he")) return FAILURE;
    if(!testfunc_string_concat_helper(t, "-+=_","-+=_")) return FAILURE;
    if(!testfunc_string_concat_helper(t, "hello","hello")) return FAILURE;
    if(!testfunc_string_concat_helper(t, "this seems excessive","this idk\n\t")) return FAILURE;
    if(!testfunc_string_concat_helper(t, "asdf","jkl;")) return FAILURE;

    return SUCCESS;
}

Status testfunc_string_init_int_helper2(CUTests t, int test, const char *compareTo){
	if(!t || !compareTo) return FAILURE;
	CUString str_test = cu_string_init_int(test);
	if(str_test == NULL){
		cu_tests_log_cstr(t, "testfunc_string_init_int_helper: cu_string_init_int NULL");
		return FAILURE;
	}
	char *cstr_test = cu_string_cstr(str_test);
	if(cstr_test == NULL){
		cu_tests_log_cstr(t, "testfunc_string_init_int_helper: cu_string_cstr  NULL");       
		return FAILURE;
	}
	int result = strcmp(cstr_test, compareTo);
	if(result != 0){
		//normally would use log_int, but log_int relies on these tests
		cu_tests_log_cstr(t, "testfun_string_init_int_helper: result != 0");
		return FAILURE;
	}
	cu_string_destroy(&str_test);
	return SUCCESS;
}

Status testfunc_string_init_int2(CUTests t){

	 if(testfunc_string_init_int_helper2(t, 4, "4") == FAILURE) return FAILURE;
	 if(testfunc_string_init_int_helper2(t, -7, "-7") == FAILURE) return FAILURE;
	 if(testfunc_string_init_int_helper2(t, -671294, "-671294") == FAILURE) return FAILURE;
	 if(testfunc_string_init_int_helper2(t, 97562, "97562") == FAILURE) return FAILURE;
	 if(testfunc_string_init_int_helper2(t, 12345678, "12345678") == FAILURE) return FAILURE;
	 if(testfunc_string_init_int_helper2(t, -1, "-1") == FAILURE) return FAILURE;
	 if(testfunc_string_init_int_helper2(t, 0, "0") == FAILURE) return FAILURE;
	 if(testfunc_string_init_int_helper2(t, 9911552, "9911552") == FAILURE) return FAILURE;
	 if(testfunc_string_init_int_helper2(t, 771, "771") == FAILURE) return FAILURE;
	 if(testfunc_string_init_int_helper2(t, -2761, "-2761") == FAILURE) return FAILURE;
	 if(testfunc_string_init_int_helper2(t, 40285, "40285") == FAILURE) return FAILURE;	

	return SUCCESS;
}

Status testfunc_string_init_uint_helper1(CUTests t, unsigned int test, const char *compareTo){
	if(!t || !compareTo) return FAILURE;
	CUString str_test = cu_string_init_int(test);
	if(str_test == NULL){
		cu_tests_log_cstr(t, "testfunc_string_init_int_helper: cu_string_init_int NULL");
		return FAILURE;
	}
	char *cstr_test = cu_string_cstr(str_test);
	if(cstr_test == NULL){
		cu_tests_log_cstr(t, "testfunc_string_init_int_helper: cu_string_cstr  NULL");       
		return FAILURE;
	}
	int result = strcmp(cstr_test, compareTo);
	if(result != 0){
		//normally would use log_uint, but log_uint relies on these tests
		cu_tests_log_cstr(t, "testfun_string_init_int_helper: result != 0");
		return FAILURE;
	}
	cu_string_destroy(&str_test);
	return SUCCESS;
}


Status testfunc_string_init_uint1(CUTests t){

	 if(testfunc_string_init_uint_helper1(t, 4, "4") == FAILURE) return FAILURE;
	 if(testfunc_string_init_uint_helper1(t, 7, "7") == FAILURE) return FAILURE;
	 if(testfunc_string_init_uint_helper1(t, 671294, "671294") == FAILURE) return FAILURE;
	 if(testfunc_string_init_uint_helper1(t, 97562, "97562") == FAILURE) return FAILURE;
	 if(testfunc_string_init_uint_helper1(t, 12345678, "12345678") == FAILURE) return FAILURE;
	 if(testfunc_string_init_uint_helper1(t, 1, "1") == FAILURE) return FAILURE;
	 if(testfunc_string_init_uint_helper1(t, 0, "0") == FAILURE) return FAILURE;
	 if(testfunc_string_init_uint_helper1(t, 9911552, "9911552") == FAILURE) return FAILURE;
	 if(testfunc_string_init_uint_helper1(t, 771, "771") == FAILURE) return FAILURE;
	 if(testfunc_string_init_uint_helper1(t, 2761, "2761") == FAILURE) return FAILURE;
	 if(testfunc_string_init_uint_helper1(t, 771, "771") == FAILURE) return FAILURE;
	 if(testfunc_string_init_uint_helper1(t, 1271271, "1271271") == FAILURE) return FAILURE;
	 if(testfunc_string_init_uint_helper1(t, 237661, "237661") == FAILURE) return FAILURE;
	 if(testfunc_string_init_uint_helper1(t, 72661, "72661") == FAILURE) return FAILURE;

	 return SUCCESS;
}

