/* Creates a datagram server. The port number is passed as an argument. This server runs forever */

#include <stdio.h>
#include <stdlib.h>     // Para exit()
#include <string.h>
#include <strings.h>    // Para bzero()
#include <unistd.h>     // Para close()

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>  // Para inet_ntoa()

#include <errno.h>

#include <time.h>

#define	LOCAL_BROADCAST	"192.168.10.255"
#define CLIENT_PORT     2500
#define BUFFER_MAX      200

void inline error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int SERVER_PORT = 50000+rand()%101;

    int socketfd, length, n;
    struct sockaddr_in server;
    struct sockaddr_in client;
    char buffer[BUFFER_MAX];

    printf("Bienvenido!\nEsta es la aplicacion Servidor\n\n");

    // Creo el socket
    socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketfd < 0) {
        error("socket()");
    }

    // Configuro los parametros del server
    server.sin_family = AF_INET;                // Familiy internet IPv4
    server.sin_port = htons(SERVER_PORT);       // Puerto del servidor
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server.sin_zero), 8);               // Coloca ceros en resto estructura

    // Asocio la IP y puerto del server al socket
    if (bind(socketfd, (struct sockaddr *)&server, sizeof(struct sockaddr_in)) < 0) {
        error("bind()");
    }

    // Configuro los parametros de los clientes
    client.sin_family = AF_INET;                            // Familiy internet IPv4
    client.sin_port = htons(CLIENT_PORT);                   // Puerto del servidor
    client.sin_addr.s_addr = inet_addr(LOCAL_BROADCAST);    // Ip local broadcast 192.168.10.255
    //client.sin_addr.s_addr = INADDR_BROADCAST;              // Ip broadcast 255.255.255.255
    bzero(&(server.sin_zero), 8);

    // Configuro las opciones del socket para que acepte broadcast
    int broadcast = 1;
    if (setsockopt(socketfd,SOL_SOCKET,SO_BROADCAST,(void *)&broadcast,sizeof(broadcast)) < 0) {
        error("setsockopt()");
    }

    while (1) {
        printf("[SERVER]: ");
        do {
            fflush(stdin);
            bzero(buffer, BUFFER_MAX);
            fgets(buffer, BUFFER_MAX, stdin);
        } while (strlen(buffer) > BUFFER_MAX);
         
        if (sendto(socketfd,buffer,BUFFER_MAX,0,(struct sockaddr *)&client,sizeof(struct sockaddr_in))  < 0) {
            error("sendto()");
        }
    }
}