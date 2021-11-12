#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>

#define SERVER_ADDRESS "192.168.100.4"
#define PORT 8888

#define TCP 1

// Se agrega la librería ws2_32 a lista de dependencias
#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsa;
    SOCKET sockfd;
    struct sockaddr_in server;

    size_t recv_size;

    const char* buf_tx = "Hola servidor, soy un cliente";
    char* buf_rx = malloc(100);

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
    // 0: uso del protocolo TCP
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
        printf("No se pudo crear el socket: %d", WSAGetLastError());

#else

    if((sockfd = Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
        printf("No se pudo crear el socket: %d", WSAGetLastError());
    
#endif

    printf("Socket creado.\n");

    server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    // Conectar al servidor remoto
    if(connect(sockfd, (struct sockaddr*)&server, sizeof(server)))
    {
        printf("La conexi%cn con el servidor fall%c.\n", 162, 162);
        return -1;
    }

    printf("Conectado al servidor.\n");

    /* enviar secuencias de testeo */
    // if(send(sockfd, buf_tx, sizeof(buf_tx), 0) < 0)
    // {
    //     printf("Env%co fallido.\n", 160);
    //     return 1;
    // }

    // printf("Informaci%cn enviada.\n", 162);

    // Recibir una respuesta del servidor
    // if((recv_size = recv(sockfd, buf_rx, 100, 0)) == SOCKET_ERROR)
    //     printf("Recepci%cn fallida.\n", 162);

    // printf("Respuesta recibida.\n");

    // Añadir el caracter nulo para adaptar bien la cadena antes de imprimir
    // buf_rx[recv_size] = '\0';

    // puts(buf_rx);

    return 0;
}
