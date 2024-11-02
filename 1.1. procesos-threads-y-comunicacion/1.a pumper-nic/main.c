#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>

#define MAX 256
#define TAM sizeof(int)

#define CANT_EMPLEADOS 4
#define CANT_CLIENTES 20

#define CLIENTE_VIP 0
#define CLIENTE_NORMAL 1

#define HAMBURGUESA 3
#define MENU_VEGANO 4
#define PAPAS_FRITAS 5

#define CANT_ITERACIONES 50
#define COLOR_RESET "\033[0m"
#define COLOR_CLIENTE_VIP "\x1b[38;5;208m"    
#define COLOR_CLIENTE_NORMAL "\033[1;36m"  
#define COLOR_DESPACHADOR "\033[1;32m"    
#define COLOR_HAMBURGUESA "\033[1;34m"     
#define COLOR_MENU_VEGANO "\033[1;35m"     
#define COLOR_PAPAS "\033[1;31m"          

int pipe_vip_desp[2], pipe_normal_desp[2];
int pipe_desp_hamb[2], pipe_desp_papas[2], pipe_desp_veg[2];
int pipe_hamb_cli[2], pipe_papas_cli[2], pipe_veg_cli[2];

void cliente() {
    srand(time(NULL) + getpid());

    close(pipe_vip_desp[0]);
    close(pipe_normal_desp[0]);
    close(pipe_hamb_cli[1]);
    close(pipe_papas_cli[1]);
    close(pipe_veg_cli[1]);

    int vip = (rand() % 4 == 0) ? CLIENTE_VIP : CLIENTE_NORMAL; 
    
    for (int i = 0; i < CANT_ITERACIONES; i++) {
        int cola_llena = rand() % 20;

        if(cola_llena == 1) {
            printf("La cola está llena y el cliente se va.\n");
            continue; 
        }

        int pedido = HAMBURGUESA + rand() % 3;
        int pedido_recibido;

        if(vip == CLIENTE_VIP) {
            printf(COLOR_CLIENTE_VIP "Cliente VIP #%d realiza el pedido de un %i.\n" COLOR_RESET, getpid(), pedido);
            write(pipe_vip_desp[1], &pedido, TAM); 
        } 
        else {
            printf(COLOR_CLIENTE_NORMAL "Cliente Normal #%d realiza el pedido de un %i.\n" COLOR_RESET, getpid(), pedido);
            write(pipe_normal_desp[1], &pedido, TAM); 
        }

        switch (pedido) {
            case HAMBURGUESA :
                read(pipe_hamb_cli[0], &pedido_recibido, TAM);
                printf(COLOR_CLIENTE_VIP "Cliente #%d recibe una hamburguesa.\n" COLOR_RESET, getpid());
                break;
            case PAPAS_FRITAS :
                read(pipe_papas_cli[0], &pedido_recibido, TAM);
                printf(COLOR_CLIENTE_VIP "Cliente #%d recibe unas papas fritas.\n" COLOR_RESET, getpid());
                break;
            case MENU_VEGANO :
                read(pipe_veg_cli[0], &pedido_recibido, TAM);
                printf(COLOR_CLIENTE_VIP "Cliente #%d recibe un menú vegano.\n" COLOR_RESET, getpid());
                break;
            default:
                break;
        }
    }

    close(pipe_vip_desp[1]);
    close(pipe_normal_desp[1]);
    close(pipe_hamb_cli[0]);
    close(pipe_papas_cli[0]);
    close(pipe_veg_cli[0]);
}

