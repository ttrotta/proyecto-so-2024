#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_CHAR 500
#define MAX_ARGS 5
#define MAX_CHAR_ARG 70
#define MAX_CHAR_COM 7

void ejecutarComando(char* imagen, char** argumentos){
    int pid = fork();

    if (pid < 0) {
        printf("ERROR: Falló el fork\n");
        exit(1);
    } else if (pid == 0) {
        execv(imagen, argumentos);
        printf("ERROR: No se pudo cargar el comando\n");
        exit(1);
    } else {
        wait(NULL);
    }
}

void limpiarBuffer(const char* str){
    if (str[strlen(str) - 1] != '\n') {
        while (getchar() != '\n');
    }
}

void imprimirTitulo(const char* titulo){

    printf("\e[1;36m"); // Color de texto a cian claro
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~~~~~~~~~~~~~    %s    ~~~~~~~~~~~~~~\n", titulo);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\033[0m"); // Se reestablece el color por defecto
}

int main() {
    char path_actual[512];
    getcwd(path_actual, sizeof(path_actual)); // Obtener directorio actual
    int salir = 0;
    char comando[MAX_CHAR + 2]; // Buffer para el comando y parámetros
    char command[MAX_CHAR_COM + 1]; // Comando sin parámetros

    // Memoria para los argumentos del comando
    char** args = malloc((MAX_ARGS + 2) * sizeof(char*));
    for (int i = 0; i < (MAX_ARGS + 2); i++) {
        args[i] = malloc((MAX_CHAR_ARG + 1) * sizeof(char));
    }

    // Imprimir título inicial con colores
    imprimirTitulo("MINISHELL");

    while (!salir) {
        printf("\e[1;32m minishell\033[0;37m:\e[1;34m%s $ \033[0;37m", path_actual);
        fgets(comando, sizeof(comando), stdin);

        if (strlen(comando) == MAX_CHAR + 1 && comando[MAX_CHAR] != '\n') {
            printf("ERROR: El comando ingresado supera la cantidad de caracteres permitidos (%d)\n", MAX_CHAR);
            limpiarBuffer(comando);
            continue;
        }

        // Remover el salto de línea al final del comando
        comando[strcspn(comando, "\n")] = 0;

        if (strlen(comando) == 0) continue; // Si se ingresó solo un Enter

        char* token = strtok(comando, " ");
        if (!token) continue; // Sin comando válido

        if (strlen(token) > MAX_CHAR_COM) {
            printf("ERROR: El comando ingresado no existe. Para ayuda ingrese 'ayuda'. Para salir ingrese 'salir'.\n");
            continue;
        }

        strcpy(command, token);

        int cantArgs = 0;
        while ((token = strtok(NULL, " ")) != NULL) {
            if (cantArgs == MAX_ARGS) {
                printf("ERROR: Se superaron la cantidad de parámetros permitidos (%d)\n", MAX_ARGS);
                break;
            }
            if (strlen(token) > MAX_CHAR_ARG) {
                printf("ERROR: Parámetro demasiado largo (%d caracteres máximo)\n", MAX_CHAR_ARG);
                break;
            }
            strcpy(args[++cantArgs], token);
        }

        args[cantArgs + 1] = NULL; // El último argumento debe ser NULL para execv



        if (strcmp(command, "cdir") == 0) {
            args[0] = "./comandos/cdir";
            ejecutarComando(args[0], args);
        } else if (strcmp(command, "edir") == 0) {
            args[0] = "./comandos/edir";
            ejecutarComando(args[0], args);
        } else if (strcmp(command, "carch") == 0) {
            args[0] = "./comandos/carch";
            ejecutarComando(args[0], args);
        } else if (strcmp(command, "listar") == 0) {
            args[0] = "./comandos/listar";
            ejecutarComando(args[0], args);
        } else if (strcmp(command, "mostrar") == 0) {
            args[0] = "./comandos/mostrar";
            ejecutarComando(args[0], args);
        } else if (strcmp(command, "manual") == 0) {//Mostrar una ayuda con los comandos posibles.
            args[0] = "./comandos/manual";
            ejecutarComando(args[0], args);
        } else if (strcmp(command, "mperm") == 0) {
            args[0] = "./comandos/mperm";
            ejecutarComando(args[0], args);
        } else if (strcmp(command, "salir") == 0) {
            salir = 1;
        } else {
            printf("ERROR: Comando no reconocido. Para ayuda ingrese 'ayuda'. Para salir ingrese 'salir'.\n");
        }
    }

    // Liberar la memoria asignada dinámicamente
    for (int i = 0; i < (MAX_ARGS + 2); i++) {
        free(args[i]);
    }
    free(args);

    // Imprimir título de cierre con colores
    imprimirTitulo("CERRANDO MINISHELL");

    return 0;
}
