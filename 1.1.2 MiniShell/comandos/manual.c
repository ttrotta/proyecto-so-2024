#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void print_header(const char *title) {
    printf("\n--------------------------------------------------------------------------\n");
    printf("\n%s\n", title);
    printf("\n--------------------------------------------------------------------------\n");
}

int main(int argc, char** argv) {
    // Si no se pasa ningún argumento, muestra la lista de comandos disponibles
    if (argv[1] == NULL) {
        print_header("                   COMANDOS DISPONIBLES EN LA SHELL:");

        printf("1 - cdir 'ruta/nombre': Crea un directorio con el nombre especificado en la ruta\n");
        printf("2 - edir 'ruta/nombre': Elimina el directorio especificado en la ruta\n");
        printf("3 - carch 'ruta/nombre': Crea un archivo de texto con el nombre especificado en la ruta\n");
        printf("4 - listar 'ruta/nombre': Lista el contenido del directorio correspondiente al nombre especificado en la ruta\n");
        printf("5 - mostrar 'ruta/nombre.txt': Muestra el contenido del archivo correspondiente al nombre especificado en la ruta\n");
        printf("6 - mperm 'ruta/nombre': Modifica los permisos del archivo correspondiente al nombre especificado en la ruta\n");
        printf("7 - manual: Muestra los comandos implementados en la shell\n");
        printf("8 - salir: Cierra la shell\n\n");

    // Comando 'cdir'
    } else if (!strcmp(argv[1], "cdir")) {
        print_header("                        AYUDA PARA EL COMANDO CDIR:");
        printf("Este comando crea uno o más directorios con los nombres especificados.\n");
        printf("Uso: cdir 'ruta/nombre' ...\n");
        printf("Si deseas crear el directorio en una ruta específica, usa el formato 'ruta/nombre'.\n");
        printf("Para crear más de un directorio, utiliza: 'cdir ruta1/nombre1 ruta2/nombre2 ...'.\n");

    // Comando 'edir'
    } else if (!strcmp(argv[1], "edir")) {
        print_header("                        AYUDA PARA EL COMANDO EDIR:");
        printf("Este comando elimina uno o más directorios con los nombres especificados.\n");
        printf("Uso: edir 'ruta/nombre' ...\n");
        printf("Si el directorio no está en la ubicación actual, debes proporcionar la ruta completa: 'ruta/nombre'.\n");
        printf("Para eliminar más de un directorio: 'edir ruta1/nombre1 ruta2/nombre2 ...'.\n");

    // Comando 'carch'
    } else if (!strcmp(argv[1], "carch")) {
        print_header("                       AYUDA PARA EL COMANDO CARCH:");
        printf("Este comando crea uno o más archivos con los nombres especificados.\n");
        printf("Uso: carch 'ruta/nombre' ...\n");
        printf("Si deseas crear el archivo en una ruta específica, usa el formato 'ruta/nombre'.\n");
        printf("Para crear más de un archivo: 'carch ruta1/nombre1 ruta2/nombre2 ...'.\n");

    // Comando 'listar'
    } else if (!strcmp(argv[1], "listar")) {
        print_header("                       AYUDA PARA EL COMANDO LISTAR:");
        printf("Este comando lista el contenido de uno o más directorios especificados.\n");
        printf("Uso: listar 'ruta/nombre' ...\n");
        printf("Si el directorio no está en la ubicación actual, proporciona la ruta completa: 'ruta/nombre'.\n");
        printf("Para listar más de un directorio: 'listar ruta1/nombre1 ruta2/nombre2 ...'.\n");

    // Comando 'mostrar'
    } else if (!strcmp(argv[1], "mostrar")) {
        print_header("                      AYUDA PARA EL COMANDO MOSTRAR:");
        printf("Este comando muestra el contenido de uno o más archivos de texto especificados.\n");
        printf("Uso: mostrar 'ruta/nombre.txt' ...\n");
        printf("Si el archivo no está en la ubicación actual, proporciona la ruta completa: 'ruta/nombre.txt'.\n");
        printf("Para mostrar más de un archivo: 'mostrar ruta1/nombre1.txt ruta2/nombre2.txt ...'.\n");

    // Comando 'mperm'
    } else if (!strcmp(argv[1], "mperm")) {
        print_header("                       AYUDA PARA EL COMANDO MPERM:");
        printf("Este comando modifica los permisos del archivo especificado.\n");
        printf("Uso: mperm 'ruta/nombre' ...\n");
        printf("Permisos:\n");
        printf("0: Ningún permiso\n");
        printf("1: Ejecución\n");
        printf("2: Escritura\n");
        printf("3: Escritura y Ejecución\n");
        printf("4: Lectura\n");
        printf("5: Lectura y Ejecución\n");
        printf("6: Lectura y Escritura\n");
        printf("7: Lectura, Escritura y Ejecución\n");
        printf("La combinación se ingresa en el formato UGO (User, Group, Others), por ejemplo '751'.\n");

    // Si el comando no existe
    } else {
        printf("No se reconoce el comando.\n");
    }

    return 0;
}
