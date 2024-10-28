#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv){

	char* nombre = argv[1];
	char* modo = argv[2];
	int i = strtol(modo, 0, 10);
	char ocho[] = {'8'};
	char nueve[] = {'9'};
	int res;
	/*Tiene que ser mayor a 000 ya que si es 0, no hay ningun permiso que modificar, el minimo sería el 001, que sería el permiso de ejecución para la categoría "others"
	  Tiene que ser menor a 778 ya que lo máximo que se puede formar es 777 que serian los tres permisos (r,w,x) a las tres categorias (u,g,o)*/
	if (strpbrk(argv[2],ocho) == NULL && strpbrk(argv[2],nueve) == NULL && (i > 0) && (i < 778)){
		res = chmod(nombre, i);	
		if(!(res < 0)){ 		
			printf("\nUsted ha modificado los permisos correctamente\n");
		}else{
			printf("\nLe informamos que el archivo no es valido\n");
		}
	}else {
		printf("ERROR: Los permisos ingresados son invalidos\n");
	}
	
	return 0;
}
