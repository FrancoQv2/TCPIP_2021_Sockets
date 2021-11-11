#include <stdio.h>
#include <winsock.h>

#define TCP 1

// Se agrega la librería ws2_32 a lista de dependencias
#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsa;
    SOCKET s;

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
    if((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
        printf("No se pudo crear el socket: %d", WSAGetLastError());

#else

    if((s = Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
        printf("No se pudo crear el socket: %d", WSAGetLastError());
    
#endif

    printf("Socket creado.\n");

    return 0;
}
