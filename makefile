CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g
OBJ = main.o tokenizer.o history.o

.PHONY: all test sanitize clean
all: tokenizer
tokenizer: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)
main.o: main.c tokenizer.h history.h
tokenizer.o: tokenizer.c tokenizer.h
history.o: history.c history.h

tests/test_memory: tests/test_memory.c tokenizer.c tokenizer.h history.c history.h
	$(CC) $(CFLAGS) -o $@ tests/test_memory.c
test: tests/test_memory
	./tests/test_memory
sanitize:
	$(CC) $(CFLAGS) -fsanitize=address,undefined -fno-omit-frame-pointer -o tests/test_memory_sanitize tests/test_memory.c
	ASAN_OPTIONS=detect_leaks=1 ./tests/test_memory_sanitize
clean:
	rm -f $(OBJ) tokenizer tests/test_memory tests/test_memory_sanitize
