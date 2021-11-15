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

int SocketConnect(int hSocket)
{
    int iRetval = -1;
    int ServerPort = 50080;
    struct sockaddr_in remote = {0};

    remote.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    remote.sin_family = AF_INET;
    remote.sin_port = htons(ServerPort);

    iRetval = connect(hSocket, (struct sockaddr*)&remote, sizeof(struct sockaddr_in));
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
