#!/bin/bash

# Nombre del archivo fuente
SOURCE="minishell.c"
# Nombre del ejecutable
EXECUTABLE="minishell"

# Compilar el programa
echo "Compilando $SOURCE..."
gcc "$SOURCE" -o "$EXECUTABLE"
if [ $? -ne 0 ]; then
    echo "Error: La compilación falló."
    exit 1
fi
echo "Compilación exitosa."

# Ejecutar el programa
echo "Ejecutando $EXECUTABLE..."
./"$EXECUTABLE"
