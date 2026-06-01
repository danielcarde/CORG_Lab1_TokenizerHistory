CC = gcc
CFLAGS = -Wall -g
OBJ = main.o tokenizer.o history.o

all: tokenizer

tokenizer: $(OBJ)
	$(CC) $(CFLAGS) -o tokenizer $(OBJ)

main.o: main.c tokenizer.h history.h
tokenizer.o: tokenizer.c tokenizer.h
history.o: history.c history.h

clean:
	rm -f $(OBJ) tokenizer
