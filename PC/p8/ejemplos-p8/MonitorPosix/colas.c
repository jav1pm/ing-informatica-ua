#include "colas.h"
#include "errores.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

/***
 * reservar_memoria: reserva memoria para la cola en funcion de su
 * capacidad y del tamaño de los elementos
 ***/

struct elem_c *reservar_memoria (unsigned capacidad, size_t tam_elem)
{
  int i;
  struct elem_c *ptr_elem;

  /* Reserva de memoria para la cola */
    ptr_elem = (struct elem_c *)malloc (capacidad*sizeof(struct elem_c));
  if(ptr_elem == NULL)
    error_fatal (errno,"malloc");

  /* Reserva de memoria para los elementos */
  for(i = 0; i < (int)capacidad; i++){
    ptr_elem[i].elem = (elem_t *) malloc (tam_elem);
    if(ptr_elem[i].elem == NULL)
      error_fatal(errno, "malloc");
  }
  return ptr_elem;
}

/***
 * poner_en_la_cola: introduce un elemento en la cola
 ***/

int poner_en_la_cola (cola_t *cola, elem_t *elem, unsigned prio)
{
  int error;

  /* Esperamos por el cerrojo de la cola */
  error = pthread_mutex_lock (&cola->cerrojo);
  if(error)
    error(error, "pthread_mutex_lock");

  /* Esperamos a que haya sitio en la cola */
  while( cola->num_elem == cola->capacidad){
    error = pthread_cond_wait ( &cola->hay_sitio, &cola->cerrojo );
    if(error)
      error(error, "pthread_cond_wait");
  }

  /* Ya hay sitio. Ponemos el elemento en la cola */
  cola->ptr_base[cola->ultimo].prio = prio;
  memcpy (cola->ptr_base[cola->ultimo].elem, elem, cola->tam_elem);
  cola->ultimo = (cola->ultimo + 1) % cola->capacidad;
  ++cola->num_elem;

    /* Indicamos que hay elementos en la cola */
  error = pthread_cond_signal (&cola->hay_elementos);
  if(error)
    error(error, "pthread_cond_wait");

  /* Salimos de la seccion critica, es decir, devolvemos el cerrojo */
  error = pthread_mutex_unlock (&cola->cerrojo);
  if(error)
    error(error, "pthread_mutex_unlock");

  return 0;
}

/***
 * quitar_de_la_cola: saca de la cola el elemento de mayor prioridad.
 * Si hay varios de igual prioridad, saca el mas antiguo
 ***/

int quitar_de_la_cola (cola_t *cola, elem_t *elem, unsigned *prio)
{
  int error;
  int i,j,max;
  struct elem_c aux;

  error = pthread_mutex_lock (&cola->cerrojo);
  if (error)
    error (error, "pthread_mutex_lock");

  /* Esperamos a que haya algun elemento en la cola */
  while( cola->num_elem == 0 ) {
    error = pthread_cond_wait (&cola->hay_elementos, &cola->cerrojo);
    if (error)
      error (error, "pthread_cond_wait");
  }

  /* Ya hay algun elemento. Buscamos el elemento de mayor prioridad */
  i = max = cola->primero;
  do{
    if(cola->ptr_base[i].prio > cola->ptr_base[max].prio)
      max = i;
    i = (i+1)%cola->capacidad;
  }while (i != cola->ultimo);

  /* Extraemos el elemento */
  memcpy (elem, cola->ptr_base[max].elem, cola->tam_elem);
  *prio = cola->ptr_base[max].prio;

  if (max == cola->primero)
    cola->primero = (cola->primero+1) % cola->capacidad;
  else{
    /* Recolocamos el resto de elementos para que no queden huecos en
       la cola */
    i = max;
    j = (max+1)%cola->capacidad;
    aux = cola->ptr_base[i];
    /* Esta recolocacion esta acotada en el tiempo y no depende del
       tamano del elemento ya que no movemos elementos sino enlaces a
       elementos */
    while (j != cola->ultimo) {
      cola->ptr_base[i] = cola->ptr_base[j];
      i = j;
      j = (j+1) % cola->capacidad;
    }
    cola->ptr_base[i] = aux;
    cola->ultimo = i;
  }
  --cola->num_elem;

  /* Indicamos que ya hay sitio libre en la cola */
  error = pthread_cond_signal (&cola->hay_sitio);
  if (error)
    error (error, "pthread_cond_signal");

  /* Salimos de la seccion critica */
  error = pthread_mutex_unlock(&cola->cerrojo);
  if (error)
    error (error, "pthread_mutex_unlock");

  return 0;
}
