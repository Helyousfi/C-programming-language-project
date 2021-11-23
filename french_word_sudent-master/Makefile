CC=gcc

CFLAGS=-Ofast -march=native -mtune=native -std=c11

LDFLAGS=

EXEC=main

SRC=./src/load_dic.c		\
	./src/main.c

OBJ= $(SRC:.c=.o)

all: $(EXEC)

main: $(OBJ)
	$(CC) $(LDFLAGS) -o ./bin/$@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean mrproper

clean:
	find ./bin -name main -exec rm {} \;
	find ./src -name *.o  -exec rm {} \;

mrproper: clean
	rm $(EXEC)
