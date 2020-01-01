#ifndef COMMSOCK_H
#define COMMSOCK_H

#ifdef WIN32
/*-------------------------------windows-------------------------------*/
#include <WinSock2.h>
#include <windows.h>
#include <Ws2tcpip.h>
#define SOCKLEN  int
#pragma comment(lib, "ws2_32.lib")
/*-------------------------------windows end---------------------------*/
#else
/*-------------------------------linux---------------------------------*/
#include<netinet/in.h>
#include<sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<sys/un.h>
#define SOCKLEN  socklen_t
#define closesocket close
/*-------------------------------linux end-------------------------------*/
#endif


#endif //COMMSOCK_H