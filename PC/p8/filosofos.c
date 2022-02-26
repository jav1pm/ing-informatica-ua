// Francisco Javier Pérez Martínez

/******************************************************************/
/*      Problema de la comida de los filósofos con monitores      */
/******************************************************************/

// # Compilación : gcc -o filosofos filosofos.c comida.c -lpthread

#include "comida.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

// veces que come un filosofo
#define VECES_COME 5

// puntero al monitor
comida_t *c;

void pensar(int id) {
    printf("El filosofo %d esta pensando\n", id);
    sleep(0.5);
}

void comer(int id) {
    printf("El filosofo %d esta comiendo\n", id);
    sleep(1);
    printf("El filosofo %d ya ha comido\n", id);
}

void *codigo_fil(void * id) {

    int i = *(int *) id;

    for (int h = 0; h < VECES_COME; h++) {
        // piensa
        pensar(i);
        // coge palillos
        coger_palillo(c, i);
        // come 
        comer(i);
        // deja palillos
        dejar_palillo(c, i);
    }
    pthread_exit(id);
}

int main(){
    pthread_t thFil[NUM_FILOSOFOS];
    int filosofos[NUM_FILOSOFOS];

    int h;
    int error;
    int *salida;

    // inicializar el monitor que controla la comida
    comida_t comida = INICIALIZAR_COMIDA;
    c = &comida;

    // crear filosofos
    for (h = 0; h < NUM_FILOSOFOS; h++) {
        filosofos[h] = h;
        error = pthread_create(&thFil[h], NULL, codigo_fil, &filosofos[h]);
        if (error) {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
            exit(-1);
        }
    }

    // terminar filosofos
    for (h = 0; h < NUM_FILOSOFOS; h++) {
        error = pthread_join(thFil[h], (void **)&salida);
        if (error) {
            fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
        }
    }

    return 0;
}