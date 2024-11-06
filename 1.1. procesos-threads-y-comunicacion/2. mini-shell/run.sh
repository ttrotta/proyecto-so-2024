#!/bin/bash

# Se compila el archivo minishell.c en un ejecutable llamado minishell
gcc -Wall minishell.c -o minishell

# Se verifica si la compilación fue exitosa
if [ $? -eq 0 ]; then
    # Ejecutar el ejecutable minishell
    ./minishell
else
    echo "Error en la compilación de minishell.c"
fi
