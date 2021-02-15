#include <iostream>
#include <string>

class Node
{		
	public:
		int data;
		Node* nextNode;
		
		Node(int);
		~Node();
};

class LinkedList
{
	private:
		Node* headNode;
	
	public:
		LinkedList();
		LinkedList(std::string);
		~LinkedList();
		
		bool isEmpty();
		
		int insertHead(int);
		int insertTail(int);
		int insertMid(int, int);
		
		void deleteHead();
		void deleteTail();
		void deleteMid(int);
		
		void writeToFile(std::string);
		
		int operator[](int);
		friend std::ostream &operator<<(std::ostream &, const LinkedList&);
};
