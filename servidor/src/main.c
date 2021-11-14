#include <stdio.h>
#include <winsock.h>
#include <errno.h>
#include "comun.h"

#define TCP 1
#define SERVER_ADDRESS "192.168.100.4"
#define SERVER_PORT 50080
#define BACKLOG 3       // Solo se pueden poner en pendiente 3 conexiones como máximo

// Se agrega la librería ws2_32 a lista de dependencias
#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsa;
    SOCKET sockfd, new_socket;
    struct sockaddr_in server, client;
    int len;
    int recv_size;

    unsigned char falloRecepcion = 0;

    char* buf_rx = malloc(512);
    char* buf_tx = malloc(512);

    printf("\nInicializando Winsock...\n");
    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
        printf("Fall%c. C%cdigo de error: %d", 0xa2, 0xa2, WSAGetLastError());
        return 1;
    }

    printf("Inicializado.\n");

#if TCP
    // AF_INET: para direcciones IPv4
    // SOCK_STREAM: conexión orientada a streams. Es decir, al protocolo TCP
    // IPPROTO_TCP: uso del protocolo TCP
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
        printf("No se pudo crear el socket: %d", WSAGetLastError());

#else

    if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
        printf("No se pudo crear el socket: %d", WSAGetLastError());
    
#endif

    printf("Socket creado.\n");

    // Preparar la estructura sockaddr_in
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    server.sin_port = htons(SERVER_PORT);

    if(bind(sockfd, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Fall%c el bind con c%cdigo de error: %d", 162, 162, WSAGetLastError());
        return -1;
    }

    puts("Bind hecho");

    // Escuchar conexiones entrantes
    listen(sockfd, BACKLOG);

    puts("Esperando conexiones entrantes...");

    len = sizeof(struct sockaddr_in);

    client.sin_port = htonl(2500);
    client.sin_family = AF_INET;

    new_socket = accept(sockfd, (struct sockaddr*)&client, &len);
    if(new_socket < 0)
    {
        fprintf(stderr, "accept() fall%c con c%cdigo de error: %d", 162, 162, WSAGetLastError());
        return -1;
    }

    printf("Conexi%cn aceptada al cliente %s\n", 162, inet_ntoa(client.sin_addr));

    /* Aceptar la información de los sockets entrantes en forma iterativa */
    while(1)
    {
        memset(buf_tx, 0, 200);

        printf("[SERVIDOR]: Escribir un mensaje\n");
        fgets(buf_tx, 200, stdin);
        if(send(new_socket, buf_tx, strlen(buf_tx), 0) < 0)
        {
            fprintf(stderr, "Env%co fallido.\n", 161);
            return -1;
        }

        if(strcmp(buf_tx, "exit\n") == 0)
        {
            closesocket(new_socket);
            break;
        }
    }
    
    closesocket(sockfd);
    WSACleanup();

    return 0;
}
