CC=gcc
CFLAGS= -Wall  -Wextra -std=c11 -Werror -g


test : clean test.o lib.o
	$(CC)  $(CFLAGS)  ./Build/test.o ./Build/n_std_collections_sequences.o -o ./Build/test
	cp ./Build/test ./src/build/Debug/outDebug
	rm ./Build/*.o

test.o : ./src/garbage/test.c
	$(CC)  $(CFLAGS) -c  ./src/garbage/test.c -o ./Build/test.o

lib.o : ./src/std/src/n_std_collections_sequences.c
	$(CC)  $(CFLAGS) -c  ./src/std/src/n_std_collections_sequences.c -o ./Build/n_std_collections_sequences.o


clean:
	rm -f ./*.o 

