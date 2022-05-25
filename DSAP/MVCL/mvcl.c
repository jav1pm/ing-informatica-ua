#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>

#define maxm 500      // Máximo número de filas en la matriz
#define maxn 500      /// Máximo númeor de columnas en la matriz
#define maxnumprocs 8 // Máximo número de procesos

main(int argc, char **argv) {
  void vermatriz(int lda, double a[][lda], int, int, char[]);
  void vervector(double a[], int m, char nombre[]);
  void matvec(int col, double a[][col], double x[], double y[], int m, int local);

  int i, j, k;
  int m, n; // m = nº filas, n = nº columnas
  double a[maxm][maxn], x[maxn], sol[maxm], y[maxn];

  int myrank, numprocs, tam, local;
  int columna_ini, col_por_proceso;
  MPI_Status estado;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

  if (myrank == 0) {

    while ((m <= 0) || (m > maxm)) {

      printf("Numero de filas (1 - %d): ", maxm);
      scanf("%d", &m);

      if (m > maxn) {
        printf("El valor introducido sobrepasa el maximo: %d\n", maxn);
      }
      if (m < 1) {
        printf("El valor introducido debe ser > 0\n");
      }
    }

    while ((n <= 0) || (n > maxm)) {

      printf("Numero de columnas (1 - %d): ", maxm);
      scanf("%d", &n);

      if (n > maxn) {
        printf("El valor introducido sobrepasa el maximo: %d\n", maxn);
      }
      if (n < 1) {
        printf("El valor introducido debe ser > 0\n");
      }
    }
    // rellenar matriz
    for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++) {
        a[i][j] = i + j;
      }
    }

    // rellenar vector
    for (j = 0; j < n; j++) x[j] = j;

    // si el nº de filas y columnas es menor o igual a 10, mostramos la matriz.
    if ((m <= 10) && (n <= 10)) {
      vermatriz(maxn, a, m, n, "A");
      printf("\n");
      vervector(x, n, "x");
    }

    // resultado: matriz * vector
    for (i = 0; i < m; i++) {
      sol[i] = 0;
      for (j = 0; j < n; j++) {
        sol[i] = sol[i] + a[i][j] * x[j];
      }
    }
    vervector(sol, m, "A*x secuencial");
    printf("=============================================\n\n");

    // calcular reparto
    tam = n / numprocs; // el nº de columnas que va a recibir el resto de procesos.
    local = tam + n % numprocs; // el nº de columnas que va a utilizar el proceso root.
  }

  // envio de tam y m al resto de procesos
  MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&tam, 1, MPI_INT, 0, MPI_COMM_WORLD);

  if (myrank == 0) {
    // envío de un bloque consecutivo de columnas empleando la opción 1 (elemento a elemento) visto en teoría.
    columna_ini = local; // variable para inidicar en que columna empieza el siguiente proceso
    for (k = 1; k < numprocs; k++) {
      for (i = 0; i < m; i++) { // m además de ser el nº filas también corresponde con el nº de elementos que tendrá cada columna
        for (j = columna_ini; j < columna_ini + tam; j++) { // empezamos por donde se ha quedado el proceso root hasta columnas de root + las columnas que tendrá el siguiente proceso
          MPI_Send(&a[i][j], 1, MPI_DOUBLE, k, 9, MPI_COMM_WORLD);
        }
      }
      // envio de la parte de vector x
      MPI_Send(&x[columna_ini], tam, MPI_DOUBLE, k, 8, MPI_COMM_WORLD);
      columna_ini += tam;
    }
    //printf("Soy el proceso (%d), ", myrank);
    //vermatriz(maxn, a, m, local, "bloque de columnas recibido");
  }
  else {
    for (i = 0; i < m; i++) {
      for (j = 0; j < tam; j++) {
        // recibir elemento a elemento
        MPI_Recv(&a[i][j], 1, MPI_DOUBLE, 0, 9, MPI_COMM_WORLD, &estado);
        //printf("%7.3f (%d) ", a[i][j], myrank);
      }
    }
    //printf("Soy el proceso (%d), ", myrank);
    //vermatriz(maxn, a, m, tam, "bloque de columnas recibido");
    MPI_Recv(&x[0], tam, MPI_DOUBLE, 0, 8, MPI_COMM_WORLD, &estado);

    // for (i = 0; i < tam; i++) {
    //   printf("Elemento = %7.3f recibido en (%i)", x[i], myrank);
    // }
    // printf("\n");
  }

  if (myrank == 0) {
    matvec(maxn, a, x, y, m, local);
    printf("Soy el proceso (%d), ", myrank);
    vervector(y, m, "solución parcial A*x");
    printf("\n");
  }
  else {
    matvec(maxn, a, x, y, m, tam);
    printf("Soy el proceso (%d), ", myrank);
    vervector(y, m, "solución parcial A*x");
    printf("\n");
  }

  // MPI_Reduce para ir acumulando la y de cada proceso.
  if (myrank != 0) {
    MPI_Reduce(&y,&y,m,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
  }
  else {
    MPI_Reduce(MPI_IN_PLACE,&y,m,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    vervector(y, m, "\nResultado final en y de A*x");
    printf("\n");
  }

  MPI_Finalize();
  return 0;
}

void vermatriz(int lda, double a[][lda], int m, int n, char nombre[]) {
  int i, j;
  printf("%4s =", nombre);
  printf("%6d ", 0);
  for (j = 1; j < n; j++) {
    printf("%7d ", j);
  }
  printf("\n");
  for (i = 0; i < m; i++) {
    printf("%8d:", i);
    for (j = 0; j < n; j++)
    {
      printf("%7.3f ", a[i][j]);
    }
    printf("\n");
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

void matvec(int col, double a[][col], double x[], double y[], int m, int local) { 
  int i, j;
  //printf(" \nColumnas = %d - ", local);
  for (i = 0; i < m; i++) {
      y[i] = 0;
      for (j = 0; j < local; j++) {
          y[i] = y[i] + a[i][j] * x[j];
      }
  }
}