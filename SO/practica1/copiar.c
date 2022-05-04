#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {
    int tuberia[2];
    int archivo;
    char buffer[1];
    pipe(tuberia); //Creamos la tubería

    if(fork() > 0) { //Hijo
        archivo = open(argv[1],O_RDONLY); //Lee el archivo de argv[1](Read only)
        while(read(archivo,buffer,1) > 0) { //Lee archivo
            write(tuberia[1],buffer,1); //Escribe en la tubería
        }
    }
    else{
        archivo = creat(argv[2],0666); //Permiso al programa para: Lectura, Escritura, pero no puede ejecutar
        while(read(tuberia[0],buffer,1) > 0) { //Lee la tuberia
            write(archivo, buffer, 1); //Escribe nuevo archivo, copia del original
        }
    }
}