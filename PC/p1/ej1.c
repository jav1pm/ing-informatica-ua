/* procesos */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROCESOS 5

int I = 0;

void codigo_del_proceso(int id) { // función que realiza cada hijo
  int i;

  for (i = 0; i < 50; i++)
    printf("Proceso(id=%d): i = %d, I = %d\n", id, i, I++);

  // el id se almacena en los bits 8 al 15 antes de devolverlo al padre
  exit(id);
}

int main() {
  int p;
  int id[NUM_PROCESOS] = {1, 2, 3, 4, 5}; // crear 5 procesos hijos y el proceso padre se dedica a esperar a que acabe.
  int pid;
  int salida;

  for (p = 0; p < NUM_PROCESOS; p++) {
    pid = fork();
    if (pid == -1) { // maquina sin memoria,etc no se ha podido crear el hijo.
      perror("Error al crear un proceso: ");
      exit(-1);
    } else if (pid == 0) // si devuelve un 0  estamos en el codigo del hijo y si devuelve un valor positivo estamos en el proceso padre y al padre se le devuelve el pid de ese proceso hijo.
      codigo_del_proceso(id[p]);
  }

  // Codigo del padre
  for (p = 0; p < NUM_PROCESOS; p++) {
    pid = wait(&salida); // el padre se queda esperando a que acaben los hijos.
    printf("Proceso(pid=%d) con id = %x terminado y status = %d \n", pid, // pid del hijo que ha terminado,
           salida >> 8, WEXITSTATUS(salida));
           // desplazar 8 bits y nos quedamos con el valor 
  }
  return 0;
}