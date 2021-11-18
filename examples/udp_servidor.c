/* Creates a datagram server. The port number is passed as an argument. This server runs forever */

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

void error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    int socketfd, length, client_len, n;
    struct sockaddr_in server;
    struct sockaddr_in client;
    char buffer[1024];

    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(0);
    }

    socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketfd < 0) {
        error("Opening socket");
    }
    
    length = sizeof(server);
    bzero(&server, length);
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));
    
    if (bind(socketfd, (struct sockaddr *)&server, length) < 0) {
        error("binding");
    }
    
    client_len = sizeof(struct sockaddr_in);
    
    while (1) {
        n = recvfrom(socketfd, buffer, 1024, 0, (struct sockaddr *)&client, &client_len);
        if (n < 0) {
            error("recvfrom");
        }
        write(1, "Received a datagram: ", 21);
        write(1, buffer, n);
        n = sendto(socketfd, "Got your message\n", 17,
                   0, (struct sockaddr *)&client, client_len);
        if (n < 0) {
            error("sendto");
        }
    }
}