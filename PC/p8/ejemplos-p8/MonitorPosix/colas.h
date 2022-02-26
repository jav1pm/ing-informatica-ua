#ifndef _COLAS_H_
#define _COLAS_H_
#include <sys/types.h>
#include <pthread.h>

/* Tipo de los elementos de la cola. Estes es el tipo que emplea el usuario */
typedef char elem_t;

/* Elementos de la cola. Este es el tipo empleado internamente en la codificacion de
   las operaciones y, como vemos, se le asocia una prioridad a cada elemento que se
   pone en la cola */
struct elem_c {
  unsigned prio;
  elem_t *elem;
};

typedef struct cola {
  unsigned capacidad;
  size_t tam_elem;
  struct elem_c *ptr_base;
  int primero;
  int ultimo;
  unsigned num_elem;
  pthread_mutex_t cerrojo;
  pthread_cond_t hay_elementos;
  pthread_cond_t hay_sitio;
}cola_t;

#define INICIALIZAR_LA_COLA(capacidad, tipo_elem) {       \
    (capacidad),                                          \
      sizeof (tipo_elem),                                 \
      reservar_memoria ((capacidad), sizeof(tipo_elem)),  \
      0,                                                  \
      0,                                                  \
      0,                                                  \
      PTHREAD_MUTEX_INITIALIZER,                          \
      PTHREAD_COND_INITIALIZER,                           \
      PTHREAD_COND_INITIALIZER                            \
      }

struct elem_c* reservar_memoria(unsigned capacidad, size_t tam_elem);
int poner_en_la_cola (cola_t *cola, elem_t *elem, unsigned prio);
int quitar_de_la_cola (cola_t *cola, elem_t *elem, unsigned *prio);

#endif
