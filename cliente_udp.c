/* UDP client in the internet domain */

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

#define CLIENT_SERVER     2500
#define BUFFER_MAX  200

void inline error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    int socketfd_server, length, n;
    int socketfd;
    struct sockaddr_in server;
    struct sockaddr_in client;
    struct sockaddr_in from;
    struct hostent *hp;
    char buffer[BUFFER_MAX];

    printf("Bienvenido!\nEsta es la aplicacion Cliente\n\n");

    socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketfd < 0) {
        error("socket()");
    }

    client.sin_family = AF_INET;
    client.sin_port = htons(CLIENT_SERVER);
    client.sin_addr.s_addr = INADDR_ANY;        // Ip local broadcast 255.255.255.255
    bzero(&(client.sin_zero), 8);               // Coloca ceros en resto estructura

    if (bind(socketfd, (struct sockaddr *)&client, sizeof(struct sockaddr)) < 0) {
        error("bind()");
    }

    length = sizeof(struct sockaddr_in);

    while (1) {
        n = recvfrom(socketfd, buffer, BUFFER_MAX, 0, (struct sockaddr *)&from, &length);
        if (n < 0) {
            error("recvfrom()");
        }

        printf("[][%s:%d]: %s", inet_ntoa(from.sin_addr), ntohs(from.sin_port), buffer);
        bzero(buffer, BUFFER_MAX);
    }
}