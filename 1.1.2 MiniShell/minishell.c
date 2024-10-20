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
	int pid;
	pid = fork();
	if (!pid){
		execv(imagen, argumentos);
		printf("ERROR: No se pudo cargar el comando\n");
		exit(1);
	} else
		wait(NULL);
}

void limpiarBuffer(const char* str){
    if(str[strlen(str) - 1] != '\n')
		while(getchar() != '\n');
}

int main(){
	char path_actual[512];
	getcwd(path_actual, 512);
	int salir = 0;
	int valida = 1;
	char* punteroAux;
	char comando[MAX_CHAR + 2]; // comando + parametros
	char command[MAX_CHAR_COM+1]; // comando
	char** args = malloc((MAX_ARGS+2)*sizeof(char*));
	*args = malloc(512*sizeof(char));
	for (int i = 1; i < (MAX_ARGS+2); i++)
		*(args+i) = malloc((MAX_CHAR_ARG+1)*sizeof(char));
	
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~ MINISHELL ~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	while (!salir){
		printf("\e[1;32m minishell\033[0;37m:\e[1;34m%s $ \033[0;37m", path_actual);
		valida = 1;
		fgets(comando,MAX_CHAR + 2,stdin);
		if (strlen(comando) == MAX_CHAR + 1 && comando[MAX_CHAR] != '\n'){
			printf("ERROR: El comando ingresado supera la cantidad de caracteres permitidos (%i)\n", MAX_CHAR);
		} else if (strlen(comando) != 1){	
			char comando_aux[MAX_CHAR + 2];
			int len = strlen(comando);
			strcpy(comando_aux, comando);
			comando_aux[len-1] = '\0';			
			char delimitador[] = " ";
			char *token = strtok(comando_aux, delimitador);
			if (strlen(token)>MAX_CHAR_COM){
				printf("ERROR: El comando ingresado no existe.\nPara ayuda ingrese el comando 'ayuda'. Para salir ingrese el comando 'salir'\n", MAX_CHAR_COM);
			}else{
				strcpy(command,token);
				token = strtok(NULL, delimitador);
				int cantArgs = 0;
				if(token != NULL && valida){
					while(token != NULL && valida){
						if (cantArgs==MAX_ARGS){
							printf("ERROR: Se superaron la cantidad de parametros permitidos (%i)\n",MAX_ARGS);
							valida = 0;
						}else {
							if (strlen(token)>MAX_CHAR_ARG){
								printf("ERROR: Se superaron los caracteres permitidos por parametro (%i)\n",MAX_CHAR_ARG);
								valida = 0;
							}else {
								cantArgs++;
								strcpy(args[cantArgs],token);
								token = strtok(NULL, delimitador);
							}
						}
						
					}
				}
				if (valida){
					punteroAux = args[cantArgs+1];
					args[cantArgs+1] = NULL;
					if (!strcmp(command, "cdir")){
						args[0] = "./procesos/cdir";
						ejecutarComando(args[0], args);
					} else if (!strcmp(command, "edir")){
						args[0] = "./procesos/edir";
						ejecutarComando(args[0], args);
					} else if (!strcmp(command, "carch")){
						args[0] = "./procesos/carch";
						ejecutarComando(args[0], args);
					} else if (!strcmp(command, "listar")){
						args[0] = "./procesos/listar";
						ejecutarComando(args[0], args);
					} else if (!strcmp(command, "mostrar")){
						args[0] = "./procesos/mostrar";
						ejecutarComando(args[0], args);
					} else if (!strcmp(command, "ayuda")){
						args[0] = "./procesos/ayuda";
						ejecutarComando(args[0], args);
					} else if (!strcmp(command, "mperm")){
						args[0] = "./procesos/mperm";
						ejecutarComando(args[0], args);
					} else if (!strcmp(command, "salir"))
						salir = 1;
					else	
						printf("ERROR: El comando ingresado no existe.\nPara ayuda ingrese el comando 'ayuda'. Para salir ingrese el comando 'salir'\n");
					args[cantArgs+1] = punteroAux;
				}
			}
			
		} // else -> strlen(comando) == 1 // Se ingreso un \n, no hay que hacer nada
		limpiarBuffer(comando);
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~ CERRANDO MINISHELL ~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	return 0;
}
