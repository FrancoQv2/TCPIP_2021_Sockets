#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#include <stdlib.h>     // Para exit()
#include <string.h>
#include <strings.h>    // Para bzero()
#include <unistd.h>     // Para close()
#include <arpa/inet.h>  // Para inet_ntoa()

#define IP_SERVER       "192.168.10.10"
#define PORT            2500    // Puerto de conexion
#define MAX_SIZE_DATO   200     // Tamaño maximo en bytes a transmitir

int main(int argc, char const *argv[]) {
    int socketfd, numbytes;             // Descriptores de archivo
    char recv_buffer[MAX_SIZE_DATO];    // Buffer temporario
    
    struct hostent *he;
    struct sockaddr_in servidor;    // Info de la direccion del servidor
    
    printf("Bienvenido!\n");
    printf("Esta es la aplicacion Cliente\n");

    
    //char *ip = IP_SERVER;
    if ((he = gethostbyname(IP_SERVER)) == NULL) {
        printf("Error en Gethostbyname()\n");
        exit(-1);
    }
        
    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error en socket()\n");
        exit(-1);
    }

    servidor.sin_family = AF_INET;

    printf("a %i\n",PORT);
    servidor.sin_port = htons(PORT);
    printf("b %i\n",servidor.sin_port);

    servidor.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(servidor.sin_zero), 8);
    
    if (connect(socketfd, (struct sockaddr *)&servidor, sizeof(struct sockaddr)) < 0) {
        printf("Error en connect()\n");
        exit(-1);
    }
    
    while (1) {
        memset(recv_buffer,0,MAX_SIZE_DATO);

        if ((numbytes = recv(socketfd, recv_buffer, MAX_SIZE_DATO, 0)) < 0) {
            printf("Error en recv()\n");
            exit(-1);
        }
        else {
            if (strcmp(recv_buffer,"exit\n") == 0) break;
            
            recv_buffer[numbytes] = '\0';
            printf("[][%s:%d]", inet_ntoa(servidor.sin_addr),servidor.sin_port);
            printf(" - %s", recv_buffer);
        }
        
    }

    close(socketfd);
}