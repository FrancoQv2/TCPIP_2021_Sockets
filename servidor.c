#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#include <stdlib.h>     // Para exit()
#include <strings.h>    // Para bzero()
#include <unistd.h>     // Para close()
#include <arpa/inet.h>  // Para inet_ntoa()

#define	IP_SERVER	((in_addr_t) 0xc0a80132)

#define PORT    50005   // Puerto de conexion
#define BACKLOG 5       // Numero de conexiones permitidas

int main(int argc, char const *argv[]) {
    int sockfd1, sockfd2;           // Descriptores de archivo
    int tama_sin;
    struct sockaddr_in servidor;    // Info de la direccion de servidor
    struct sockaddr_in cliente;     // Info de la direccion del cliente

    char mensaje[200];
    
    printf("Bienvenido!\n");
    printf("Esta es la aplicacion Servidor\n");
    
    // Creo una nueva instancia de un socket
    if ((sockfd1 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error en socket()\n");
        exit(-1);
    }

    /* 
        Address to accept any incoming messages.
    #define	INADDR_ANY		    ((in_addr_t) 0x00000000)
        Address to send to all hosts.
    #define	INADDR_BROADCAST	((in_addr_t) 0xffffffff)
    */
    
    servidor.sin_family = AF_INET;

    servidor.sin_port = htons(PORT);            // Convierte PORT al numero de red
    //servidor.sin_addr.s_addr = INADDR_ANY;      // Coloca ip automaticamente (0.0.0.0)
    servidor.sin_addr.s_addr = IP_SERVER;

    // 192.168.1.50
    // 1100 0000.1010 1000.0000 0001.0011 0010
    // C0.A8.01.32
    
    bzero(&(servidor.sin_zero), 8);             // Coloca ceros en resto estructura
    
    // Asocio una direccion IP y num de puerto al socket creado
    if (bind(sockfd1, (struct sockaddr *)&servidor, sizeof(struct sockaddr)) < 0) {
        printf("Error en bind()\n");
        exit(-1);
    }

    // Espera conexiones en un socket
    if ((listen(sockfd1, BACKLOG)) < 0) {
        printf("Error en listen()\n");
        exit(-1);
    }

    //printf("Escribe un mensaje: ");
    //fgets(mensaje,sizeof(mensaje),stdin);

    while (1) {

        tama_sin = sizeof(struct sockaddr_in);
        if ((sockfd2 = accept(sockfd1, (struct sockaddr *)&cliente, &tama_sin)) < 0) {
            printf("Error en accept()\n");
            exit(-1);
        }

        printf("Tenes una conexion desde %s \n", inet_ntoa(cliente.sin_addr));

        send(sockfd2, mensaje, sizeof(mensaje), 0);
        close(sockfd2);
    }
    close(sockfd1);
}