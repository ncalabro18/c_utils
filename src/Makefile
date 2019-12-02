CC = gcc
FLAGS = -Wall -g -Wno-unused-function
OBJECTS = cu_utils.o unit_tests.o arraylist.o queue.o
LIB =  cu_utils.a

cu_utils.a: $(OBJECTS)
	ar -cvq $(LIB) $(OBJECTS)

cu_utils.o: cu_utils.c
	$(CC) $(FLAGS) -c cu_utils.c -o cu_utils.o

unit_tests.o: unit_tests/unit_tests.c
	$(CC) $(FLAGS) -c unit_tests/unit_tests.c -o unit_tests.o

arraylist.o: structures/arraylist.c
	$(CC) $(FLAGS) -c structures/arraylist.c -o arraylist.o

nstring.o: structures/nstring.c
	$(CC) $(FLAGS) -c structures/nstring.c -o ntring.o

queue.o: structures/queue.c
	$(CC) $(FLAGS) -c structures/queue.c -o queue.o

clean:
	rm $(OBJECTS)
