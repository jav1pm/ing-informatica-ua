// Francisco Javier Pérez Martínez

/**********************************************************/
/*      Lectores/Escritores con prioridad de lectura      */
/**********************************************************/

/*
 * - Si hay algún lector en la sección crítica otros lectores pueden entrar.
 * - Un escritor solamente puede entrar en la sección crítica si no hay ningún proceso.
 * - Problema: Inanición para los escritores.
*/

// Compilación : gcc -o p5 p5.c -lpthread

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

int LECTORES = 10;
int ESCRITORES = 5;

// Semaforos
sem_t mx, writer;

// nº lectores en la seccion critica
int readers = 0;

// recurso
int recurso = -1;

// Prioridad lector

void reader_lock() {
    sem_wait(&mx);
    readers++;
    
    if (readers == 1) {
        sem_wait(&writer);
    }
    sem_post(&mx);
}

void reader_unlock() {
    sem_wait(&mx);
    readers--;

    if (readers == 0) {
        sem_post(&writer);
    }
    sem_post(&mx);
}

// Funciones lector-escritor

void *lector(void *id) {

    for(int i = 0; i < LECTORES; i++) {
        reader_lock();
        printf("El lector %d ha leido un valor de %d\n", *(int*) id, recurso);
        reader_unlock();
        usleep(rand()%5); // pequeño retardo aleatorio
    }
    pthread_exit(id);
}

void *escritor(void *id) {

    for(int i = 0; i < ESCRITORES; i++) {
        sem_wait(&writer);
        printf("El escritor %d ha actualizado el recurso\n", *(int*) id);
        recurso = *(int*) id; // modificar el recurso
        sem_post(&writer);
        usleep(rand()%5); // pequeño retardo aleatorio
    }
    pthread_exit(id);
}

void crear_hilos(pthread_t hilos[], int id[], int num, void *(*func) (void*)) {

    for (int i = 0; i < num; i++) {
        id[i] = i;
        int error = pthread_create(&hilos[i], NULL, func, &id[i]);
        if (error) {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
            exit(-1);
        }
    }
}

void terminar_hilos(pthread_t hilos[], int num) {
    
    int *salida;

    for (int i = 0; i < num; i++) {
        int error = pthread_join(hilos[i], (void **) &salida);
        if (error) {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
        }
    }
}

// Funcion principal
int main() {
    pthread_t tidlector[LECTORES], tidescritor[ESCRITORES];
    int id_lec[LECTORES], id_esc[ESCRITORES];
    
    // Inicializacion de semaforos
    sem_init(&mx, 0, 1);
    sem_init(&writer, 0, 1);

    // Se crean los hilos
    crear_hilos(tidescritor, id_esc, ESCRITORES, escritor);
    crear_hilos(tidlector, id_lec, LECTORES, lector);

    // Se espera a que los hilos terminen
    terminar_hilos(tidlector, LECTORES);
    terminar_hilos(tidescritor, ESCRITORES);

    // Cerrar todos los semaforos
    sem_destroy(&mx);
    sem_destroy(&writer);

    return 0;
}