#ifndef __SOCKETS
#define __SOCKETS

#include <winsock.h>

#define SERVER_ADDRESS "192.168.100.4"
#define LOCAL_BROADCAST "192.168.100.255"

SOCKET SocketCreate(void);

int SocketConnect(int hSocket);

int SocketSend(int hSocket, char* Rqst, short lenRqst);

int SocketReceive(int hSocket, char* Rsp, short RvcSize);

#endif