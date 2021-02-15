#cython: profile=True
from libc.stdlib cimport malloc, free

cdef extern from "SinglyLinkedList.h":
	ctypedef struct Node:
		int data
		Node* nextNode
	ctypedef struct LinkedList:
		Node* headNode
	
	Node* createNewNode(int)
	LinkedList* createNewLinkedList()

	void freeLinkedList(LinkedList*)

	int isEmpty(LinkedList)
	void printLinkedList(LinkedList)
	int getData(int, LinkedList)

	int insertHead(int, LinkedList*)
	int insertTail(int, LinkedList*)
	int insertMid(int, int, LinkedList*)

	void deleteHead(LinkedList*)
	void deleteTail(LinkedList*)
	void deleteMid(int, LinkedList*)

	LinkedList* readFromFile(const char*)
	void writeToFile(LinkedList, const char*)

cdef char* fromStringToChar(str s):
	cdef:
		int n = len(s)
		int i
		char* newChar = <char*> malloc((n + 1) * sizeof(char))
	if newChar is NULL:
		raise MemoryError('Insufficent memory')
	for i in range(n):
		newChar[i] = ord(s[i])
	newChar[n] = '\0'
	return newChar

cdef class LList:
	cdef:
		LinkedList* llist
		char* temp
	
	def __cinit__(self, str fileName = ''):
		
		if fileName != '':
			temp = fromStringToChar(fileName)
			self.llist = readFromFile(temp)
			free(temp)
		else:
			self.llist = createNewLinkedList()
		
		if self.llist == NULL:
			raise MemoryError('Cannot initiallize linked list')
	
	def __dealloc__(self):
		if self.llist != NULL:
			freeLinkedList(self.llist)
	
	def toFile(self, str fileName):
		temp = fromStringToChar(fileName)
		writeToFile(self.llist[0], temp)
		free(temp)
	
	def printLL(self):
		printLinkedList(self.llist[0])
	
	cdef void insert_c(self, int data, int index):
		cdef int res
		if index == -1:
			res = insertTail(data, self.llist)
		elif index == 0:
			res = insertHead(data, self.llist)
		else:
			res = insertMid(data, index, self.llist)
		
		if res == 0:
			raise MemoryError('Insufficent Memory')
		
	def insert(self, int data, int index = -1):
		self.insert_c(data, index)
	
	def pop(self):
		deleteTail(self.llist)
