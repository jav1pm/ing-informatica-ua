/***
  $ prueba-colas

  Programa para probar el modulo colas.c
  Compilacion:
    gcc -o pruba-colas prueba-colas.c colas.c -lpthread
***/

#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "errores.h"
#include "colas.h"

typedef struct {
  int sec;
  char datos[11];
} mensaje_t;

void *cod_del_emisor (void *arg)
{
  cola_t *cola = (cola_t *)arg;
  struct timespec retardo = {0, 250000000}; /* 0 seg, 250 ms */
  int i;
  int error;
  mensaje_t msg;

  for (i = 1; i <= 100; i++){
    msg.sec = i;
    /* Uno de cada 10 mensajes lleva prioridad mas alta */
    if (i%10 == 0)
      strncpy (msg.datos, "URGENTE", sizeof (msg.datos));
    else
      strncpy (msg.datos, "normal", sizeof (msg.datos));
    error = poner_en_la_cola (cola, (elem_t *)&msg, i%10 == 0 ? 2:1);
    if (error)
      error_fatal (error, "poner_en_la_cola");
    error = nanosleep (&retardo, NULL);
    if (error == -1)
      error_fatal (error, "nanosleep");
  }

  ++msg.sec;
  strncpy (msg.datos, "FIN", sizeof (msg.datos));
  poner_en_la_cola (cola, (elem_t *)&msg, 0);
  printf("Fin del emisor.\n");

  pthread_exit(0);
}

void *cod_del_receptor (void *arg)
{
  cola_t *cola = (cola_t *)arg;
  struct timespec retardo = {1,0}; /* 1 seg, 0 ns */
  int prio;
  int error;
  mensaje_t msg;

  do {
    error = quitar_de_la_cola (cola, (elem_t *)&msg, &prio);
    if (error)
      error_fatal (error, "quitar_de_la_cola");
    printf("Mensaje %d %s con prioridad %d\n", msg.sec, msg.datos, prio);
    error = nanosleep (&retardo, NULL);
    if (error == -1)
      error_fatal (error, "nanosleep");
  } while (strcmp(msg.datos, "FIN") != 0);
  printf("Fin del receptor.\n");

  pthread_exit(0);
}

int main (int argc, char *argv[])
{
  cola_t cola = INICIALIZAR_LA_COLA (32, mensaje_t);
  pthread_t emisor, receptor;
  int error;

  /* Creacion de los hilos */
  error = pthread_create(&emisor,NULL,cod_del_emisor, (void *)&cola);
  if (error)
    error_fatal( error, "pthread_create");
  error = pthread_create(&receptor,NULL,cod_del_receptor, (void *)&cola);
  if (error)
    error_fatal( error, "pthread_create");

  /* Esperamos la terminacion de los hilos */
  error = pthread_join(emisor,NULL);
  if (error)
    error_fatal( error, "pthread_join");
  error = pthread_join(receptor,NULL);
  if (error)
    error_fatal( error, "pthread_join");

  printf("Fin del hilo principal.\n");

  return 0;
}
