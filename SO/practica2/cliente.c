#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#define PORT 9999//puerto
#define MAXDATASIZE 100000//tamaño buffer

int main(int argc, char *argv[]){
    //declaramos las estructuras para conectarse al servidor
    struct sockaddr_in remoto;
    struct in_addr;
    int conector = socket(AF_INET,SOCK_STREAM,0);
    int numbytes=20;
    char buf[MAXDATASIZE];//declaramos el buffer


    if(argc>1) {
        if(conector==-1) {
            printf("Error de conexión\n");
            exit(-1);
        }

        remoto.sin_family = AF_INET;//familia protocolos
        remoto.sin_port = htons(PORT);//asignamos el puerto
        remoto.sin_addr.s_addr = inet_addr(argv[1]); // IP_Servidor (127.0.0.1)
        bzero(&(remoto.sin_zero),8);

        if(connect(conector, (struct sockaddr* )&remoto, sizeof(struct sockaddr))==-1) {//se concta al servidor, y miramos si lo hace
            printf("Error de conexion\n");
            exit(-1);
        }

        if((numbytes=recv(conector,buf,MAXDATASIZE,0)) == -1) {//obtenemos los datos del servidor y los guardamos en el buffer y miramos si lo hace
          printf("Error en recv() \n");
          exit(-1);
       }

        buf[numbytes]='\0';
        printf("**********************************************************************\n");
        printf("Contenido del archivo recibido al establecer conexión con el servidor:\n\n%s", buf);//mostramos por pantalla
  
        close(conector);//cerramos conexion
    }else{
        printf("ERROR ARGUMENTOS:   cliente <ip>\n");
    }

}





