#include "constantes.h"

int main(int argc, char *argv[]) {
    int id_cliente = atoi(argv[1]);
    int tipo_cliente = atoi(argv[2]);
    int menu = atoi(argv[3]);

    struct msg_buffer mensaje;

    int msg_id = msgget(KEY, 0666);
    if (msg_id == -1) {
        perror("msgget");
        exit(1);
    }

    int id_recibir; 

    mensaje.id_cliente = id_cliente;
    id_recibir = id_cliente + DIFERENCIADOR;
    mensaje.menu = menu;

    char tipo_cliente_s[10]; 

    if (tipo_cliente == CLIENTE_VIP) {
        strcpy(tipo_cliente_s, "VIP"); 
    } 
    else {
        strcpy(tipo_cliente_s, "NORMAL");
    }

    mensaje.tipo = tipo_cliente;
    printf(RED "Cliente %d de tipo %s realiza pedido de menú %d.\n" RESET, id_cliente, tipo_cliente_s, menu);
    usleep(TIME_U);
    if (msgsnd(msg_id, &mensaje, LONGITUD, IPC_NOWAIT) == -1) {
        if (errno == EAGAIN) {  // La cola está llena
            printf("Hay mucha gente y el cliente %d decide marcharse y volver más tarde.\n", id_cliente);
        } 
        else {
            perror("Error al enviar el mensaje");
            exit(1);
        }
    } 
    else {
        if (msgrcv(msg_id, &mensaje, LONGITUD, id_recibir, 0) == -1) {
            perror("Error al recibir el mensaje");
            exit(1); 
        }
        printf(RED "Cliente %d recibió su pedido de menú %d.\n" RESET, id_cliente, menu);
        usleep(TIME_U);
    }
    
    exit(0);
}