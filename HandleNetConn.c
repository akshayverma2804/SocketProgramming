/*-------------------------------------------------

Description : Source file for socket functions implementation.

*/
/*
Header files: ServerHeader.h

*/


#ifndef _ServerHeader_H_
#include "ServerHeader.h"
#define _ServerHeader_H_
#endif

#ifndef _Err_Winsock_H_ 
#include "Err_Winsock.h"
#endif

#ifndef _DataHeader_H_ 
#include "DataHeader.h"
#define _DataHeader_H_
#endif

/*
  Function Name: HandleNetConn
  
  Description: function to create and handle network sockets.
  Parameters\Arguments: None
  Return Values: int.
		  
*/	

 #pragma comment(lib,"ws2_32.lib") //Winsock Library
 

// Prototypes

BOOL CreateSocketInformation(SOCKET s);

void FreeSocketInformation(DWORD Index);

 

// Global var

DWORD TotalSockets = 0;

LPSOCKET_INFORMATION SocketArray[FD_SETSIZE];

SOCKET ListenSocket;
SOCKET AcceptSocket;
SOCKADDR_IN ServerAddr;
WSADATA wsaData;
FD_SET WriteSet;
FD_SET ReadSet;
int mod_init=0;


int HandleNetConn()
{
   int iResult;
   DWORD i;
   DWORD Total;
   ULONG NonBlock;
   DWORD Flags, SendBytes, RecvBytes;
   
	iResult=init_socket();
 
 	if (!iResult)
	{
			// Prepare a socket to listen for connections
		   if (bind(ListenSocket, (PSOCKADDR) &ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
			{
			  printf("error in binding the port");
			  closesocket(ListenSocket);
			  WSACleanup();
			  return ERR_SERVER_BIND_FAILED;
		   }

			printf("Bind succeeded");		 

			if (listen(ListenSocket, MAX))
			{
				printf("error in Listening");
				closesocket(ListenSocket);
				WSACleanup();
				return ERR_SERVER_LISTEN_FAILED;
			}	
			
			printf("\n\nServer Listening\n");

		   // Change the socket mode on the listening socket from blocking to

		   // non-block so the application will not block waiting for requests

		   NonBlock = 1;

		   if (ioctlsocket(ListenSocket, FIONBIO, &NonBlock) == SOCKET_ERROR)
		   {
			  printf("ioctlsocket() failed with error\n");
			  return ERR_IOCTLSOCKET_FAILED;

		   }
	 

		   while(TRUE)
		   {
				// Prepare the Read and Write socket sets for network I/O notification
				FD_ZERO(&ReadSet);
				FD_ZERO(&WriteSet);
				// Always look for connection attempts
				FD_SET(ListenSocket, &ReadSet);

				// Set Read and Write notification for each socket based on the

				// current state the buffer.  If there is data remaining in the

				// buffer then set the Write set otherwise the Read set

				for (i = 0; i < TotalSockets; i++)
				{
						FD_SET(SocketArray[i]->Socket, &ReadSet);
				}

			  if ((Total = select(0, &ReadSet, &WriteSet, NULL, NULL)) == SOCKET_ERROR)
			  {
				 printf("select() returned with error\n");
				 return 1;
			  }
			  else
				printf("select() is OK!\n");

			  // Check for arriving connections on the listening socket.

			  if (FD_ISSET(ListenSocket, &ReadSet))
			  {
				 Total--;
				 if ((AcceptSocket = accept(ListenSocket, NULL, NULL)) != INVALID_SOCKET)
				 {
					// Set the accepted socket to non-blocking mode so the server will
					// not get caught in a blocked condition on WSASends

					NonBlock = 1;
					if (ioctlsocket(AcceptSocket, FIONBIO, &NonBlock) == SOCKET_ERROR)
					{
					   printf("ioctlsocket(FIONBIO) failed with error\n");
					   return 1;
					}
					else
					   printf("ioctlsocket(FIONBIO) is OK!\n");

					if (CreateSocketInformation(AcceptSocket) == FALSE)
					{
						 printf("CreateSocketInformation(AcceptSocket) failed!\n");
						 return 1;
					}
					else
						printf("CreateSocketInformation() is OK!\n");
				 }
				 else
				 {
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
					   printf("accept() failed with error\n");
					   return 1;
					}
					else
					   printf("accept() is fine!\n");
				 }
			  }

			  // Check each socket for Read notification until the number
			  // of sockets in Total is satisfied

			  for (i = 0; Total > 0 && i < TotalSockets; i++)
			  {
				 LPSOCKET_INFORMATION SocketInfo = SocketArray[i];

				 // If the ReadSet is marked for this socket then this means data

				 // is available to be read on the socket

				 if (FD_ISSET(SocketInfo->Socket, &ReadSet))

				 {

					Total--;
					SocketInfo->DataBuf.buf = SocketInfo->Buffer;
					SocketInfo->DataBuf.len = DATA_BUFSIZE;
					Flags = 0;

					if (WSARecv(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &RecvBytes, &Flags, NULL, NULL) == SOCKET_ERROR)
					{
					   if (WSAGetLastError() != WSAEWOULDBLOCK)
					   {
						  printf("WSARecv() failed with error\n");
						  FreeSocketInformation(i);
					   }
					   else
						  printf("WSARecv() is OK!\n");

					   continue;

					}

					else
					{
					   SocketInfo->BytesRECV = RecvBytes;

					   // If zero bytes are received, this indicates the peer closed the connection.

					   if (RecvBytes == 0)
					   {
						  FreeSocketInformation(i);
						  continue;
					   }
					}
				 }
			  }

		   }

		}
		return ERR_SUCCESS;
	}
 

BOOL CreateSocketInformation(SOCKET s)
{   
	LPSOCKET_INFORMATION SI;
	printf("Accepted socket number\n");

   if ((SI = (LPSOCKET_INFORMATION) GlobalAlloc(GPTR, sizeof(SOCKET_INFORMATION))) == NULL)
   {
      printf("GlobalAlloc() failed with error \n");
      return FALSE;
   }

   else
      printf("GlobalAlloc() for SOCKET_INFORMATION is OK!\n");


   // Prepare SocketInfo structure for use

   SI->Socket = s;
   SI->BytesRECV = 0;

   SocketArray[TotalSockets] = SI;
   TotalSockets++;
   return(TRUE);

}

 

void FreeSocketInformation(DWORD Index)
{
   LPSOCKET_INFORMATION SI = SocketArray[Index];
   DWORD i;

   closesocket(SI->Socket);
   printf("Closing socket number\n");
   GlobalFree(SI);

   // Squash the socket array

   for (i = Index; i < TotalSockets; i++)
   {
      SocketArray[i] = SocketArray[i + 1];
   }
   TotalSockets--;

}


_declspec(dllexport) int init_socket()
{
	int iResult;
	ListenSocket = INVALID_SOCKET;
	AcceptSocket = INVALID_SOCKET;
	
	if ((iResult = WSAStartup(MAKEWORD(2,2),&wsaData)) != 0)
   {
		printf("WSAStartup() failed with error\n");
		WSACleanup();
		return ERR_WINSOCK_INIT_FAILED;
   }
   
    if ((ListenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		printf("Error creating a listening socket");
		WSACleanup();
		return ERR_SOCKET_CREATION_FAILED;
	}
	
	ServerAddr.sin_family = AF_INET;			//getting server info
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServerAddr.sin_port = htons(PORT);
		   
	iResult = EventAndThreadInit();
	return ERR_SUCCESS;
   
 }