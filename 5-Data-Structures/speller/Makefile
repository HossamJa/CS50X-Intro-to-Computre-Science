# Define the compiler. Change "gcc" to "clang" if needed for your environment.
CC = gcc 

# Conditional: if using clang, add the specific unused arguments flag
ifeq ($(CC), clang)
    CLANG_FLAG = -Qunused-arguments
endif

# Common compiler flags for both GCC and Clang
CFLAGS = -ggdb3 -gdwarf-4 -O0 $(CLANG_FLAG) -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow

speller: speller.o dictionary.o
	$(CC) $(CFLAGS) -o speller speller.o dictionary.o -lm

speller.o: speller.c
	$(CC) $(CFLAGS) -c $<

dictionary.o: dictionary.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o speller