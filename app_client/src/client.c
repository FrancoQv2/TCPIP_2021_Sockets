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

#include <time.h>


#define CLIENT_PORT 2500
#define BUFFER_MAX  200

void inline error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    time_t t;
    struct tm *tm;
    char   actual_date[14],actual_time[10];

    int    socketfd, length, n;
    struct sockaddr_in server;
    struct sockaddr_in client;
    char   buffer[BUFFER_MAX];

    printf("Bienvenido!\nEsta es la aplicacion Cliente\n\n");
    
    socketfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (socketfd < 0) {
        error("socket()");
    }

    client.sin_family = AF_INET;
    client.sin_port = htons(CLIENT_PORT);
    client.sin_addr.s_addr = INADDR_ANY;        // Ip local broadcast 255.255.255.255
    bzero(&(client.sin_zero), 8);               // Coloca ceros en resto estructura

    if (bind(socketfd, (struct sockaddr *)&client, sizeof(struct sockaddr)) < 0) {
        error("bind()");
    }

    length = sizeof(struct sockaddr_in);

    while (1) {
        n=recvfrom(socketfd, buffer, BUFFER_MAX, 0, (struct sockaddr *)&server, &length);
        if (n < 0) {
            error("recvfrom()");
        }

        t = time(NULL);
        tm = localtime(&t);
        strftime(actual_date, 14, "%d/%m/%Y", tm);
        strftime(actual_time, 10, "%H:%M:%S", tm);

        printf("[%s-%s][%s:%d]: %s",actual_date,actual_time,inet_ntoa(server.sin_addr),ntohs(server.sin_port),buffer);
        bzero(buffer, BUFFER_MAX);
    }
}

