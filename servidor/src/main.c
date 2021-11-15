#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include "comun.h"
#include "sockets.h"
#include <time.h>
#include <locale.h>

#define TCP 0
#define LOCAL_BROADCAST "192.168.100.255"
#define CLIENTS_PORT 2500
#define BUFFER_MAX 200

// Se agrega la librería ws2_32 a lista de dependencias
#pragma comment(lib, "ws2_32.lib")

int main()
{
    setlocale(LC_ALL, "");
    srand(time(NULL));

    WSADATA wsa;
    SOCKET sockfd;
    struct sockaddr_in server;
    struct sockaddr_in client;
    int SERVER_PORT = 50000 + rand() % 101;
    
    char* buf_tx = malloc(512);
    
    printf("\nInicializando Winsock...\n");
    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
        fprintf(stderr, "%ls %d", "Falló. Código de error:", WSAGetLastError());
        exit(-1);
    }

    printf("Inicializado.\n");

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == SOCKET_ERROR)
    {
        fprintf(stderr, "%ls %d", L"Falló la creación del socket", WSAGetLastError());
        exit(-1);
    }
    
    puts("Socket creado.\n");

    // Preparar la estructura sockaddr_in
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(SERVER_PORT);

    if(bind(sockfd, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        fprintf(stderr, "%ls %d", L"Falló el bind con código de error:", WSAGetLastError());
        exit(-1);
    }

    client.sin_family = AF_INET;
    client.sin_port = htons(CLIENTS_PORT);
    client.sin_addr.s_addr = inet_addr(LOCAL_BROADCAST);

    int broad = 1;
    if(setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (void*)&broad, sizeof(broad)) < 0)
    {
        fprintf(stderr, "%ls", L"Error en la habilitación del broadcast.");
        exit(-1);
    }

    /* Aceptar la información de los sockets entrantes en forma iterativa */
    while(1)
    {
        printf("[SERVIDOR]: ");
        do
        {
            fflush(stdin);
            memset(buf_tx, 0, BUFFER_MAX);
            fgets(buf_tx, BUFFER_MAX, stdin);
        } while(strlen(buf_tx) > BUFFER_MAX);
        
        if(sendto(sockfd, buf_tx, BUFFER_MAX, 0, (struct sockaddr*)&client, sizeof(struct sockaddr_in)) < 0)
        {
            fprintf(stderr, "No se pudo enviar mensaje");
            exit(-1);
        }

        if(strcmp(buf_tx, "exit\n") == 0)
        {
            closesocket(sockfd);
            break;
        }
    }

    WSACleanup();

    return 0;
}
