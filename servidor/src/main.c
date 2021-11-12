#include <stdio.h>
#include <winsock.h>

#define TCP 1
#define SERVER_ADDR "192.168.100.4"
#define SERVER_PORT 8888
#define BACKLOG 3       // Solo se pueden poner en pendiente 3 conexiones como máximo

// Se agrega la librería ws2_32 a lista de dependencias
#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsa;
    SOCKET sockfd, new_socket;
    struct sockaddr_in server, client;
    int c;

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

    if((s = Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
        printf("No se pudo crear el socket: %d", WSAGetLastError());
    
#endif

    printf("Socket creado.\n");

    // Preparar la estructura sockaddr_in
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    server.sin_port = htons(SERVER_PORT);

    if(bind(sockfd, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
        printf("Fall%c el bind con c%cdigo de error: %d", 162, 162, WSAGetLastError());

    puts("Bind hecho");

    // Escuchar conexiones entrantes
    listen(sockfd, BACKLOG);

    puts("Esperando conexiones entrantes...");

    c = sizeof(struct sockaddr_in);
    new_socket = accept(sockfd, (struct sockaddr*)&client, &c);
    if(new_socket == INVALID_SOCKET)
        printf("accept fall%c con c%cdigo de error: %d", 162, 162, WSAGetLastError());

    printf("Conexi%cn aceptada", 162);
    
    closesocket(sockfd);
    WSACleanup();

    return 0;
}
