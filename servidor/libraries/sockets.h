#ifndef __SOCKETS
#define __SOCKETS

#include <winsock.h>

SOCKET SocketCreate(void);

int SocketSend(int hSocket, char* Rqst, short lenRqst);

int SocketReceive(int hSocket, char* Rsp, short RvcSize);

#endif