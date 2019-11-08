CC = gcc
FLAGS = -Wall -g
OBJECTS = cutils.o

test_merge: $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) test_merge.c -o test_merge



cutils.o: ../cutils.c
	$(CC) $(FLAGS) -c ../cutils.c -o cutils.o

