CC = gcc
FLAGS = -Wall -g -I../src libcu_utils.a
LINK = libcu_utils.a
TESTS = test_sort test_queue test_string test_arraylist test_stack test

test: test.c libcu_utils.a
	$(CC $(FLAGS) test.c -o test $(LINK)

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

../src/libcu_utils.a:
	cd ../src && make libcu_utils.a && make clean

libcu_utils.a:
	cp ../src/libcu_utils.a libcu_utils.a 


clean:
	rm $(TESTS) libcu_utils.a
