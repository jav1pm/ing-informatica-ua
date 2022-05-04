#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {


  int x = atoi (argv[1]);
  int y = atoi (argv[2]);
  int e;
  int vectorHijo[x + 1];
  int padre;//padres de los hijos finales
  int hijos;//hijos finales
  int superPadre;//guarda el super padre


  if (fork () == 0) {
    superPadre = getppid();
  }
  else {
    wait(&e);
    exit(0);
  }
  for (int j = 1; j < x; j++) {
    if(fork()==0){
      if(j==1){
        vectorHijo[0] = getpid();
        vectorHijo[1] = getppid();
      }
      else {
        vectorHijo[j] = getpid();
      }
    }
    else {
      wait(&e);
      exit(0);
    }
  }
      for(int i=0;i<y;i++) {
        if(fork()==0) {
          if(i==0){
            printf("Soy el super padre(%d): mis hijos finales son: ",superPadre);//mostramos el padre de arriba con sus hijos
          }
          hijos = getpid();

          printf("%d ", hijos);//hijos finales de 
          if(i==y-1){
              printf("\n");
              /*
              *muestra los padres de cada hijo final
              */
              for(int j=1;j<y+1;j++){
                padre = hijos - y  + j;
                    
                    printf("Soy el subhijo %d, mis padres son: ", padre);
                    for(int l = 0; l < x; l++) {//muestra los hijos del super padre
                        printf("%d ", vectorHijo[l]);
                      }
                      printf("\n");
              }
            
          }
          exit(0);
        }
        else {
          wait(&e);
        }
      }
      

}



