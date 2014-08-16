/*-------------------------------------------------

Description : Source file for socket functions implementation.

*/
/*
Header files: ServerHeader.h

*/


#ifndef _ServerHeader_H_ 
#include "ServerHeader.h"
#endif

#ifndef _Err_Winsock_H_ 
#include "Err_Winsock.h"
#endif

#ifndef _DataHeader_H_ 
#include "DataHeader.h"
#endif

_declspec(dllexport) int EventAndThreadInit()
{

	int i;

	hEvent = CreateEvent(NULL,               // default security attributes
						0,               // auto-reset event
						0,              // initial state is nonsignaled
						"ReadEvent"   // object name
						); 

	if (hEvent == NULL) 
	{ 
		printf("CreateEvent failed");
		return ERR_CREATE_EVENT_FAILED;
	}

	for (i=0; i < NUMBEROFPROC;i++)
	{
		hThread[i]=CreateThread(NULL,
								0,
								0,
								0,
									0,
									&dwThreadIdArray[i]);
			if (hThread[i] == NULL) 
			{
				printf("CreateThread failed");
				return ERR_CREATE_THREAD_FAILED;
			}

	}
	return ERR_SUCCESS;
}