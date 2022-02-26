/*
ADA. 2019-20
Pràctica 1 de laboratori: "Empirical analysis of Quicksort average-time complexity."

Objectiu de la pràctica:

- Refrescar el llenguatge de programació i l'ús de les eines: compilador, make, editor, etc.
- Saber obtenir de manera empírica la complexitat temporal d'un algorisme, generant instàncies aleatòries i cronometrant el temps que tarda a resoldre-les.
- Saber mesurar temps de procés utilitzant la llibreria "chrono" de l'estàndard C++11.
- Conèixer el tipus de dades "size_t" per a representar la grandària dels objectes, útil per a evitar desbordaments dels tipus compostos; 
- Conèixer l'eina Gnuplot per a dibuixar funcions matemàtiques i el seu comando "fit" per a trobar la funció que millor s'ajusta a una sèrie de dades.
*/

/*
ADA. 2018-19
Práctica 1 de laboratorio: "Empirical analysis of Quicksort average-time 
    complexity."

Objetivo de la práctica:

- Refrescar el lenguaje de programación y el uso de las herramientas:
  compilador, make, editor, etc.

- Saber obtener de manera empírica la complejidad tenporal de un algoritmo,
  generando instancias aleatorias y cronometrando el tiempo que tarda en
  resolverlas.

- Saber medir el tiempo de proceso utilizando la libreria "chrono" del
  estandar C++11.

- Conocer el tipo de datos "size_t" para representar el tamaño de los 
  objetos.

- Conocer la herramienta Gnuplot para dibujar funciones matemáticas y
  su comando "fit" para encontrar la función que mejor se ajusta a  una
  serie de datos.
*/

#include <unistd.h>
#include <iostream>
#include <math.h>
#include <chrono>

using namespace std;
using namespace chrono;

//--------------------------------------------------------------
// Bubble sort basic algorithm
void 
bubbleSort(int * v, size_t size){
int aux;

for (size_t i = 1; i < size; i++)
    for (size_t j = 0; j < size - i; j++)
        if (v[j]>v[j+1]){ /*swap*/
            aux = v[j]; 
            v[j] = v[j+1]; 
            v[j+1] = aux;
        }
}  
//--------------------------------------------------------------                


int
main(void){

//    srand(getpid());
    srand(0);

    cout << "# BubbleSort CPU times in milliseconds:"
        << endl
        << "# Size \t CPU time (ms.)"
        << endl
        << "# ----------------------------"
        << endl;

    for (int exp = 10; exp <= 16; exp++){ 
        size_t size = size_t( pow(2,exp) ); //2^10 a 2^16
        int* v = new int [size]; //memoria dinamica viene del heap
        if (!v){
            cerr << "Error, not enough memory!" << endl;
            exit (EXIT_FAILURE);
        }

        cout << size << "\t\t" << std::flush;

        for (size_t j = 0; j < size; j++) 
            v[j] = rand(); 

        auto start = clock();
        bubbleSort(v,size);
        auto end = clock();


        cout << 1000.0 * (end-start) / CLOCKS_PER_SEC  << endl;

        for (size_t i = 1; i < size; i++)
            if (v[i] < v[i-1]){ 
                cerr << "Panic, array not sorted! " << i << endl; 
                exit(EXIT_FAILURE);            
            }

        delete[] v; 
    }
}


