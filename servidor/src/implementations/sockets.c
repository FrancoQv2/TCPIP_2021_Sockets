#include "sockets.h"
#include <stdio.h>

SOCKET SocketCreate()
{
    SOCKET hSocket;
    if((hSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "No se pudo crear el socket: %d", WSAGetLastError());
        exit(-1);
    }

    return hSocket;
}

int SocketSend(int hSocket, char* Rqst, short lenRqst)
{
    int shortRetval = -1;
    
    shortRetval = send(hSocket, Rqst, lenRqst, 0);

    return shortRetval;
}

int SocketReceive(int hSocket, char* Rsp, short RvcSize)
{
    int shortRetval = -1;
    shortRetval = recv(hSocket, Rsp, RvcSize, 0);

    return shortRetval;
}
