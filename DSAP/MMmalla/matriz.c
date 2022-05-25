#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define MAXBLOQTAM 100
#define rmax 4

int main(int argc, char **argv) {

    int myrank, numprocs, bloqtam, r, tamBuffer;
    int fila, columna, error;
    double *a, *b, *c, *buffer;
    double *atmp;

    int *mifila;
    MPI_Status estado;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    if (myrank == 0) {

        // calcular r
        r = sqrt(numprocs);

        if (r > rmax) {
            printf("La dimensión de las matrices no puede ser mayor que 4\n");
            MPI_Finalize();
            return 0;
        }

        if (r * r != numprocs) {
            printf("El nº de procesadores debe ser un cuadrado perfecto\n");
            MPI_Finalize();
            return 0;
        }

        while ((bloqtam <= 0 ) || (bloqtam > MAXBLOQTAM)) {

            // leer bloqtam
            printf("Introduce el tamaño del bloque: ");
            scanf("%d", &bloqtam);

            if (bloqtam > MAXBLOQTAM) {
                printf("El valor introducido debe ser menor de %d \n", MAXBLOQTAM);
            }
        }
    }

    // Enviar bloqtam y r con Bcast()
    MPI_Bcast(&r, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&bloqtam, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // inicializar bloques de matrices
    a = malloc(bloqtam*bloqtam * sizeof(double));
    b = malloc(bloqtam*bloqtam * sizeof(double));
    c = malloc(bloqtam*bloqtam * sizeof(double));
    atmp = malloc(bloqtam*bloqtam * sizeof(double));

    // calcular la posición en la malla (fila, columna)
    fila = myrank / r;
    columna = myrank % r;

    // definir bloques a,b,c
    definir_bloques(a, b, c, bloqtam, fila, columna);

    // calculamos el proceso arriba y abajo
    int arriba, abajo;
    
    if (fila == 0) { // caso: estoy en la primera fila
        arriba = (r - 1)*r + columna; // el proceso arriba estará en la ultima fila
        abajo = (fila + 1)*r + columna;
    }
    else if (fila == r - 1) { // caso:  estoy en la ultima fila
        arriba = (fila - 1)*r + columna;
        abajo = columna; // el proceso abajo estará en la primera fila (0 + columna)
    }
    else { // resto de casos
        arriba = (fila - 1)*r + columna;
        abajo = (fila + 1)*r + columna;
    }

    // calcular los procesos en mi fila
    mifila = malloc((r-1) * sizeof(int));
    calcular_miFila(mifila, r, fila, columna, numprocs, myrank);

    // para el envío de mensajes en modo buffered
    MPI_Pack_size(bloqtam*bloqtam, MPI_DOUBLE, MPI_COMM_WORLD, &tamBuffer);
    tamBuffer = numprocs * (tamBuffer + MPI_BSEND_OVERHEAD);
    buffer = malloc(tamBuffer * sizeof(double));
    MPI_Buffer_attach(buffer, tamBuffer);

    // Algoritmo de cannon
    for (int k = 0; k < r; k++) { // k iteraciones
        if (columna == (fila+k) % r) {
            // Mandar a; a todos los procesadores de mi fila
            for (int i = 0; i < r-1; i++) {
                MPI_Send(a, bloqtam*bloqtam, MPI_DOUBLE, mifila[i], k, MPI_COMM_WORLD);
            }
            mult(a, b, c, bloqtam);
        }
        else {
            // Recibir A y almacenarlo en atmp
            MPI_Recv(atmp, bloqtam*bloqtam, MPI_DOUBLE, fila*r + ((fila+k) % r), k, MPI_COMM_WORLD, &estado);
            mult(atmp, b, c, bloqtam);        
        }
        // hacer una rotación de los bloques b a lo largo de las columnas
        MPI_Bsend(b, bloqtam*bloqtam, MPI_DOUBLE, arriba, 2*k, MPI_COMM_WORLD); // enviar b al proceso arriba
        MPI_Recv(b, bloqtam*bloqtam, MPI_DOUBLE, abajo, 2*k, MPI_COMM_WORLD, &estado); // recibir b del proceso abajo
    }
    MPI_Buffer_detach(&buffer, &tamBuffer); // liberar buffer

    // Calcular errores y escribir por pantalla
    for (int i = 0; i < bloqtam*bloqtam; i++) { // COMPROBAR SI A = C
        if(abs(a[i] - c[i]) > 0.0000001) {
            error++;
        }
    }

    if (error != 0) {
        printf("El error obtenido por el proceso %d es de %d.\n", myrank, error);
    }   
    else {
        printf("OK en el proceso %d. Errores cometidos = %d\n", myrank, error);
    }

    // vervector(a, bloqtam*bloqtam, "bloque a");
    // vervector(c, bloqtam*bloqtam, "bloque c");

    free(a); 
    free(b); 
    free(c); 
    free(atmp); 
    free(mifila);
    free(buffer);

    MPI_Finalize();
    return 0;
}

void mult(double a[], double b[], double *c, int m) {
    int i, j, k;
    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++) {
            for (k = 0;k < m;k++) {
                c[i*m+j] = c[i*m+j]+a[i*m+k]*b[k*m+j];
            }
        }
    }
}

void definir_bloques(double *a, double *b, double *c, int bloqtam, int fila, int columna) {
    // definir bloque a
    for (int i = 0; i < bloqtam*bloqtam; i++) {
        a[i] = i * (double) (fila * columna + 1) / bloqtam;
    }

    // definir bloque b (matriz identidad)
    for (int i = 0; i < bloqtam; i++) {
        for (int j = 0; j < bloqtam; j++) {
            if (i == j && columna == fila) { // si la fila y la columna coinciden
                b[i*bloqtam+j] = 1.0; // escribir 1s en la diagonal
            }
            else {
                b[i*bloqtam+j] = 0.0;
            }
        }
    }
    
    // definir bloque c
    for (int i = 0; i < bloqtam*bloqtam; i++) {
        c[i] = 0.0;
    }
}

void calcular_miFila(int *mifila, int r, int fil, int col, int numprocs, int myrank) {
    int j = 0;
    for (int i = 0; i < numprocs; i++){
        // si los procesos estan en la misma fila y es distinto al proceso que calcula
        if (fil == i/r && col != i%r) {
            // obtengo todos los procesos situados en la fila menos el proceso en el que estoy
            mifila[j] = i;
            j++;
        }
    }
}

void vervector(double a[], int m, char nombre[]) {
  int i;
  printf("%6s = ", nombre);
  for (i = 0; i < m; i++) {
    printf("%7.3f ", a[i]);
    if ((i + 1) % 5 == 0)
      printf("\n         ");
  }
  printf("\n");
}