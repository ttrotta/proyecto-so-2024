#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define COLOR_ROJO "\x1b[31m"
#define COLOR_VERDE "\x1b[92m"
#define COLOR_AMARILLO "\x1b[33m"
#define COLOR_NARANJA "\x1b[38;5;208m"
#define COLOR_RESET "\x1b[0m"

#define CANT_RENOS 9
#define CANT_ELFOS 10
#define MAX_ELFOS_PROBLEMAS 3

#define TIME 10000

sem_t semSanta, semRenos, semElfos, cantRenos, cantElfos;
pthread_mutex_t mutex;

void* santa(void *arg) {
    while(1){
        sem_wait(&semSanta);
        printf(COLOR_ROJO "\nSanta es despertado!\n\n" COLOR_RESET);
        usleep(TIME);

        pthread_mutex_lock(&mutex);
            if(sem_trywait(&cantRenos) == -1) { // renos despertaron a santa
                printf(COLOR_NARANJA "Llegaron todos los renos y santa prepara su trineo.\n" COLOR_RESET);
                usleep(TIME);
                for(int i = 0; i < CANT_RENOS; i++) {
                    sem_post(&semRenos);
                    sem_post(&cantRenos);
                }
                printf(COLOR_NARANJA "Los renos hicieron su trabajo y vuelven de vacaciones.\n" COLOR_RESET);
                usleep(TIME);
            }
            else { // elfos despertaron a santa
                sem_post(&cantRenos); // dejamos como estaban los renos
                printf(COLOR_NARANJA "Santa ayuda a los tres elfos que pidieron ayuda.\n" COLOR_RESET);
                usleep(TIME);
                for (int i = 0; i < MAX_ELFOS_PROBLEMAS; i++) {
                    sem_post(&cantElfos);
                }
                printf(COLOR_NARANJA "Los 3 elfos resolvieron sus problemas y se van.\n\n" COLOR_RESET);
                sem_post(&semElfos);
            }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void* renos(void *arg) {
    while(1){
        pthread_mutex_lock(&mutex);
            sem_wait(&cantRenos);
            usleep(TIME);
            if(sem_trywait(&cantRenos) == 0) { // si no es el último
                sem_post(&cantRenos); // volvemos a estado original ya que decrementamos
                printf(COLOR_AMARILLO "Vuelve un reno al Polo Norte luego de vacaciones.\n" COLOR_RESET);
            }
            else { // si es el último
                printf(COLOR_AMARILLO "Vuelve el último reno y va a despertar a Santa.\n\n" COLOR_RESET);
                sem_post(&semSanta);
            }
        pthread_mutex_unlock(&mutex);
        sem_wait(&semRenos); // esperando la vuelta de los renos, para irse de vacaciones
         sleep(1); // este sleep libera de la inanición a los elfos
    }
    pthread_exit(NULL); 
}

void* elfos(void *arg) {
    while(1){
        sem_wait(&semElfos);
        pthread_mutex_lock(&mutex);
            sem_wait(&cantElfos);
            if(sem_trywait(&cantElfos) == 0) {
                sem_post(&semElfos);
                sem_post(&cantElfos);
                printf(COLOR_VERDE "Elfo en problemas para hacer juguetes!\n" COLOR_RESET);
                usleep(TIME);
            }
            else {
                printf(COLOR_VERDE "Llega un tercer elfo en problemas, van a buscar a Santa.\n" COLOR_RESET);
                sem_post(&semSanta);
                usleep(TIME);
            }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t santa_t;
    pthread_t renos_t[CANT_RENOS], elfos_t[CANT_ELFOS];

    sem_init(&semSanta, 0, 0);
    sem_init(&semRenos, 0, 0);
    sem_init(&semElfos, 0, 1);
    sem_init(&cantRenos, 0, CANT_RENOS);
    sem_init(&cantElfos, 0, MAX_ELFOS_PROBLEMAS);

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&santa_t, NULL, santa, NULL);

    for(int i = 0; i < CANT_RENOS; i++) {
        pthread_create(&renos_t[i], NULL, renos, NULL);
    }

    for(int i = 0; i < CANT_ELFOS; i++) {
        pthread_create(&elfos_t[i], NULL, elfos, NULL);
    }

    pthread_join(santa_t, NULL);

    for(int i = 0; i < CANT_RENOS; i++) {
        pthread_join(renos_t[i], NULL);
    }

    for(int i = 0; i < CANT_ELFOS; i++) {
        pthread_join(elfos_t[i], NULL);
    }

    sem_destroy(&semSanta);
    sem_destroy(&semRenos);
    sem_destroy(&semElfos);
    sem_destroy(&cantRenos);
    sem_destroy(&cantElfos);

    pthread_mutex_destroy(&mutex);

    return 0;
}