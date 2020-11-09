#include <iostream>
#include <memory.h>
#include "Stack.h"

Stack::Stack(int size)
{
	this-> size = size;
	this->st = this->top = new int[size];
}

Stack::~Stack()
{
	delete[] st;
}

bool Stack::isEmpty()
{
	return this->st == this->top;
}

bool Stack::isFull()
{
	return (this->top - this->st) >= this->size;
}

void Stack::push(const int& newEle)
{
	if(isFull())
	{
		int* temp = this->st;
		this->st = this->top = new int[this->size + 1];
		memcpy(this->st, temp, (this->size) * sizeof(int));
		this->top += this->size;
		++this->size;
		delete[] temp;
	}
	*this->top++ = newEle;
}

void Stack::pop(int& dummyValue)
{
	if(!isEmpty())
		dummyValue = *--this->top;
}

std::istream& operator >> (std::istream& is, Stack& inputStack)
{
	int inputValue;
	is >> inputValue;
	inputStack.push(inputValue);
	return is;
}
