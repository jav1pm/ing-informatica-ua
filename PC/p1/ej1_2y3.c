/* ejercicio 1 , apartado 2 y 3. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROCESOS 2

void imprimir(int id) {
  printf("Proceso (id=%d)\n", id);
}

int main() {
  int p;
  int id[NUM_PROCESOS] = {1, 2}; // 2 procesos
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
