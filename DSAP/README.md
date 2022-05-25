# DESARROLLO DE SOFTWARE EN ARQUITECTURAS PARALELAS

Repositorio para las prácticas de Desarrollo de software en arquitecturas paralelas.

## Prácticas realizadas

- ANILLO
- CONTAR
- MVCL
- MMalla
- FW

## Ejemplo

```c
#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
	int myrank, numprocs, entero;
	MPI_Status estado;

	MPI_Init(&argc,&argv); // Inicializamos entorno MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank); // Devuelve el nº lógico que corresponde a cada proceso (0..N)
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs); // Devuelve el nº total de procesos existentes.

	if (myrank == 0) // proceso root
	{
		printf("Introduce un numero entero: ");
		scanf("%d", &entero);

		// buf, count, buf_datatype, destino, tag, comm
		MPI_Send(&entero, 1, MPI_INT, myrank + 1, 8, MPI_COMM_WORLD);

		// buf, count, buf datatype, origen, tag, comm, status
		MPI_Recv(&entero, 1, MPI_INT, numprocs - 1, 8, MPI_COMM_WORLD, &estado);

		printf("Soy el proceso %d, el entero recibido es: %d \n", myrank, entero);

		entero += 1;

		printf("Soy el proceso %d, le sumo uno: %d \n", myrank, entero);
	}
	else if (myrank == numprocs - 1) // último proceso
	{
		MPI_Recv(&entero, 1, MPI_INT, myrank - 1, 8, MPI_COMM_WORLD, &estado);
		printf("Soy el proceso %d, el entero recibido es: %d \n", myrank, entero);

		entero += 1;
		MPI_Send(&entero, 1, MPI_INT, 0, 8, MPI_COMM_WORLD);
	}
	else // resto de procesos
	{
		MPI_Recv(&entero, 1, MPI_INT, myrank - 1, 8, MPI_COMM_WORLD, &estado);
		printf("Soy el proceso %d, el entero recibido es: %d \n", myrank, entero);

		entero += 1;
		MPI_Send(&entero, 1, MPI_INT, myrank + 1, 8, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}
```

## Autor

- [@Javiiiis](https://www.github.com/Javiiiis)

## Licencia

[MIT](https://choosealicense.com/licenses/mit/)
