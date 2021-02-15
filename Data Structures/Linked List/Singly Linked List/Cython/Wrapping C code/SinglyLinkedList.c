#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "SinglyLinkedList.h"

// Contructor
Node* createNewNode(int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if(newNode == NULL)
		return NULL;
	else
	{
		newNode->data = data; newNode->nextNode = NULL;
		return newNode;
	}
}

LinkedList* createNewLinkedList()
{
	LinkedList* newLinkedList = (LinkedList*)malloc(sizeof(LinkedList));
	if(newLinkedList == NULL)
		return NULL;
	else
	{
		newLinkedList->headNode = NULL;
		return newLinkedList;
	}
}

// Destructor
void freeLinkedList(LinkedList* L)
{
	Node* currentNode = L->headNode;
	while(currentNode)
	{
		Node* temp = currentNode;
		currentNode = currentNode->nextNode;
		free(temp);
	}
	if(L != NULL)
		free(L);
}

// Basic operation
int isEmpty(LinkedList L)
{
	return (L.headNode == NULL);
}

void printLinkedList(LinkedList L)
{
	Node* currentNode = L.headNode;
	while(currentNode)
	{
		printf("%d ", currentNode->data);
		currentNode = currentNode->nextNode;
	}
	printf("\n");
}

int getData(int index, LinkedList L)
{
	int i = 0;
	Node* currentNode = L.headNode;
	while(currentNode)
	{
		if(i == index)
			return currentNode->data;
		currentNode = currentNode->nextNode; i += 1;
	}
	return INT_MAX;
}

// Insertion
int insertHead(int newData, LinkedList* L)
{
	Node* newNode = createNewNode(newData);
	if(newNode != NULL)
	{
		if(isEmpty(*L))
			L->headNode = newNode;
		else
		{
			newNode->nextNode = L->headNode;
			L->headNode = newNode;
		}
		
		return 1;
	}
	return 0;
}

int insertTail(int newData, LinkedList* L)
{
	Node* newNode = createNewNode(newData);
	if(newNode != NULL)
	{
		if(isEmpty(*L))
			L->headNode = newNode;
		else
		{
			Node* currentNode = L->headNode;
			while(currentNode->nextNode)
				currentNode = currentNode->nextNode;
			currentNode->nextNode = newNode;
		}
		return 1;
	}
	
	return 0;
}

int insertMid(int newData, int indexAfter, LinkedList* L)
{
	Node* newNode = createNewNode(newData);
	if(newNode != NULL)
	{
		if(isEmpty(*L))
		{
			L->headNode = newNode;
			return 1;
		}
		else
		{
			int i = 0;
			Node* currentNode = L->headNode;
			
			while((currentNode != NULL) && (i != indexAfter))
			{
				currentNode = currentNode->nextNode; i += 1;
			}
			
			if(currentNode)
			{
				Node* temp = currentNode->nextNode;
				newNode->nextNode = temp;
				currentNode->nextNode = newNode;
				return 1;
			}
			
			free(currentNode);
			return 0;
		}
	}
	
	return 0;
}

// Deletion
void deleteHead(LinkedList* L)
{
	if(!isEmpty(*L))
	{
		Node* temp = L->headNode;
		L->headNode = temp->nextNode;
		free(temp);
	}
}

void deleteTail(LinkedList* L)
{
	if(!isEmpty(*L))
	{
		Node* currentNode = L->headNode;
		if(currentNode->nextNode == NULL)
		{
			L->headNode = NULL;
			free(currentNode);
		}
		else
		{
			while(currentNode->nextNode->nextNode)
				currentNode = currentNode->nextNode;
			Node* temp = currentNode->nextNode;
			currentNode->nextNode = NULL;
			free(temp);
		}
	}
}

void deleteMid(int indexAfter, LinkedList* L)
{
	int i = 0;
	Node* currentNode = L->headNode;

	while((currentNode != NULL) && (i != indexAfter))
	{
		currentNode = currentNode->nextNode; i += 1;
	}
	
	if(currentNode != NULL)
		if(currentNode->nextNode != NULL)
		{
			Node* temp = currentNode->nextNode;
			currentNode->nextNode = temp->nextNode;
			free(temp);
		}
}

// File operations
LinkedList* readFromFile(const char* fileName)
{
	FILE *fp = fopen(fileName, "r");
	if(fp != NULL)
	{
		char buffer[255];
		LinkedList* newList = createNewLinkedList();
		if(newList != NULL)
		{
			while(fgets(buffer, 255, fp))
    			insertTail(atoi(buffer), newList);
    		return newList;
    	}
	}
	fclose(fp);
	return NULL;
}
void writeToFile(LinkedList L, const char* fileName)
{
	FILE *fp = fopen(fileName, "w");
	if(fp != NULL)
	{
		if(!isEmpty(L))
		{
			Node* currentNode = L.headNode;
			while(currentNode)
			{
				char line[255];
				sprintf(line, "%d\n", currentNode->data);
				fprintf(fp, line);
				currentNode = currentNode->nextNode;
			}
		}
	}
	fclose(fp);
}
