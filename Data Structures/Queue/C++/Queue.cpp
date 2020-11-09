#include <iostream>
#include <memory.h>
#include "Queue.h"

Queue::Queue(int size)
{
	this->size = size;
	this->queue = this->bottom = this->top = new int[size];
}

Queue::~Queue()
{
	if(queue != nullptr)
		delete[] queue;
}

bool Queue::isFull()
{
	return (this->top - this->bottom >= this->size);
}

bool Queue::isEmpty()
{
	return this->top == this->bottom;
}

void Queue::enqueue(const int& newEle)
{
	if(isFull())
	{
		int* temp = this->queue;
		this->queue = this->bottom = this->top = new int[this->size + 1];
		memcpy(this->queue, temp, (this->size) * sizeof(int));
		this->top += this->size;
		++this->size;
		delete[] temp;
	}
	*this->top++ = newEle;
}

void Queue::dequeue(int& dummyValue)
{
	if(!isEmpty())
		dummyValue = *this->bottom++;
}

std::istream& operator >> (std::istream& is, Queue& inputQueue)
{
	int inputValue;
	is >> inputValue;
	inputQueue.enqueue(inputValue);
	return is;
}
