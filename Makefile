CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/destinos.c src/pasajeros.c src/avl.c src/estadisticas.c
OBJ = $(SRC:.c=.o)
EXEC = terminal_portuario

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(EXEC)