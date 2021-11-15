/* Creates a datagram server. The port number is passed as an argument. This server runs forever */

#include <stdio.h>
#include <stdlib.h>  // Para exit()
#include <string.h>
#include <strings.h>    // Para bzero()
#include <unistd.h>     // Para close()

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>  // Para inet_ntoa()

#include <time.h>

// 192.168.10.255
// 1100 0000.1010 1000.0000 1010.1111 1111
// C0.A8.0A.ff
//#define	LOCAL_BROADCAST	((in_addr_t) 0xc0a80aff)
#define	LOCAL_BROADCAST	"192.168.10.255"
#define CLIENTS_PORT    2500
#define BUFFER_MAX      200


int main(int argc, char *argv[]) {
    srand(time(NULL));
    int PORT_SERVER = 50000+rand()%101;

    int socketfd, length, n;
    struct sockaddr_in server;
    struct sockaddr_in client;
    char buffer[BUFFER_MAX];

    printf("Bienvenido!\nEsta es la aplicacion Servidor\n\n");

    // Creo el socket
    socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketfd < 0) {
        printf("socket()");
    }

    // Asocio una ip y puerto al socket
    server.sin_family = AF_INET;                // Familiy internet IPv4
    server.sin_port = htons(PORT_SERVER);       // Puerto del servidor
    server.sin_addr.s_addr = INADDR_ANY;

    bzero(&(server.sin_zero), 8);               // Coloca ceros en resto estructura

    if (bind(socketfd, (struct sockaddr *)&server, sizeof(struct sockaddr_in)) < 0) {
        printf("bind()");
    }

    client.sin_family = AF_INET;                            // Familiy internet IPv4
    client.sin_port = htons(CLIENTS_PORT);                  // Puerto del servidor
    client.sin_addr.s_addr = inet_addr(LOCAL_BROADCAST);    // Ip local broadcast 192.168.10.255
    bzero(&(server.sin_zero), 8);
    int broad = 1;
    if (setsockopt(socketfd,SOL_SOCKET,SO_BROADCAST,(void *)&broad,sizeof(broad)) < 0) {
        printf("Fallo xd");
        exit(-1);
    }

    while (1) {
        printf("[SERVER]: ");
        do {
            fflush(stdin);
            bzero(buffer, BUFFER_MAX);
            fgets(buffer, BUFFER_MAX, stdin);
        } while (strlen(buffer) > BUFFER_MAX);

        n = sendto(socketfd, buffer, BUFFER_MAX, 0, (struct sockaddr *)&client, sizeof(struct sockaddr_in));    
        puts(buffer);
        if (n < 0) {
            printf("sendto()");
        }
    }
}