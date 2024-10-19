#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define COLOR_ROJO "\x1b[31m"
#define COLOR_VERDE "\x1b[32m"
#define COLOR_AMARILLO "\x1b[33m"
#define COLOR_AZUL "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CIAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"

#define TIME 1

sem_t semRueda, semCuadro, semMotor, semPintores, semEquipamiento;

void *operarioRueda(void *arg) {
    while (1) {
        sem_wait(&semRueda);
        printf(COLOR_CIAN "El operario 1 arma una rueda.\n" COLOR_RESET);
        sleep(TIME);
        sem_post(&semCuadro);
    }
    pthread_exit(NULL);
}

void *operarioCuadro(void *arg) {
    while (1) {
        sem_wait(&semCuadro);
        sem_wait(&semCuadro);
        printf(COLOR_AMARILLO "El operario 2 arma el cuadro (chasis).\n" COLOR_RESET);
        sleep(TIME);
        sem_post(&semMotor);
    }
    pthread_exit(NULL);
}

void *operarioMotor(void *arg) {
    while (1) {
        sem_wait(&semMotor);
        printf(COLOR_MAGENTA "El operario 3 agrega el motor al vehículo.\n" COLOR_RESET);
        sleep(TIME);
        sem_post(&semPintores);
    }
    pthread_exit(NULL);
}

void *operarioPintor1(void *arg) {
    while (1) {
        sem_wait(&semPintores);
        printf(COLOR_VERDE "El operario 4 pinta de verde la moto.\n" COLOR_RESET);
        sleep(TIME);
        sem_post(&semEquipamiento);
    }
    pthread_exit(NULL);
}

void *operarioPintor2(void *arg) {
    while (1) {
        sem_wait(&semPintores);
        printf(COLOR_ROJO "El operario 5 pinta de rojo la moto.\n" COLOR_RESET);
        sleep(TIME);
        sem_post(&semEquipamiento);
    }
    pthread_exit(NULL);
}

void *operarioEquipamientoExtra(void *arg) {
    while (1) {
        sem_wait(&semEquipamiento);
        sem_post(&semRueda);
        sem_post(&semRueda);

        sem_wait(&semEquipamiento);
        printf(COLOR_AZUL "El operario 6 agrega equipamiento extra a la moto.\n" COLOR_RESET);
        sleep(TIME);
        sem_post(&semRueda);
        sem_post(&semRueda);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t rueda_t, cuadro_t, motor_t, pintor1_t, pintor2_t, equipamiento_t;  

    sem_init(&semRueda, 0, 2);
    sem_init(&semCuadro, 0, 0);
    sem_init(&semMotor, 0, 0);
    sem_init(&semPintores, 0, 0);
    sem_init(&semEquipamiento, 0, 0);

    pthread_create(&rueda_t, NULL, operarioRueda, NULL);
    pthread_create(&cuadro_t, NULL, operarioCuadro, NULL);
    pthread_create(&motor_t, NULL, operarioMotor, NULL);
    pthread_create(&pintor1_t, NULL, operarioPintor1, NULL);
    pthread_create(&pintor2_t, NULL, operarioPintor2, NULL);
    pthread_create(&equipamiento_t, NULL, operarioEquipamientoExtra, NULL);

    pthread_join(rueda_t, NULL);
    pthread_join(cuadro_t, NULL);
    pthread_join(motor_t, NULL);
    pthread_join(pintor1_t, NULL);
    pthread_join(pintor2_t, NULL);
    pthread_join(equipamiento_t, NULL);

    sem_destroy(&semRueda);
    sem_destroy(&semEquipamiento);
    sem_destroy(&semMotor);
    sem_destroy(&semPintores);
    sem_destroy(&semEquipamiento);

    return 0;
}