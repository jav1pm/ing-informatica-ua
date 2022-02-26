// Francisco Javier Pérez Martínez

/**************************************/
/*       Problema de la barbería      */
/**************************************/

// # Compilación : gcc -o barberia barberia.c -lpthread

// # Observaciones :
//
// 1. Se ha añadido un retardo en cada mensaje de acción para observar mejor la ejecución del programa.
// 2. El programa termina cuando no queden más clientes que atender.

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

const int NUM_BARBEROS = 3;
const int NUM_CLIENTES = 25;

sem_t max_capacidad; // controla la capacidad de clientes que tiene la barbería. Inicializado a  20
sem_t sofa; // controla el uso del sofá de los clientes. Inicializado a  4
sem_t silla_barbero; // controla las sillas que usan los barberos para cortar el pelo. Inicializado a 3
sem_t cliente_listo; // este semáforo sirve para indicar que el cliente ya esta sentado en la silla.
sem_t terminado; // indica que el corte de pelo ha terminado. Inicializado a 0.
sem_t dejar_silla_barbero; // usado cuando el cliente abandona la silla después del corte de pelo. Inicializado a 0.
sem_t pago; // controla el pago de los clientes. Inicializado a 0.
sem_t recibo; // entrega al cliente de un recibo de pago, indica que se ha aceptado el pago. Inicializado a 0.
sem_t coord; // controla la ocupación de los barberos, tanto para cortar el pelo como para cobrar. Inicializado a 3.

void *barbero(void *id) {

    while (1) {
        sem_wait(&cliente_listo); // barbero queda a la espera de que el cliente esté listo (sentarse en la silla).
        sem_wait(&coord); // barbero ocupado.
        // cortar pelo
        printf("Barbero %d cortando pelo\n", *(int *)id);
        sleep(2);
        sem_post(&coord); // liberar ocupacion.
        sem_post(&terminado); // corte de pelo finalizado.
        sem_wait(&dejar_silla_barbero); // el cliente deja la silla.
        sem_post(&silla_barbero); // silla del barbero libre.
    }
    pthread_exit(id);
}

void *cajero(void *id) {

    while (1) {
        sem_wait(&pago); // esperar algun pago.
        sem_wait(&coord); // cajero ocupado.
        // cobrar
        printf("Cobrando ... \n");
        sleep(2);
        sem_post(&coord); // liberar ocupacion.
        sem_post(&recibo); // pago aceptado, entrega de recibo.
    }
    pthread_exit(id);
}

void *cliente(void * id) {

    int i = *(int *) id;

    sem_wait(&max_capacidad); // espera un nuevo cliente - limitado a 20.
    // Entrar a barberia
    printf("Cliente %d entra\n", i);
    sleep(1);
    sem_wait(&sofa); // espera en el sofa.
    printf("Cliente %d se sienta en el sofa\n", i);
    sleep(1);
    sem_wait(&silla_barbero); // esperando a ser llamado.
    // levantarse sofa
    printf("Cliente %d se levanta del sofa\n", i);
    sleep(1);
    sem_post(&sofa); // cliente en pie.
    // sentarse silla barbero
    printf("Cliente %d se sienta en la silla del barbero\n", i);
    sleep(1);
    sem_post(&cliente_listo); // cliente listo, se encuentra en la silla.
    sem_wait(&terminado); // espera a que termine su corte.
    // levantarse silla barbero
    printf("Cliente %d se levanta de la silla del barbero\n", i);
    sleep(1);
    sem_post(&dejar_silla_barbero); // una vez finalizado, se levanta.
    // pagar
    printf("Cliente %d realiza el pago\n", i);
    sleep(1);
    sem_post(&pago); // cliente ya ha pagado.
    sem_wait(&recibo); // esperando recibo.
    // salir tienda
    printf("Cliente %d sale de la barbería\n", i);
    sleep(1);
    sem_post(&max_capacidad); // cliente sale de la barberia.

    pthread_exit(id);
}

int main() {

    pthread_t thCliente[NUM_CLIENTES];
    pthread_t thBarbero[NUM_BARBEROS];
    pthread_t thCajero;
    int id_cliente[NUM_CLIENTES];
    int id_barbero[NUM_BARBEROS];

    int h;
    int error;
    int *salida;
    
    // Inicializacion de semaforos
    sem_init(&max_capacidad, 0, 20);
    sem_init(&sofa, 0, 4);
    sem_init(&silla_barbero, 0, 3);
    sem_init(&cliente_listo, 0, 0);
    sem_init(&terminado, 0 , 0);
    sem_init(&dejar_silla_barbero, 0 , 0);
    sem_init(&pago, 0 , 0);
    sem_init(&recibo, 0 , 0);
    sem_init(&coord, 0 , 3);


    // crear barberos
    for (h = 0; h < NUM_BARBEROS; h++) {
        id_barbero[h] = h;
        error = pthread_create(&thBarbero[h], NULL, barbero, &id_barbero[h]);
        if (error) {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
            exit(-1);
        }
    }

    // crear clientes
    for (h = 0; h < NUM_CLIENTES; h++) {
        id_cliente[h] = h;
        error = pthread_create(&thCliente[h], NULL, cliente, &id_cliente[h]);
        if (error) {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
            exit(-1);
        }
    }

    // Cajero
    pthread_create(&thCajero, NULL, cajero, &h);

    // terminar clientes
    for (h = 0; h < NUM_CLIENTES; h++) {
        error = pthread_join(thCliente[h], (void **)&salida);
        if (error) {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
        }
    }

    // Cerrar todos los semaforos
    sem_destroy(&max_capacidad);
    sem_destroy(&sofa);
    sem_destroy(&silla_barbero);
    sem_destroy(&cliente_listo);
    sem_destroy(&terminado);
    sem_destroy(&dejar_silla_barbero);
    sem_destroy(&pago);
    sem_destroy(&recibo);
    sem_destroy(&coord);

    return 0;
}