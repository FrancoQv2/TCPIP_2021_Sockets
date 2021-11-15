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

// 192.168.10.255
// 1100 0000.1010 1000.0000 1010.1111 1111
// C0.A8.0A.ff
#define	LOCAL_BROADCAST	((in_addr_t) 0xc0a80aff)

#define PORT_SERVER 2500
#define BUFFER_MAX  200

void inline error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    int socketfd, length, n;
    struct sockaddr_in server;
    struct sockaddr_in from;
    char buffer[BUFFER_MAX];

    printf("Bienvenido!\nEsta es la aplicacion Servidor\n\n");

    // Creo el socket
    socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketfd < 0) {
        error("socket()");
    }


    // Asocio una ip y puerto al socket
    server.sin_family = AF_INET;                // Familiy internet IPv4
    server.sin_port = htons(PORT_SERVER);       // Puerto del servidor
    //server.sin_addr.s_addr = INADDR_BROADCAST;  // Ip local broadcast 255.255.255.255
    server.sin_addr.s_addr = LOCAL_BROADCAST;  // Ip local broadcast 192.168.10.255

    bzero(&(server.sin_zero), 8);               // Coloca ceros en resto estructura

    if (bind(socketfd, (struct sockaddr *)&server, sizeof(struct sockaddr)) < 0) {
        error("bind()");
    }


    while (1) {
        //memset(buffer,0,BUFFER_MAX);
        bzero(buffer, BUFFER_MAX);

        printf("[SERVER]: ");
        fgets(buffer, BUFFER_MAX, stdin);
        
        n = sendto(socketfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server, sizeof(struct sockaddr));
        if (n < 0) {
            error("sendto()");
        }
    }
}