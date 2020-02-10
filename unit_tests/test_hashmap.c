#include <structures/cu_hashmap.h>
#include <cu_tests.h>

Status testfunc_hashmap1(CUTests t);

int hs_int(byte* key);

int main(void){

	CUTests t = cu_tests_init();

	cu_tests_addTest(t, testfunc_hashmap);
	
	cu_tests_test(t);

	cu_tests_destroy(&t);

	return 0;
}


Status testfunc_hashmap1(CUTests t){
	
	CUHashMap map = cu_hashmap_init(10, sizeof(int), sizeof(int), hs_int);
	int k, v;
	int data[] = {
		100, 55,
	       	201, 221,
	       	302, 99,
	       	403, 65,
	       	504, 1625,
	       	605, 0x625,
	       	706, 6255,
	       	807, 0x1625,
	       	908, 65251,
	       	1000, 6252151,
	       	1100, 6252151,
	       	1200, 625251,
	       	1300, 6252151,
	       	1400, 21,
	       	1500, 252151,
	       	1600, 2252151,
	       	1700, 6252151,
	       	1005, 46252151,
	       	1805, 2252151,
	       	1905, 62521751,
	       	2000, 6252151,
	       	2100, 62151,
	       	22014, 62151,
	       	23015, 2152151,
	       	2408, 252151,
	       	25016, 521510,
	       	26016, 72352151,
	       	27016, 62521351,
	       	28016, 625241,
	       	29016, 987123,
	       	29017, 9817235,
	       	29018, 12482,
	       	29019, 161352,
	       	29011, 8762135,
	       	29012, 0x62522,
	       	29013, 62522
	};
	int data_length = sizeof(data) / sizeof(int) / 2;

	for(int i = 0; i < data_length; i++){	
		k = data[i * 2], v = data[i * 2 + 1];
		if(cu_hashmap_push(map, (byte*) &k, (byte*) &v) == FAILURE){
			cu_tests_log_cstr(t, "hashmap_push == FAILURE");
			return FAILURE;
		}

		byte* peek_ret = cu_hashmap_peek(map, (byte*) &k);
		if(peek_ret == NULL){
			cu_tests_log_cstr(t, "peek_ret == NULL");
			return FAILURE;
		}
		if(v != *((int*)peek_ret)){
			cu_tests_log_cstr(t, "v != *peek_ret");
			cu_tests_log_newline(t);
			cu_tests_log_cstr(t, "i = ");
			cu_tests_log_int(t, i);
			return FAILURE;
		}
	}

	cu_hashmap_destroy(&map);
	return SUCCESS;;
}

Status testfunc_hashmap2(CUTests t){
	int length = 1000;


	return SUCCESS;
}

int hs_int(byte* key){
	return *((int*)key);
}


}

Status testfunc_hashmap2(CUTests t){

	
	return SUCCESS;
}

int hs_int(byte* key){
	return *((int*)key);
}


