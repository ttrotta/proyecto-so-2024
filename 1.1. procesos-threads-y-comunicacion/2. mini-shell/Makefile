CC = gcc
CFLAGS = -o
COMMANDS = cdir edir carch listar mostrar manual mperm

all: $(COMMANDS)

# Compilar cada comando dentro de la carpeta comandos
$(COMMANDS): 
	$(CC) comandos/$@.c $(CFLAGS) comandos/$@

# Limpia los ejecutables
clean:
	rm -f comandos/$(COMMANDS)