void despachador() {
    close(pipe_vip_desp[1]);
    close(pipe_normal_desp[1]);
    close(pipe_desp_hamb[0]);
    close(pipe_desp_papas[0]);
    close(pipe_desp_veg[0]);

    int menu_pedido;

    fcntl(pipe_vip_desp[0], F_SETFL, O_NONBLOCK); 

    while (1) {
        if(read(pipe_vip_desp[0], &menu_pedido, TAM) > 0) {
            printf(COLOR_DESPACHADOR "Llega un pedido VIP.\n" COLOR_RESET);
        }
        else {
            read(pipe_normal_desp[0], &menu_pedido, TAM);
            printf(COLOR_DESPACHADOR "Llega un pedido normal.\n" COLOR_RESET);
        }
        // Analizar caso de todos VIP 
        switch (menu_pedido) {
            case HAMBURGUESA:
                printf(COLOR_HAMBURGUESA "Despachador manda a cocinar una hamburguesa.\n" COLOR_RESET);
                write(pipe_desp_hamb[1], &menu_pedido, TAM); 
                break;
            case PAPAS_FRITAS: 
                printf(COLOR_PAPAS "Despachador manda a cocinar unas papas fritas.\n" COLOR_RESET);
                write(pipe_desp_papas[1], &menu_pedido, TAM); 
                break;    
            case MENU_VEGANO:
                printf(COLOR_MENU_VEGANO "Despachador manda a cocinar un menú vegano.\n" COLOR_RESET);
                write(pipe_desp_veg[1], &menu_pedido, TAM);
                break;
            default:
                break;
        }
    }

    close(pipe_vip_desp[0]);
    close(pipe_normal_desp[0]);
    close(pipe_desp_hamb[1]);
    close(pipe_desp_papas[1]);
    close(pipe_desp_veg[1]);
}

void hamburguesa_simple() {
    close(pipe_desp_hamb[1]);
    close(pipe_hamb_cli[0]);
    
    int pedido;
    while(1) {
        read(pipe_desp_hamb[0], &pedido, TAM);
        printf(COLOR_HAMBURGUESA "Empleado prepara una hamburguesa.\n" COLOR_RESET);
        sleep(1);
        write(pipe_hamb_cli[1], &pedido, TAM);
    }

    close(pipe_desp_hamb[0]);
    close(pipe_hamb_cli[1]);
}

void menu_vegano() {
    close(pipe_desp_veg[1]);
    close(pipe_veg_cli[0]);
    
    int pedido;
    while(1) {
        read(pipe_desp_veg[0], &pedido, TAM);
        printf(COLOR_MENU_VEGANO "Empleado prepara un menú vegano.\n" COLOR_RESET);
        sleep(1);
        write(pipe_veg_cli[1], &pedido, TAM);
    }

    close(pipe_desp_veg[0]);
    close(pipe_veg_cli[1]);
}

void papas_fritas() {
    close(pipe_desp_papas[1]);
    close(pipe_papas_cli[0]);
    
    int pedido;
    while(1) {
        read(pipe_desp_papas[0], &pedido, TAM);
        printf(COLOR_PAPAS "Empleado prepara unas papas fritas.\n" COLOR_RESET);
        sleep(1);
        write(pipe_papas_cli[1], &pedido, TAM);
    }
    
    close(pipe_desp_papas[0]);
    close(pipe_papas_cli[1]);
}

void crear_proceso(void (*func)(), const char* error_msg) {
    pid_t pid = fork();
    if (pid == 0) {
        func(); 
        exit(0);
    } else if (pid < 0) {
        perror(error_msg);
        exit(1);
    }
}

int main() {

    if (pipe(pipe_vip_desp) == -1 || pipe(pipe_normal_desp) == -1 || pipe(pipe_desp_hamb) == -1 || 
        pipe(pipe_desp_papas) == -1 || pipe(pipe_desp_veg) == -1 || pipe(pipe_hamb_cli) == -1 || 
        pipe(pipe_papas_cli) == -1 || pipe(pipe_veg_cli) == -1) {
        fprintf(stderr, "Creación de pipes fallida.");
        return 1;
    }

    crear_proceso(despachador, "Error en la creación del proceso despachador.");

    void (*empleado_funcs[CANT_EMPLEADOS])() = {hamburguesa_simple, menu_vegano, papas_fritas, papas_fritas};

    for (int i = 0; i < CANT_EMPLEADOS; i++) {
        crear_proceso(empleado_funcs[i], "Error en la creación del proceso empleado.");
    }

    for (int i = 0; i < CANT_CLIENTES; i++) {
        crear_proceso(cliente, "Error en la creación del proceso cliente.");
    }

    for(int i = 0; i < CANT_EMPLEADOS + CANT_CLIENTES; i++) {
        wait(NULL);
    }

    return 0;
}
