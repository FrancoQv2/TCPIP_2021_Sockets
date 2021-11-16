#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include "comun.h"
#include "sockets.h"
#include <time.h>
#include <locale.h>
#include <conio.h>
#include <Windows.h>

#define TCP 0
#define CLIENTS_PORT 2500

// Se agrega la librería ws2_32 a lista de dependencias
#pragma comment(lib, "ws2_32.lib")

int main()
{
    setlocale(LC_ALL, "");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);

    srand(time(NULL));

    WSADATA wsa;
    SOCKET sockfd;
    struct sockaddr_in server;
    struct sockaddr_in client;
    int server_port = 50000 + rand() % 101;
    
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
    server.sin_port = htons(server_port);

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
    
    int index;
    /* Aceptar la información de los sockets entrantes en forma iterativa */
    while(1)
    {
        size_t teclas_apretadas;
        do
        {
            teclas_apretadas = 0;
            printf("[SERVIDOR]: ");

            fflush(stdin);
            memset(buf_tx, 0, BUFFER_MAX+2);
            
            int tecla = 0;
            index = 0;
            while(tecla != 13)  // El bucle se repetirá mientras la tecla apretada no sea el enter
            {
                if(_kbhit())
                {
                    tecla = _getch();

                    // Para omitir las teclas Fn
                    if(_kbhit())
                    {
                        tecla = _getch();
                        continue;
                    }
                    
                    if(tecla != 13)
                    {
                        // La tecla 8 es el retroceso
                        if(tecla != 8)
                        {
                            if(teclas_apretadas < BUFFER_MAX)
                            {
                                fputc(tecla, stdout);
                                teclas_apretadas++;
                                buf_tx[index++] = tecla;
                            }
                        }
                        else if(teclas_apretadas > 0) // Que solo se permita retroceder si ya se escribió algo
                        {
                            teclas_apretadas--;
                            if(teclas_apretadas < BUFFER_MAX)
                                buf_tx[--index] = 0;
                            printf("\b \b");
                        }
                    }
                }
            }

            fputc('\n', stdout);

            // if(teclas_apretadas > BUFFER_MAX)
            //     printf("%ls", L"\n¡No se deben superar los 200 caracteres!\n\n");

        } while(teclas_apretadas > BUFFER_MAX);

        buf_tx[index++] = '\n';
        buf_tx[index++] = '\0';
        
        if(sendto(sockfd, buf_tx, index, 0, (struct sockaddr*)&client, sizeof(struct sockaddr_in)) < 0)
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
