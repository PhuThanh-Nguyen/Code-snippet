#include <iostream>

class Queue
{
	private:
		int size;
		int* bottom, *top, *queue;
	public:
		Queue(int size = 1);
		~Queue();
		
		bool isFull();
		bool isEmpty();
		
		void enqueue(const int&);
		void dequeue(int&);
		friend std::istream& operator >> (std::istream&, Queue&);
};
