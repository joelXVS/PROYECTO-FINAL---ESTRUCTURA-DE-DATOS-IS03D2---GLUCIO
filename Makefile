# Compilador y opciones
CC       = gcc
CFLAGS   = -Wall -Wextra -g -I.
LDFLAGS  =

# Nombre del ejecutable
TARGET   = terminal_portuario

# Archivos fuente y objetos
SRCS     = main.c destinos.c pasajeros.c avl.c
OBJS     = $(SRCS:.c=.o)

# Regla por defecto
all: $(TARGET)

# Enlazar objetos para crear el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilar cada .c a .o (regla implícita)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(OBJS) $(TARGET)

# Limpiar y luego compilar
rebuild: clean all

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Indicar que no son archivos reales
.PHONY: all clean rebuild run