#include <stdio.h>
#include <winsock.h>

// Se agrega la librería ws2_32 a lista de dependencias
#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsa;

    printf("\nInitialising Winsock...");
    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        return 1;
    }

    printf("Initialised.");

    return 0;
}