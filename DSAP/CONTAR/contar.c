#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

#define MAXENTERO 100 // valor máximo de los datos donde buscar
#define REPETICIONES 100000 // nº de repeticiones
#define NUMBUSCADO 10 // valor buscado en el conjunto de datos
#define MAXTAM 100000 // maximo tamaño del vector

// comunciación punto a punto. (send & recv)

int main(int argc, char const *argv[])
{
    int myrank, numprocs, tamanyo, numVeces, numVecesParalelo, cuenta_total, n, indice_root, indiceProceso;
	MPI_Status estado;
	double sequential_time, end_time, start_time, parallel_time;
    
    MPI_Init(&argc,&argv); // Inicializamos entorno MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank); // Devuelve el nº lógico que corresponde a cada proceso (0..N)
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs); // Devuelve el nº total de procesos existentes.
	
	int *vector;

	if (myrank == 0) { // proceso root

		printf("# ------------- CALCULO SECUENCIAL ------------- #\n");

		do {
			printf("Introduce el tamaño del vector (1-100000): ");
			scanf("%d", &tamanyo);
		}while(tamanyo < 0 || tamanyo > MAXTAM);

		if (tamanyo > 0 && tamanyo <= MAXTAM) {
			
			vector = (int *) malloc(tamanyo * sizeof(int)); // vector dinámico con malloc.

			srand(1);

			for (int i = 0; i < tamanyo; i++) {
				vector[i] = 1 + ((double) (MAXENTERO) * rand()) / RAND_MAX;
			}

			// cálculo secuencial del proceso 0.
			numVeces = 0;
			start_time = MPI_Wtime();

			for (int i = 0; i < REPETICIONES; i++) { // repetimos la búsqueda según *REPETICIONES*.
				for (int j = 0; j < tamanyo; j++) { // recorremos el vector.
					if (vector[j] == NUMBUSCADO) numVeces++; // si el nº en el vector es igual al NUMBUSCADO contador++.
				}
			}
			end_time = MPI_Wtime();
			sequential_time = end_time - start_time;
			printf("Veces que aparece el %d en %d repeticiones del vector de tamaño %d: %d veces, el %5.2f% \n",
					NUMBUSCADO, REPETICIONES, tamanyo, numVeces, ((100.0*numVeces)/tamanyo) / REPETICIONES);
			printf("Tiempo de proceso: %f \n \n", sequential_time);

			printf("# ------------- CALCULO PARALELO ------------- #\n");
			numVecesParalelo = 0;

			n = tamanyo / numprocs; // tamaño de los vectores que se van a pasar.
			indice_root = n + (tamanyo % numprocs); // hasta donde va a leer el proceso root.
			
			indiceProceso = indice_root; // variable auxiliar para indicarle a cada proceso en que posición del vector debe empezar.
			start_time = MPI_Wtime();

			for (int i = 1; i < numprocs; i++) {
				MPI_Send(&n, 1, MPI_INT, i, i, MPI_COMM_WORLD); // le pasamos el tamaño.
				MPI_Send(&vector[indiceProceso], n, MPI_INT, i, i, MPI_COMM_WORLD); // donde van a empezar los procesos restantes.
				indiceProceso += n; // vamos aumentando el indice para el siguiente proceso.
			}
			// paralelo en el proceso root
			for (int i = 0; i < REPETICIONES; i++) { // repetimos la búsqueda según *REPETICIONES*.
				for (int j = 0; j < indice_root; j++) { // el proceso root recorre hasta el indice indicado.
					if (vector[j] == NUMBUSCADO) numVecesParalelo++; // si el nº en el vector es igual al NUMBUSCADO contador++.
				}
			}
			//printf("n = %d, indice_root = %d \n", n, indice_root);
		}
	}
	if (myrank != 0) { // codigo de los procesos restantes.
		numVecesParalelo = 0;
		MPI_Recv(&n, 1, MPI_INT, 0, myrank, MPI_COMM_WORLD, &estado); // recibimos el tamaño.
		vector = (int *) malloc(n * sizeof(int)); // reservamos el tamaño de cada proceso restante con malloc.
		MPI_Recv(vector, n, MPI_INT, 0, myrank, MPI_COMM_WORLD, &estado); // recibimos los datos del vector.

		for (int i = 0; i < REPETICIONES; i++) {
			for (int j = 0; j < n; j++) {
				if (vector[j] == NUMBUSCADO) numVecesParalelo++;
			}
		}
		// enviamos al proceso root el numero de veces que se ha encontrado NUMBUSCADO.
		MPI_Send(&numVecesParalelo, 1, MPI_INT, 0, myrank, MPI_COMM_WORLD);
	}
	if (myrank == 0) { // miramos si estamos en el proceso root.
		cuenta_total = numVecesParalelo;
		for (int i = 1; i < numprocs; i++) { // recibir los datos de los procesos restantes y sumarlos en la variable cuenta_total.
			MPI_Recv(&numVecesParalelo, 1, MPI_INT, i, i, MPI_COMM_WORLD, &estado);
			cuenta_total += numVecesParalelo;
		}
		end_time = MPI_Wtime();
		parallel_time = end_time - start_time;

		printf("Veces que aparece el %d en %d repeticiones del vector de tamaño %d: %d veces, el %5.2f% \n", 
			NUMBUSCADO, REPETICIONES, tamanyo, cuenta_total, ((100.0*cuenta_total)/tamanyo) / REPETICIONES);
		printf("Tiempo de proceso: %f \n \n", parallel_time);

		// Cálculo del speed-up y eficiencia.

		double sp = sequential_time / parallel_time;
		printf("Speed-up = %f \n", sp);
		printf("Eficiencia = %5.2f% \n", (sp/numprocs) * 100.0);
	}
	free(vector); // liberar vector instanciado con malloc.
	MPI_Finalize();
}
