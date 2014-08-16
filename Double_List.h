#include <stdio.h>

/*

Description: header file to declare the double linked list functions.
*/

typedef struct _Double_Link_List	//Structure for double Linked List 
{
	struct _Double_Link_List *Flink;	//forward link	
	struct _Double_Link_List *Blink;	//back link 
}DOUBLE_LINK_LIST,*pDOUBLE_LINK_LIST;

_declspec(dllexport) pDOUBLE_LINK_LIST DOUBLE_LINK_LIST_ALLOCATION();		//To allocate memory for double link list	
_declspec(dllexport) void initialize_DOUBLE_LINK_LIST(pDOUBLE_LINK_LIST); 	  //To initialize a list to NULL	
_declspec(dllexport) int INSERT_NODE_TO_LIST(pDOUBLE_LINK_LIST, pDOUBLE_LINK_LIST); //To insert a new node to a list
_declspec(dllexport) pDOUBLE_LINK_LIST DETECH_NODE_FROM_LIST(pDOUBLE_LINK_LIST); //To remove a node from front of the list 
_declspec(dllexport) pDOUBLE_LINK_LIST GET_FIRST_NODE(pDOUBLE_LINK_LIST);	// To get the first data node from the list
_declspec(dllexport) pDOUBLE_LINK_LIST DELETE_NODE(pDOUBLE_LINK_LIST, pDOUBLE_LINK_LIST); // To delete a specified node from the list


