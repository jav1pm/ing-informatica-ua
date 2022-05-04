#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>


#define PUERTO 9999

int const tam_buffer = 999999;

int main(){
    //declaramos las estructuras para que puedan conectarse al servidor
    int sfd, nsfd, pid;
    int cli_addr_len;
    struct sockaddr_in servidor, cli_addr; 
    char buffer[tam_buffer];//bufer
    char linea[10000];//para leer por lineas
    
    FILE *archivo;
    // Apertura de un conector orientado a conexión, de la familia AF_INET
    if ((sfd = socket(AF_INET, SOCK_STREAM , 0))==-1) {
        printf("Error, no se ha podido abrir el socket\n");
        exit(-1);
    }

    servidor.sin_family =  AF_INET; //familia protocolos
    servidor.sin_addr.s_addr = INADDR_ANY; // IP_Servidor (127.0.0.1)
    servidor.sin_port = htons(PUERTO);//indicamos el puerto

    if(bind(sfd , (struct sockaddr*) &servidor, sizeof(servidor)) == -1) {//introducimos la direccion
        printf("Error de bind, no se ha podido establecer conexion \n");
        exit(-1);
    } 
    // queremos que haya hasta 5 peticiones atendidas simultáneas
    listen(sfd,5); 
    // Bucle de lectura de peticiones de conexión
    for (;;) {
        printf("***************************\nEsperando conexion de cliente...\n");
        cli_addr_len = sizeof(cli_addr);
        if ((nsfd=accept(sfd, (struct sockaddr*)&cli_addr,&cli_addr_len))==-1){ //Como en cliente, rellenar con struct
            printf("Error de accept, no se ha podido establecer conexion\n");
            exit(-1); 
        }
        else {
            printf("Cliente conectado.\n");
            archivo = fopen("Google.html","r");//abrimos el fichero
            printf("Enviando datos...\n\n");
        
            // Se crea un proceso hijo (fork) para atender al cliente  
            if ((pid=fork()==0)){ // Código del hijo
                if(archivo == NULL) {
                    printf("Error al abrir el fichero, no se pudo enviar datos\n");
                    exit(-1); 
                }
                while(fgets(linea,10000, archivo) != NULL){//leo archivo por lineas
                    strcat(buffer,linea);
                }
                send(nsfd,buffer,sizeof(buffer),0); //Enviamos el archivo
                fclose(archivo);
            }
        close(sfd);  // Cerramos el descriptor de escucha
        close(nsfd); // Cerramos descriptor de conexión
        exit(0);
        }
    }
}