// Francisco Javier Pérez Martínez

/**************************************/
/*      Problema de los caníbales     */
/**************************************/

// Compilación : gcc -o canibales canibales.c -lpthread

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

int CANIBALES = 20; // nº de miembros de la tribu
const int M = 5; // nº de misioneros.
int olla = M; // nº de misioneros en la olla.

sem_t mutex; // proteger la exclusión mutua sobre la variable olla.
sem_t espera; // el canibal que va a cenar se detiene hasta que el cocinero llene la olla cuando está vacía.
sem_t coci; // el cocinero no hace nada cuando la olla está llena.

void *cocinero () {

    while (1) {
        sem_wait(&coci); // cocinero en espera
        olla = M; // llena la olla cuando está vacia
        printf("Cocinero llenando la olla...\n");
        sem_post(&espera); // olla llena, el canibal ya puede cenar
    }
}

void *canibal (void *id) {
    
    sem_wait(&mutex);
    if (olla == 0) { // Si no hay misioneros en la olla...
        sem_post(&coci); // despertar al cocinero
        sem_wait(&espera); // esperar a que llene la olla
    }
    olla--;
    printf("Canibal %d comiendo, misioneros restantes: %d\n", *(int*) id, olla);
    sem_post(&mutex);
}

// Funcion principal
int main() {

    pthread_t tidcanibal[CANIBALES];
    pthread_t thCocinero;
    int id_canibal[CANIBALES];

    int h;
    int error;
    int *salida;
    
    // Inicializacion de semaforos
    sem_init(&mutex, 0, 1);
    sem_init(&espera, 0, 0);
    sem_init(&coci,0, 0);

    // crear canibales
    for (h = 0; h < CANIBALES; h++) {
        id_canibal[h] = h;
        error = pthread_create(&tidcanibal[h], NULL, canibal, &id_canibal[h]);
        if (error) {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
            exit(-1);
        }
    }

    // Cocinero
    pthread_create(&thCocinero, NULL, cocinero, NULL);

    // terminar canibales
    for (h = 0; h < CANIBALES; h++) {
        error = pthread_join(tidcanibal[h], (void **)&salida);
        if (error) {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
        }
    }

    printf("Todos los miembros de la tribu han cenado\n");

    // Cerrar todos los semaforos
    sem_destroy(&mutex);
    sem_destroy(&espera);
    sem_destroy(&coci);

    return 0;
}