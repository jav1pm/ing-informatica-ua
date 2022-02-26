// Francisco Javier Pérez Martínez

#ifndef _COMIDA_H_
#define _COMIDA_H_
#include <sys/types.h>
#include <pthread.h>

#define NUM_FILOSOFOS 5

// estructura del monitor que controla la comida
typedef struct comida {
    // nº de palillos disponibles de cada filosofo, de 0 a 2.
    int palillos[NUM_FILOSOFOS];
    // semaforo para acceder a la sección crítica
    pthread_mutex_t cerrojo;
    // variable de condicion por cada filosofo
    pthread_cond_t puedeComer[NUM_FILOSOFOS];
}comida_t;

// Inicialmente los filosofos pueden comer y los palillos estan disponibles = 2
#define INICIALIZAR_COMIDA { \
    {[0 ... (NUM_FILOSOFOS - 1)] = 2}, \
    PTHREAD_MUTEX_INITIALIZER, \
    {[0 ... (NUM_FILOSOFOS - 1)] = PTHREAD_COND_INITIALIZER} \
}

// devuelve el palillo de la derecha del filósofo dado.
int palillo_der(int id);
// devuelve el palillo de la izquierda del filósofo dado.
int palillo_izq(int id);

void coger_palillo(comida_t *c, int id);
void dejar_palillo(comida_t *c, int id);

#endif