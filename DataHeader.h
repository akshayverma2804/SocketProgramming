/*-------------------------------------------------

Description : Header file for Data related structure and functions.

*/
/*
Header files: ServerHeader.h

*/

#ifndef _windows_H_ 
#include "windows.h"
#endif

#ifndef _Err_Winsock_H_
#define _Err_Winsock_H
#endif

#ifndef _psapi_H
#include <psapi.h>
#endif

#define NUMBEROFPROC (4*2)

HANDLE hEvent;
HANDLE hThread[NUMBEROFPROC]; //thread handles which are doubled to the number of procs on the box
DWORD dwThreadIdArray[NUMBEROFPROC];

typedef struct client_info
{
	char HostName[50];
	//char ClientIPAddress[10];
	//PROCESS_MEMORY_COUNTERS Client_Pmc;
	MEMORYSTATUSEX Client_statex;
}CLIENT_INFO,*pCLIENT_INFO;

_declspec(dllexport) int EventAndThreadInit();
_declspec(dllexport) void DataHandling();
