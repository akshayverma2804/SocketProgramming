#include "ServerHeader.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define DEFAULT_COUNT       20
#define DEFAULT_PORT        8888
#define DEFAULT_BUFFER      2048
#define DEFAULT_MESSAGE     "\'A test message from client\'"

 

char  szServer[128];                          // Server to connect to

int   iPort     = DEFAULT_PORT;    // Port on server to connect to

DWORD dwCount   = DEFAULT_COUNT; // Number of times to send message

BOOL  bSendOnly = FALSE;                        // Send data only; don't receive

 

// Function: usage:

// Description: Print usage information and exit

void usage()
{
    printf("Chapter5TestClient: select_client localhost \n\n");
    printf("\n");
}

 

// Function: ValidateArgs

// Description:

//    Parse the command line arguments, and set some global flags  

//    to indicate what actions to perform

void ValidateArgs(int argc, char **argv)
{
	strcpy_s(szServer, sizeof(szServer),&argv[1][3]);
}

 

// Function: main

// Description:

//    Main thread of execution. Initialize Winsock, parse the 

//    command line arguments, create a socket, connect to the 

//    server, and then send and receive data.

int main(int argc, char **argv)

{

    WSADATA       wsd;
		MEMORYSTATUSEX statex;
		int result;

    SOCKET        sClient;

    char          szBuffer[DEFAULT_BUFFER];

    int           ret, i;
		CLIENT_INFO client1;


    struct sockaddr_in server;
    struct hostent    *host = NULL;


            if(argc < 2)

            {
                        usage();

                        exit(1);

            }

 

    // Parse the command line and load Winsock

    ValidateArgs(argc, argv);

    if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)

    {

        printf("Failed to load Winsock library! Error %d\n", WSAGetLastError());

        return 1;

    }

    else

        printf("Winsock library loaded successfully!\n");
 

    // Create the socket, and attempt to connect to the server

    sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sClient == INVALID_SOCKET)

    {

        printf("socket() failed with error code %d\n", WSAGetLastError());

        return 1;

    }

    else

        printf("socket() looks fine!\n");
 
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_family=AF_INET;
	server.sin_port=htons(8888);
	
		statex.dwLength = sizeof (statex);

	GlobalMemoryStatusEx (&statex);
	
	result=gethostname(client1.HostName,sizeof(client1.HostName));
	
	client1.Client_statex=statex;
	

    if (connect(sClient, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)

    {

        printf("connect() failed with error code %d\n", WSAGetLastError());

        return 1;

    }

    else

        printf("connect() is pretty damn fine!\n");

 

    // Send and receive data

    printf("Sending and receiving data if any...\n");

 

  //  for(i = 0; i < (int)dwCount; i++)
    //{

        ret = send(sClient, (void *)&client1, sizeof(client1), 0);

        if (ret == 0)
			printf("\nData sent");
           // break;

        else if (ret == SOCKET_ERROR)

        {
		

            printf("send() failed with error code %d\n", WSAGetLastError());

           // break;

        }

 

        printf("send() should be fine. Send %d bytes\n", ret);

    //}

 

    if(closesocket(sClient) == 0)

            printf("closesocket() is OK!\n");

    else

            printf("closesocket() failed with error code %d\n", WSAGetLastError());

 

    if (WSACleanup() == 0)

            printf("WSACleanup() is fine!\n");

    else

            printf("WSACleanup() failed with error code %d\n", WSAGetLastError());

 

    return 0;

}
