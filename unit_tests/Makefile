CC = gcc
FLAGS = -Wall -g -I../src libcu_utils.a
LINK = libcu_utils.a
TESTS = test_sort test_queue test_string test_arraylist test_stack test_merge test_heap test_hashmap test

test: test.c libcu_utils.a
	$(CC $(FLAGS) test.c -o test $(LINK)

test_merge: test_merge.c libcu_utils.a
	$(CC) $(FLAGS) test_merge.c -o test_merge $(LINK)

test_heap: test_heap.c libcu_utils.a
	$(CC) $(FLAGS) test_heap.c -o test_heap $(LINK)

test_sort: test_sort.c libcu_utils.a
	$(CC) $(FLAGS) test_sort.c -o test_sort $(LINK)

test_stack: test_stack.c libcu_utils.a
	$(CC) $(FLAGS) test_stack.c -o test_stack $(LINK)

test_queue: test_queue.c libcu_utils.a
	$(CC) $(FLAGS) test_queue.c -o test_queue $(LINK)

test_string: test_string.c libcu_utils.a
	$(CC) $(FLAGS) test_string.c -o test_string $(LINK)

test_arraylist: test_arraylist.c libcu_utils.a
	$(CC) $(FLAGS) test_arraylist.c -o test_arraylist $(LINK)

test_hashmap: test_hashmap.c libcu_utils.a
	$(CC) $(FLAGS) test_hashmap.c -o test_hashmap $(LINK)

../src/libcu_utils.a:
	cd ../src && make libcu_utils.a && make clean

libcu_utils.a:
	cp ../src/libcu_utils.a libcu_utils.a 


clean:
	rm $(TESTS) libcu_utils.a
