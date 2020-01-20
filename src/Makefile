CC = gcc
FLAGS = -Wall -g -lm -Wno-unused-function
OBJECTS = cu_utils.o cu_arraylist.o cu_string.o cu_queue.o cu_stack.o cu_tests.o cu_heap.o cu_hashmap.o
LIB = libcu_utils.a

$(LIB): $(OBJECTS)
	ar -cvq $(LIB) $(OBJECTS)


cu_utils.o: cu_utils.c
	$(CC) $(FLAGS) -c cu_utils.c -o cu_utils.o

cu_tests.o: cu_tests.c
	$(CC) $(FLAGS) -c cu_tests.c -o cu_tests.o

cu_arraylist.o: structures/cu_arraylist.c
	$(CC) $(FLAGS) -c structures/cu_arraylist.c -o cu_arraylist.o

cu_string.o: structures/cu_string.c
	$(CC) $(FLAGS) -c structures/cu_string.c -o cu_string.o

cu_queue.o: structures/cu_queue.c
	$(CC) $(FLAGS) -c structures/cu_queue.c -o cu_queue.o

cu_stack.o: structures/cu_stack.c
	$(CC) $(FLAGS) -c structures/cu_stack.c -o cu_stack.o

cu_heap.o: structures/cu_heap.c
	$(CC) $(FLAGS) -c structures/cu_heap.c -o cu_heap.o

cu_hashmap.o: structures/cu_hashmap.c
	$(CC) $(FLAGS) -c structures/cu_hashmap.c -o cu_hashmap.o


clean:
	rm $(OBJECTS) $(LIB)

rmo:
	rm $(OBJECTS)
