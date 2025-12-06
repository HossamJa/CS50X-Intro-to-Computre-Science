# Default compiler is CLANG
CC = clang 
# Use 'gcc' if specified on command line: make CC=gcc

# Define all flags
BASE_CFLAGS = -ggdb3 -gdwarf-4 -O0 -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow
LDLIBS = -lm

# Add clang-specific flags conditionally
ifeq ($(CC), clang)
    CFLAGS = $(BASE_CFLAGS) -Qunused-arguments
else
    CFLAGS = $(BASE_CFLAGS)
endif

filter:
	$(CC) $(CFLAGS) -o $@ filter.c helpers.c $(LDLIBS)
