/*

Description: header file to define the double linked list functions.
*/

/*
Header files

User defined header file named "Double_List.h"
*/

//#include <stdio.h>
#include "Double_List.h"
#include "Err_Custom.h"

/*
  Function Name:DOUBLE_LINK_LIST_ALLOCATION
  Description: Used to initialize a list, set the list->Flink and Blink to NULL .			   
  Parameters\Arguments: None
  Return Values: returns a pointer to DOUBLE_LINK_LIST structure.
		  
*/	

_declspec(dllexport) pDOUBLE_LINK_LIST DOUBLE_LINK_LIST_ALLOCATION()	//To allocate memory for EMPLOYEE Node
{
	pDOUBLE_LINK_LIST temp;
	temp=(pDOUBLE_LINK_LIST)malloc(sizeof(DOUBLE_LINK_LIST)); //NULL Check is performed in the test code
	return temp;
}

_declspec(dllexport) void Initialize_DOUBLE_LINK_LIST_HEAD(pDOUBLE_LINK_LIST ListHead) 	  //To initialize a list to NULL	
{
	if (ListHead)
	{
		ListHead->Flink=NULL;
		ListHead->Blink=NULL;
	}
}

/*
  Function Name:IsDoubleLinkListEmpty
  Description: checks if a list is empty or not.
  Parameters\Arguments: Pointer of type DOUBLE_LINK_LIST structure (list head).
  Return Values: None
*/

_declspec(dllexport) int IsDoubleLinkListEmpty(pDOUBLE_LINK_LIST ListHead) 	  //To check if the list is empty	
{
	if (ListHead==NULL)
	{
		return ERR_LIST_EMPTY;
	}
	else
	{
		return ERR_SUCCESS;
	}
}

/*
  Function Name:INSERT_NODE_TO_LIST
  Description: It inserts a  node to a list.
  Parameters\Arguments: Pointer of type DOUBLE_LINK_LIST structure (list head) and takes a pointer to the node needs to be inserted.
  Return Values: None
*/

_declspec(dllexport) int INSERT_NODE_TO_LIST(pDOUBLE_LINK_LIST ListHead, pDOUBLE_LINK_LIST NEW_NODE) //To link a new node to a list
{
	pDOUBLE_LINK_LIST temp;
	if (ListHead == NULL)
	{
		return ERR_LIST_EMPTY;
	}
	
	if (NEW_NODE == NULL)
	{
		return ERR_NODE_EMPTY;
	}
	else
	{
		NEW_NODE->Blink=ListHead;
		NEW_NODE->Flink=ListHead->Flink;
		if (ListHead->Flink!=NULL)
		{
			NEW_NODE->Flink->Blink=NEW_NODE;
		}
		ListHead->Flink=NEW_NODE;
		return ERR_SUCCESS;
	}
} 

/*
  Function Name:DETECH_NODE_FROM_LIST
  Description: To remove (detach) a node from front of the list 
  Parameters\Arguments: Pointer of type DOUBLE_LINK_LIST structure (list head).
  Return Values: pointer to pDOUBLE_LINK_LIST structure that is detached
*/

_declspec(dllexport) pDOUBLE_LINK_LIST DETECH_NODE_FROM_LIST(pDOUBLE_LINK_LIST ListHead) //To remove (detach) a node from front of the list 
{
	pDOUBLE_LINK_LIST temp=NULL;
	
	if (ListHead->Flink==NULL)
	{
		return NULL;
	}
	else
	{
		temp=ListHead->Flink;
		ListHead->Flink=temp->Flink;
		return temp;
	}
}

/*
  Function Name:GET_FIRST_NODE
  Description: To get the first data node from the list
  Parameters\Arguments: Pointer of type DOUBLE_LINK_LIST structure (list head).
  Return Values: pointer to pDOUBLE_LINK_LIST which is the first data node
*/

_declspec(dllexport) pDOUBLE_LINK_LIST GET_FIRST_NODE(pDOUBLE_LINK_LIST ListHead)
{
	if (!IsDoubleLinkListEmpty(ListHead))
	{
		return ListHead->Flink;
	}
	else
	{
		return NULL;
	}
}

/*
  Function Name:DELETE_NODE
  Description: To  delete a specified node from the list
  Parameters\Arguments: Pointer of type DOUBLE_LINK_LIST structure (list head) and pointer to the node that is needs to be deleted.
  Return Values: pointer to pDOUBLE_LINK_LIST which is deleted from the list or NULL if there is no data node
*/

_declspec(dllexport) pDOUBLE_LINK_LIST DELETE_NODE(pDOUBLE_LINK_LIST ListHead, pDOUBLE_LINK_LIST DelNode) //To remove (detach) a node from front of the list 
{
	pDOUBLE_LINK_LIST temp=NULL;
	
	if (ListHead->Flink==NULL)
	{
		return NULL;
	}
	temp=DelNode;
	if (DelNode->Flink!=NULL)
	{
		DelNode->Blink->Flink=DelNode->Flink;
		DelNode->Flink->Blink=DelNode->Blink;
	}
	return temp;
}
