#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#include <stdlib.h>     // Para exit()
#include <strings.h>    // Para bzero()
#include <unistd.h>     // Para close()
#include <arpa/inet.h>  // Para inet_ntoa()

#define PORT    3550    // Puerto de conexion
#define BACKLOG 5       // Numero de conexiones permitidas

int main(int argc, char const *argv[]) {
    int sockfd1, sockfd2;           // Descriptores de archivo
    int tama_sin;
    struct sockaddr_in servidor;    // Info de la direccion de servidor
    struct sockaddr_in cliente;     // Info de la direccion del cliente
    
    printf("Servidor\n");
    
    // Creo una nueva instancia de un socket
    if ((sockfd1 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error en Socket()\n");
        exit(-1);
    }
    
    servidor.sin_family = AF_INET;

    servidor.sin_port = htons(PORT);            // Convierte PORT al numero de red
    servidor.sin_addr.s_addr = INADDR_ANY;      // Coloca ip automaticamente (0.0.0.0)
    
    bzero(&(servidor.sin_zero), 8);             // Coloca ceros en resto estructura
    
    if (bind(sockfd1, (struct sockaddr *)&servidor, sizeof(struct sockaddr)) < 0) {
        printf("Error en Bind()");
        exit(-1);
    }

    if ((listen(sockfd1, BACKLOG)) < 0) {
        // Espera conexiones en un socket
        printf("Error en listen()\n");
        exit(-1);
    }

    while (1) {
        tama_sin = sizeof(struct sockaddr_in);
        if ((sockfd2 = accept(sockfd1, (struct sockaddr *)&cliente, &tama_sin)) < 0) {
            printf("Error en accept()\n");
            exit(-1);
        }
        printf("Tenes una conexion desde %s \n", inet_ntoa(cliente.sin_addr));
        send(sockfd2, "Bienvenido al servidor", 24, 0);
        close(sockfd2);
    }
    close(sockfd1);
}