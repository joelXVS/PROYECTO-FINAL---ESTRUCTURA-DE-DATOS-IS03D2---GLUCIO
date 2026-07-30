CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = main.c destinos.c pasajeros.c avl.c
OBJ = $(SRC:.c=.o)
EXEC = terminal_portuario

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXEC)

.PHONY: all clean
