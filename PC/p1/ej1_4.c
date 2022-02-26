/* ejercicio 1 , apartado 4. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROCESOS 3
#define VECES 5

void imprimir(char c) {
  for(int i = 0; i < VECES; i++) {
      printf("%c", c);
  }
  printf("\n");
}

int main() {
  int p;
  char id[NUM_PROCESOS] = {'A', 'B', 'C'}; // 3 procesos 
  int pid;
  int salida;

  for (p = 0; p < NUM_PROCESOS; p++) {
    pid = fork();
    if (pid == -1) { // no se ha podido crear el hijo
      perror("Error al crear un proceso: ");
      exit(-1);
    } else if (pid == 0) { // codigo del hijo
        imprimir(id[p]);
        exit(id[p]);
    }
  }

  // Codigo del padre
  for (p = 0; p < NUM_PROCESOS; p++) {
    pid = wait(&salida);
    printf("Proceso(pid=%d) con id = %x terminado y status = %d \n", pid, salida >> 8, WEXITSTATUS(salida));
  }
  return 0;
}
