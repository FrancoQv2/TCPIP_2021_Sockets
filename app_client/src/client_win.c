#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>
#include <locale.h>
#include "comun.h"
#include <Windows.h>
#include <time.h>

#define CLIENT_SERVER 2500

#define TCP 0

// Se agrega la librería ws2_32 a lista de dependencias
#pragma comment(lib, "ws2_32.lib")

int main()
{
    setlocale(LC_ALL, "");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);

    WSADATA wsa;
    SOCKET sockfd, sockfd_server;
    struct sockaddr_in server;
    struct sockaddr_in client;
    struct sockaddr_in from;

    int length, n;

    int recv_size;

    char* buf_rx = malloc(512);

    printf("\nInicializando Winsock...\n");
    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
        fprintf(stderr, "%ls %d", L"Falló. Código de error: ", WSAGetLastError());
        return 1;
    }

    printf("Inicializado.\n");

#if TCP
    // AF_INET: para direcciones IPv4
    // SOCK_STREAM: conexión orientada a streams. Es decir, al protocolo TCP
    // 0: uso del protocolo TCP
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        fprintf(stderr, "No se pudo crear el socket: %d", WSAGetLastError());
        exit(-1);
    }

#else

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        fprintf(stderr, "No se pudo crear el socket: %d", WSAGetLastError());
        exit(-1);
    }
    
#endif

    puts("Socket creado.\n");
    
    client.sin_family = AF_INET;
    client.sin_port = htons(CLIENT_SERVER);
    client.sin_addr.s_addr = INADDR_ANY;

    memset(&(client.sin_zero), 0, 8);

    if(bind(sockfd, (struct sockaddr*)&client, sizeof(struct sockaddr)) == SOCKET_ERROR)
    {
        fprintf(stderr, "%ls %d", L"Falló el bind con código de error: ", WSAGetLastError());
        return -1;
    }
    
    length = sizeof(struct sockaddr_in);

    printf("%ls", L"¡Bienvenido a la consola de un cliente!\n\n");

    while(1)
    {
        memset(buf_rx, 0, 512);

        // Recibir una respuesta de un servidor
        if((recv_size = recvfrom(sockfd, buf_rx, BUFFER_MAX+2, 0, (struct sockaddr*)&from, &length)) == SOCKET_ERROR)
        {
            fprintf(stderr, "%ls", L"Recepción fallida.\n");
        }
        else
        {
            if(strcmp(buf_rx, "exit\n") == 0)
                break;
            buf_rx[recv_size] = 0;

            struct tm* FechaActual;
            time_t tActual;
            tActual = time(&tActual);
            FechaActual = localtime(&tActual);
            
            printf("[%02d/%02d/%d ", FechaActual->tm_mday, FechaActual->tm_mon, FechaActual->tm_year+1900);
            printf("%02d:%02d:%02d]", FechaActual->tm_hour, FechaActual->tm_min, FechaActual->tm_sec);
            printf("[%s:%d]: ", inet_ntoa(from.sin_addr), ntohs(from.sin_port));
            fputs(buf_rx, stdout);
            printf("\n");
        }
    }

    closesocket(sockfd);

    return 0;
}
