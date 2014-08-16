/*-------------------------------------------------

Description : Header file for socket related structure and functions.

*/
/*
Header files: ServerHeader.h

*/

#pragma once

#include <winsock2.h>

#include <ws2tcpip.h>

#ifndef _psapi_H
#include <psapi.h>
#define _psapi_H
#endif
#include <string.h>


#ifndef _Err_Winsock_H_
#include "Err_Winsock.h"
#define _Err_Winsock_H
#endif

#ifndef _DataHeader_H_ 
#include "DataHeader.h"
#define _DataHeader_H_
#endif


#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define TRUE   1
#define FALSE  0
#define PORT 8888
#define SERVER_IP "127.0.0.1"
#define DEFAULT_BUFLEN 1024
#define MAX 5000
#define DATA_BUFSIZE 8192

typedef struct _SOCKET_INFORMATION 
{
   CHAR Buffer[DATA_BUFSIZE];
   WSABUF DataBuf;
   SOCKET Socket;
   OVERLAPPED Overlapped;
   DWORD BytesSEND;
   DWORD BytesRECV;

}SOCKET_INFORMATION, *LPSOCKET_INFORMATION;


_declspec(dllexport) int HandleNetConn();
_declspec(dllexport) int init_socket();

