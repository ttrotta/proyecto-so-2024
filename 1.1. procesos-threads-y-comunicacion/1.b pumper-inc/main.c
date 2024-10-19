#include "constantes.h"

int main() {
    pid_t despachador;
    pid_t empleado1 , empleado2, empleado3, empleado4;

    int msg_id = msgget(KEY, IPC_CREAT | 0666);
    if (msg_id == -1) {
        perror("msgget");
        exit(1);
    }

    char *argsD[] = { "./despachador", NULL };
    despachador = fork();
    if (despachador == 0) {
        execv("./despachador", argsD);
        perror("execv falló");
        exit(1);
    }

    char *argsH[] = { "./hamburguesa-simple", NULL };
    empleado1 = fork();
    if (empleado1 == 0) {
        execv("./hamburguesa-simple", argsH);
        perror("execv falló");
        exit(1);
    }

    char *argsV[] = { "./menu-vegano", NULL };
    empleado2 = fork();
    if (empleado2 == 0) {
        execv("./menu-vegano", argsV);
        perror("execv falló");
        exit(1);
    }

    char *argsP[] = { "./papas-fritas", NULL };
    empleado3 = fork();
    if (empleado3 == 0) {
        execv("./papas-fritas", argsP);
        perror("execv falló");
        exit(1);
    }
    empleado4 = fork();
    if (empleado4 == 0)  {
        execv("./papas-fritas", argsP);
        perror("execv falló");
        exit(1);
    }


    for (int i = 0; i < CANT_CLIENTES; i++) {        
        int tipo_cliente = (rand() % 4 == 0) ? CLIENTE_VIP : CLIENTE_NORMAL; // 25% de salir VIP
        int tipo_menu = HAMBURGUESA + rand() % 3;

        if (fork() == 0) {
            srand(time(NULL) + getpid());

            char cliente_id[10];
            char tipo_cliente_str[10];
            char tipo_menu_str[10];

            // conversión a string por el uso de execv
            sprintf(cliente_id, "%d", i + 1);
            sprintf(tipo_cliente_str, "%d", tipo_cliente);
            sprintf(tipo_menu_str, "%d", tipo_menu);

            char *argsC[] = {
                "./cliente",    
                cliente_id,      
                tipo_cliente_str, 
                tipo_menu_str,    
                NULL             
            };

            execv("./cliente", argsC);

            perror("execv falló");
            exit(1);
        }

    }
    for (int i = 0; i < CANT_CLIENTES + 5; i++) {
        wait(NULL);
    }

    printf("La casa de comidas cerró.\n");

    msgctl(msg_id, IPC_RMID, NULL); 

    return 0;
}