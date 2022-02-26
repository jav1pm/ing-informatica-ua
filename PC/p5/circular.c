/*************************************************************************/
/*      gcc -o buffer-circular-hilos buffer-circular-hilos.c -lpthread   */
/*************************************************************************/
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

#define TAMBUF 8     // Tamaño del búfer circular
#define NUMDATOS 100 // Número de datos a enviar

// El buffer circular y los correspondientes punteros
int buffer[TAMBUF];
int bufin = 0;
int bufout = 0;

// Semaforo binario
pthread_mutex_t buffer_lock = PTHREAD_MUTEX_INITIALIZER;

// Variable suma
unsigned long sum = 0;

// Semaforos generales
sem_t hay_datos;
sem_t hay_sitio;

// Funciones de escritura y lectura del buffer circular
void obten_dato(int *itemp) {
    pthread_mutex_lock(&buffer_lock);
    *itemp = buffer[bufout];
    bufout = (bufout + 1) % TAMBUF;
    pthread_mutex_unlock(&buffer_lock);

    return;
}

void pon_dato(int item) {
    pthread_mutex_lock(&buffer_lock);
    buffer[bufin] = item;
    bufin = (bufin + 1) % TAMBUF;
    pthread_mutex_unlock(&buffer_lock);
    return;
}

// Funciones productor-consumidor
void *productor(void *arg1) {
    int i;

    for (i = 1; i <= NUMDATOS; i++) {
        sem_wait(&hay_sitio);
        pon_dato(i*i);
        sem_post(&hay_datos);
    }

    pthread_exit( NULL );
}

void *consumidor(void *arg2) {
    int i, midato;

    for (i = 1; i<= NUMDATOS; i++) {
        sem_wait(&hay_datos);
        obten_dato(&midato);
        sem_post(&hay_sitio);
        sum += midato;
    }

    pthread_exit( NULL );
}


// Funcion principal
int main() {
    pthread_t tidprod, tidcons;
    unsigned long i, total;

    total = 0;

    for (i = 1; i <= NUMDATOS; i++)
        total += i*i;

    printf("El resultado deberia ser %u\n", total);

    // Inicializacion de semaforos
    sem_init(&hay_datos, 0, 0);
    sem_init(&hay_sitio, 0, TAMBUF);

    // Se crean los hilos
    pthread_create(&tidprod, NULL, productor, NULL);
    pthread_create(&tidcons, NULL, consumidor, NULL);

    // Se espera a que los hilos terminen
    pthread_join(tidprod, NULL);
    pthread_join(tidcons, NULL);

    printf("Los hilos produjeron el valor %u\n", sum);

    return 0;
}