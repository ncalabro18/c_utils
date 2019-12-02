CC = gcc
FLAGS = -Wall -g
OBJECTS = c_utils.o unit_tests.o arraylist.o queue.o
TESTS = test_sort test_nstring test_queue


test_sort: $(OBJECTS) test_sort.c
	$(CC) $(FLAGS) $(OBJECTS) test_sort.c -o test_sort

test_nstring: $(OBJECTS) test_nstring.c
	$(CC) $(FLAGS) $(OBJECTS) test_nstring.c -o test_nstring

test_queue: $(OBJECTS) test_queue.c
	$(CC) $(FLAGS) $(OBJECTS) test_queue.c -o test_queue


c_utils.o: ../c_utils.c
	$(CC) $(FLAGS) -c ../c_utils.c -o c_utils.o

unit_tests.o: ../unit_tests/unit_tests.c
	$(CC) $(FLAGS) -c ../unit_tests/unit_tests.c -o unit_tests.o

arraylist.o: ../structures/arraylist.c
	$(CC) $(FLAGS) -c ../structures/arraylist.c -o arraylist.o

nstring.o: ../structures/nstring.c
	$(CC) $(FLAGS) -c ../structures/nstring.c -o ntring.o

queue.o: ../structures/queue.c
	$(CC) $(FLAGS) -c ../structures/queue.c -o queue.o

clean:
	rm $(OBJECTS) $(TESTS)
