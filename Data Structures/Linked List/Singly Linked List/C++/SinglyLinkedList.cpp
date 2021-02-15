#include "SinglyLinkedList.h"
#include <fstream>
#include <limits>

Node::Node(int data)
{
	this->data = data;
	this->nextNode = NULL;
}

Node::~Node()
{
	// do nothing
}

LinkedList::LinkedList()
{
	this->headNode = NULL;
}

LinkedList::LinkedList(std::string fileName)
{	
	this->headNode = NULL;
	std::fstream fileObj;
	fileObj.open(fileName, std::ios::in);
	if(fileObj.is_open())
	{
		int data;
		while(fileObj >> data)
			this->insertTail(data);
		fileObj.close();
	}
}

LinkedList::~LinkedList()
{
	Node* currentNode = this->headNode;
	while(currentNode != NULL)
	{
		Node* temp = currentNode;
		currentNode = currentNode->nextNode;
		delete temp;
	}
}

bool LinkedList::isEmpty()
{
	return this->headNode == NULL;
}

int LinkedList::insertHead(int data)
{
	Node* newNode = new Node(data);
	if(newNode != NULL)
	{
		if(this->isEmpty())
			this->headNode = newNode;
		else
		{
			newNode->nextNode = this->headNode;
			this->headNode = newNode;
		}
		return 1;
	}
	
	return 0;
}
int LinkedList::insertTail(int data)
{
	Node* newNode = new Node(data);
	if(newNode != NULL)
	{
		if(this->isEmpty())
			this->headNode = newNode;
		else
		{
			Node* currentNode = this->headNode;
			while(currentNode->nextNode != NULL)
				currentNode = currentNode->nextNode;
			currentNode->nextNode = newNode;
		}
		return 1;
	}
	
	return 0;
}
int LinkedList::insertMid(int index, int data)
{
	Node* newNode = new Node(data);
	if(newNode != NULL)
	{
		if(this->isEmpty())
		{
			this->headNode = newNode;
			return 1;
		}
		else
		{
			int i = 0;
			Node* currentNode = this->headNode;
			
			while((currentNode != NULL) && (i != index))
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
			
			delete newNode;
			return 0;
		}
	}
	
	return 0;
}

void LinkedList::deleteHead()
{
	if(!this->isEmpty())
	{
		Node* temp = this->headNode;
		this->headNode = temp->nextNode;
		delete temp;
	}
}
void LinkedList::deleteTail()
{
	if(!this->isEmpty())
	{
		Node* currentNode = this->headNode;
		if(currentNode->nextNode == NULL)
		{
			this->headNode = NULL;
			delete currentNode;
		}
		else
		{
			while(currentNode->nextNode->nextNode)
				currentNode = currentNode->nextNode;
			Node* temp = currentNode->nextNode;
			currentNode->nextNode = NULL;
			delete temp;
		}
	}
}
void LinkedList::deleteMid(int indexAfter)
{
	int i = 0;
	Node* currentNode = this->headNode;

	while((currentNode != NULL) && (i != indexAfter))
	{
		currentNode = currentNode->nextNode; i += 1;
	}
	
	if(currentNode != NULL)
		if(currentNode->nextNode != NULL)
		{
			Node* temp = currentNode->nextNode;
			currentNode->nextNode = temp->nextNode;
			delete temp;
		}
}

void LinkedList::writeToFile(std::string fileName)
{
	std::fstream fileObj;
	fileObj.open(fileName, std::ios::out);
	if((fileObj.is_open()) && (!this->isEmpty()))
	{
		Node* currentNode = this->headNode;
		while(currentNode != NULL)
		{
			fileObj << currentNode->data << "\n";
			currentNode = currentNode->nextNode;
		}
		fileObj.close();
	}
}

int LinkedList::operator[](int index)
{
	if(this->isEmpty())
	{
		std::cout << "WARNING: Linked list is empty\n";
		return std::numeric_limits<int>::max();
	}
	
	else
	{
		int i = 0;
		Node* currentNode = this->headNode;
		while(currentNode != NULL)
		{
			if(i == index)
				return currentNode->data;
			currentNode = currentNode->nextNode; ++i;
		}
		
		std::cout << "WARNING: Index out of bound\n";
		return std::numeric_limits<int>::max();
	}
}

std::ostream &operator<<(std::ostream & os, const LinkedList& L)
{
	Node* currentNode = L.headNode;
	while(currentNode != NULL)
	{
		os << currentNode->data << " ";
		currentNode = currentNode->nextNode;
	}
	return os;
}
