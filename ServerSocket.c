
#include "ServerHeader.h"
#include "Err_Winsock.h"
//#include "Array_Queue.h"

//#pragma comment (lib, "Ws2_32.lib")	//this is required to link the lib file

//pQUEUE BufQueue;

int main()
{	
	int Result;
	Result=HandleNetConn();
	return;
}