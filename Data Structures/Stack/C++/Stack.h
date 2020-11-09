#include <iostream>

class Stack
{
	private:
		int size;
		int *st, *top;
	public:
		Stack(int size = 1);
		~Stack();
		
		bool isEmpty();
		bool isFull();
		
		void push(const int&);
		void pop(int&);
		friend std::istream& operator >> (std::istream&, Stack&);
};
