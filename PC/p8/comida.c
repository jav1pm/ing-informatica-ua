// Francisco Javier Pérez Martínez

#include "comida.h"
#include <stdio.h>

int palillo_der(int id) {
    return (id + NUM_FILOSOFOS - 1) % NUM_FILOSOFOS;
}

int palillo_izq(int id) {
    return (id + 1) % NUM_FILOSOFOS;
}

void coger_palillo(comida_t *c, int id) {

    // bloquear acceso a la seccion critica.
    pthread_mutex_lock(&c->cerrojo);
    while(c->palillos[id] != 2) {
        // en espera hasta que dos palillos esten disponibles.
        pthread_cond_wait(&c->puedeComer[id], &c->cerrojo);
    }
    // coger 2 palillos, tanto el izquierdo como el derecho.
    // el filosofo adyacente tiene un palillo menos.
    c->palillos[palillo_izq(id)] -= 1;
    c->palillos[palillo_der(id)] -= 1;
    printf("El filosofo %d coge los palillos\n", id);
    pthread_mutex_unlock(&c->cerrojo);
    // desbloquear acceso a la seccion critica.
}

void dejar_palillo(comida_t *c, int id) {

    // bloquear acceso a la seccion critica.
    pthread_mutex_lock(&c->cerrojo);
    printf("El filosofo %d deja los palillos\n", id);

    // los filosofos adyacentes tendran un palillo mas.
    c->palillos[palillo_izq(id)] += 1;
    c->palillos[palillo_der(id)] += 1;

    // si tienen 2 palillos disponibles, ya pueden comer.
    if (c->palillos[palillo_izq(id)] == 2) {
        pthread_cond_signal(&c->puedeComer[palillo_izq(id)]);
    }
    if (c->palillos[palillo_der(id)] == 2) {
        pthread_cond_signal(&c->puedeComer[palillo_der(id)]);
    }
    pthread_mutex_unlock(&c->cerrojo);
    // desbloquear acceso a la seccion critica.
}