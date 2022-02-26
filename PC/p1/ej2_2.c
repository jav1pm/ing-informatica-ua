/* ejercicio 2 , apartado 2 */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_HILOS 3

typedef struct {
    char c;
    int veces;
} EST_CHAR;

void imprimir(EST_CHAR e) {

    for(int i = 0; i < e.veces; i++) {
        printf("%c", e.c);
    }
    printf("\n");
}

void *codigo_del_hilo (void *id){

    EST_CHAR e;

    switch(*(int *) id) {
        case 1: e.c = 'A'; e.veces = 50; // Hilo 1
        break;
        case 2: e.c = 'B'; e.veces = 100; // Hilo 2
        break;
        case 3: e.c = 'C'; e.veces = 150; // Hilo 3
        break;
    }
    imprimir(e);
   pthread_exit (id);
}

int main(){
   int h;
   pthread_t hilos[NUM_HILOS];
   int id[NUM_HILOS] = {1,2,3};
   int error;
   int *salida;

   for(h = 0; h < NUM_HILOS; h++){
      error = pthread_create( &hilos[h], NULL, codigo_del_hilo, &id[h]);
      if (error){
        fprintf (stderr, "Error: %d: %s\n", error, strerror (error));
        exit(-1);
      }
   }
   for(h = 0; h < NUM_HILOS; h++){
      error = pthread_join(hilos[h], (void **)&salida);
      if (error) {
          fprintf (stderr, "Error: %d: %s\n", error, strerror (error));
      }
      else {
          printf ("Hilo %d terminado\n", *salida);
      }
   }
}