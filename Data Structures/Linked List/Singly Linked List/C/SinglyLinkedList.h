#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node* nextNode;
}Node;

typedef struct LinkedList
{
	struct Node* headNode;
}LinkedList;

// Contructor
Node* createNewNode(int);
LinkedList* createNewLinkedList();

// Destructor
void freeLinkedList(LinkedList*);

// Basic operation
int isEmpty(LinkedList);
void printLinkedList(LinkedList);
int getData(int, LinkedList);

// Insertion
int insertHead(int, LinkedList*);
int insertTail(int, LinkedList*);
int insertMid(int, int, LinkedList*); // Insert after index

// Deletion
void deleteHead(LinkedList*);
void deleteTail(LinkedList*);
void deleteMid(int, LinkedList*); // Delete after index

// File operations
LinkedList* readFromFile(const char*);
void writeToFile(LinkedList, const char*);
