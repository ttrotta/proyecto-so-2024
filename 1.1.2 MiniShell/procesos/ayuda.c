#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv){
	if (argv[1] == NULL){
		printf("\n--------------------------------------------------------------------------\n");
		printf("\n                LISTA DE COMANDOS DISPONIBLES EN LA SHELL:\n");
		printf("\n   ES NECESARIO RESPETAR LAS MINUSCULAS PARA UN CORRECTO FUNCIONAMIENTO\n");
		printf("\n--------------------------------------------------------------------------\n");
		printf("1 - cdir 'ruta/nombre': Crea un directorio con el nombre espesificado en la ruta\n");
		printf("2 - edir 'ruta/nombre': Elimina el directorio espesificado en la ruta\n");
		printf("3 - carch 'ruta/nombre': Crea un archivo de texto con el nombre espesificado en la ruta\n");
		printf("4 - listar 'ruta/nombre': Lista el contenido del directorio correspondiente al nombre espesificado en la ruta\n");
		printf("5 - mostrar 'ruta/nombre.txt': Muestra el contenido del archivo correspondiente al nombre espesificado en la ruta\n");
		printf("6 - mperm 'ruta/nombre': Modifica los permisos del archivo correspondiente al nombre espesificado en la ruta\n");
		printf("7 - ayuda: Muestra una lista de los comandos implementados en la shell\n");
		printf("8 - salir: Cierra la shell\n\n");
	}else if (!strcmp(argv[1],"cdir")){
		printf("\n--------------------------------------------------------------------------\n");
		printf("\n                        AYUDA PARA EL COMANDO CDIR:\n\n");
		printf("Este comando crea uno o mas directorios con los nombres especificados.\n");
		printf("Para poder utilizar correctamente este comando hay que ingresar la palabra \n"
				"reservada 'cdir' seguido del nombre del directorio. En el caso de tener la \n"
				"intención de crear el directorio en una ubicacion en la cuál no se encuentra\n"
				"debera ingresar la ruta de la ubicacion respetando la forma 'ruta/nombre'.\n"
				"La forma de crear más de un directorio es respetando el siguiente formato\n"
				"'cdir 'ruta1/nombre1 'ruta2/nombre2' ... 'rutaN/nombreN' '");
		printf("\n--------------------------------------------------------------------------\n");
	}else if (!strcmp(argv[1],"edir")){
		printf("\n--------------------------------------------------------------------------\n");
		printf("\n                        AYUDA PARA EL COMANDO EDIR:\n\n");
		printf("Este comando elimina uno o mas directorios con los nombres especificados.\n");
		printf("Para poder utilizar correctamente este comando hay que ingresar la palabra \n"
				"reservada 'edir' seguido del nombre del directorio. En el caso de tener la \n"
				"intención de eliminar el directorio en una ubicacion en la cuál no se \n"
				"encuentra debera ingresar la ruta de la ubicacion respetando la forma \n"
				"'ruta/nombre'."
				"La forma de eliminar más de un directorio es respetando el siguiente \n"
				"formato 'edir 'ruta1/nombre1 'ruta2/nombre2' ... 'rutaN/nombreN' '");
		printf("\n--------------------------------------------------------------------------\n");
	}else if (!strcmp(argv[1],"carch")){
		printf("\n--------------------------------------------------------------------------\n");
		printf("\n                       AYUDA PARA EL COMANDO CARCH:\n\n");
		printf("Este comando crea uno o mas archivos con los nombres especificados.\n");
		printf("Para poder utilizar correctamente este comando hay que ingresar la palabra \n"
				"reservada 'carch' seguido del nombre del archivo. En el caso de tener la \n"
				"intención de crear el archivo en una ubicacion en la cuál no se encuentra\n"
				"debera ingresar la ruta de la ubicacion respetando la forma 'ruta/nombre'.\n"
				"La forma de crear más de un archivo es respetando el siguiente formato\n"
				"'carch 'ruta1/nombre1 'ruta2/nombre2' ... 'rutaN/nombreN' '");
		printf("\n--------------------------------------------------------------------------\n");
	}else if (!strcmp(argv[1],"listar")){
		printf("\n--------------------------------------------------------------------------\n");
		printf("\n                       AYUDA PARA EL COMANDO LISTAR:\n\n");
		printf("Este comando lista el contenido uno o mas directorios con los nombres \n"
				"especificados.");
		printf("Para poder utilizar correctamente este comando hay que ingresar la palabra \n"
				"reservada 'listar' seguido del nombre del directorio. En el caso de tener la \n"
				"intención de listar el directorio de una ubicacion en la cuál no se encuentra\n"
				"debera ingresar la ruta de la ubicacion respetando la forma 'ruta/nombre'.\n"
				"La forma de listar más de un directorio es respetando el siguiente formato\n"
				"'listar 'ruta1/nombre1 'ruta2/nombre2' ... 'rutaN/nombreN' '");
		printf("\n--------------------------------------------------------------------------\n");
	}else if (!strcmp(argv[1],"mostrar")){
		printf("\n--------------------------------------------------------------------------\n");
		printf("\n                      AYUDA PARA EL COMANDO MOSTRAR:\n\n");
		printf("Este comando muestra el contenido de uno o mas archivos con los nombres \n"
				"especificados.\n");
		printf("Para poder utilizar correctamente este comando hay que ingresar la palabra \n"
				"reservada 'mostrar' seguido del nombre del archivo. En el caso de tener la \n"
				"intención de mostrar el archivo de una ubicacion en la cuál no se encuentra\n"
				"debera ingresar la ruta de la ubicacion respetando la forma 'ruta/nombre'.\n"
				"La forma de mostrar más de un archivo es respetando el siguiente formato\n"
				"'mostrar 'ruta1/nombre1 'ruta2/nombre2' ... 'rutaN/nombreN' '");
		printf("\n--------------------------------------------------------------------------\n");
	}else if (!strcmp(argv[1],"mperm")){
		printf("\n--------------------------------------------------------------------------\n");
		printf("\n                       AYUDA PARA EL COMANDO MPERM:\n\n");
		printf("Este comando modifica los permisos del archivo mencionado en la ruta.\n");
		printf("Para indicar la combinacion de permisos que desea modificar tiene que ingresar el numero correspondiente:\n"
				"0: Ningun permiso\n"
				"1: Permiso de ejecucion\n"
				"2: Permiso de escritura\n"
				"3: Permisos de ejecucion y escritura\n"
				"4: Permiso de lectura\n"
				"5: Permisos de ejecucion y lectura\n"
				"6: Permisos de escritura y lectura\n"
				"7: Permisos de ejecucion, escritura y lectura\n"
				"Esta acción se tendra que repetir tres veces, una para cada grupo, formando una combinacion de numeros de la forma UGO,\n"
				"siendo el primer numero para modificar los permisos de Users, el segundo de Group y el  tercero de Oters. Por ejemplo:\n"
				"	-A la categoria User le vamos a modificar los permisos de ejecucion, escritura y lectura\n"
				"	-A la categoria Group le vamos a modificar los permisos de escritura y lectura\n"
				"	-A la categoria Other le vamos a modificar el permiso de ejecucion");
		printf("\n--------------------------------------------------------------------------\n");
	}else
		printf("No existe ayuda para el comando ingresado\n");

	return 0;
}
