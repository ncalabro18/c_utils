CC = gcc
FLAGS = -Wall -g
OBJECTS = c_utils.o unit_tests.o arraylist.o

test_sort: $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) test_sort.c -o test_sort



c_utils.o: ../c_utils.c
	$(CC) $(FLAGS) -c ../c_utils.c -o c_utils.o

unit_tests.o: ../unit_tests/unit_tests.c
	$(CC) $(FLAGS) -c ../unit_tests/unit_tests.c -o unit_tests.o

arraylist.o: ../structures/arraylist.c
	$(CC) $(FLAGS) -c ../structures/arraylist.c -o arraylist.o

nstring.o: ../structures/nstring.c
	$(CC) $(FLAGS) -c ../structures/nstring.c -o ntring.o
