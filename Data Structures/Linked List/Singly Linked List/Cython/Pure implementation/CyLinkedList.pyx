#cython: profile=True
from libc.stdlib cimport malloc, free, atoi
from libc.stdio cimport printf, FILE, fopen, fclose, fgets, sprintf, fprintf

ctypedef struct Node:
	int data
	Node* nextNode

ctypedef struct LinkedList:
	Node* headNode

cdef Node* createNewNode(int data):
	cdef Node* newNode = <Node*>malloc(sizeof(Node))
	if newNode is NULL:
		raise MemoryError('Insufficent Memory')
	newNode.data = data
	newNode.nextNode = NULL
	return newNode

cdef LinkedList* createNewLinkedList():
	cdef LinkedList* newLinkedList = <LinkedList*>malloc(sizeof(LinkedList))
	if newLinkedList is NULL:
		raise MemoryError('Insufficent Memory')
	newLinkedList.headNode = NULL
	return newLinkedList

cdef void freeLinkedList(LinkedList* L):
	cdef:
		Node* temp
		Node* currentNode = L.headNode
	
	while currentNode is not NULL:
		temp = currentNode
		currentNode = currentNode.nextNode
		free(temp)
	
	if L is not NULL:
		free(L)

cdef int isEmpty(LinkedList L):
	return L.headNode is NULL

cdef void printLinkedList(LinkedList L):
	cdef Node* currentNode = L.headNode
	while currentNode is not NULL:
		printf('%d ', currentNode.data)
		currentNode = currentNode.nextNode
	printf('\n')

cdef int insertHead(int newData, LinkedList* L):
	cdef Node* newNode = createNewNode(newData)
	if newNode is not NULL:
		if isEmpty(L[0]):
			L.headNode = newNode
		else:
			newNode.nextNode = L.headNode
			L.headNode = newNode
		return 1
	return 0

cdef int insertTail(int newData, LinkedList* L):
	cdef:
		Node* newNode = createNewNode(newData)
		Node* currentNode
	
	if newNode is not NULL:
		if isEmpty(L[0]):
			L.headNode = newNode
		else:
			currentNode = L.headNode
			while currentNode.nextNode is not NULL:
				currentNode = currentNode.nextNode
			currentNode.nextNode = newNode
		return 1
	return 0

cdef int insertMid(int newData, int indexAfter, LinkedList* L):
	cdef:
		int i = 0;
		Node* newNode = createNewNode(newData)
		Node* currentNode = L.headNode
		Node* temp
		
	if newNode is not NULL:
		if isEmpty(L[0]):
			L.headNode = newNode
			return 1
		else:
			while (currentNode is not NULL) and (i != indexAfter):
				currentNode = currentNode.nextNode
				i += 1
			
			if currentNode is not NULL:
				temp = currentNode.nextNode
				newNode.nextNode = temp
				currentNode.nextNode = newNode
				return 1
			
			free(newNode)
			return 0
	return 0

cdef int deleteHead(LinkedList* L):
	cdef:
		Node* temp
		int returnVal
	
	if isEmpty(L[0]) == 0:
		temp = L.headNode
		returnVal = temp.data
		L.headNode = temp.nextNode
		free(temp)
	
		return returnVal
	
	raise IndexError('Empty linked list')

cdef int deleteTail(LinkedList* L):
	cdef:
		Node* currentNode
		Node* temp
		int returnVal
	
	if isEmpty(L[0]) == 0:
		currentNode = L.headNode
		if currentNode.nextNode is NULL:
			returnVal = currentNode.data
			L.headNode = NULL
			free(currentNode)
		else:
			while currentNode.nextNode.nextNode is not NULL:
				currentNode = currentNode.nextNode
			temp = currentNode.nextNode
			returnVal = temp.data
			currentNode.nextNode = NULL
			free(temp)
		return returnVal
	
	raise IndexError('Empty linked list')

cdef int deleteMid(int indexAfter, LinkedList* L):
	cdef:
		int i = 0, returnVal
		Node* currentNode = L.headNode
		Node* temp

	while (currentNode != NULL) and (i != indexAfter):
		currentNode = currentNode.nextNode
		i += 1
	
	if currentNode != NULL:
		if currentNode.nextNode != NULL:
			temp = currentNode.nextNode
			returnVal = temp.data
			currentNode.nextNode = temp.nextNode
			free(temp)
			return returnVal
	
	raise IndexError('Empty linked list or index out of bound')

cdef LinkedList* readFromFile(const char* fileName):
	cdef:
		char buff[255]
		LinkedList* newList = createNewLinkedList()
		FILE *fp = fopen(fileName, "r")
	
	if fp is not NULL:
		if(newList is not NULL):
			while fgets(buff, 255, fp) is not NULL:
				insertTail(atoi(buff), newList)
			return newList
	fclose(fp)
	return NULL
cdef void writeToFile(LinkedList L, const char* fileName):
	cdef:
		FILE *fp = fopen(fileName, "w")
		Node* currentNode
		char line[255]
	if fp is not NULL:
		if isEmpty(L) == 0:
			currentNode = L.headNode	
			while currentNode:
				sprintf(line, "%d\n", currentNode.data)
				fprintf(fp, line)
				currentNode = currentNode.nextNode
	fclose(fp)
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
	
	def __cinit__(self, list init_list = []):
		
		self.llist = createNewLinkedList()
		
		if self.llist == NULL:
			raise MemoryError('Cannot initiallize linked list')
		
		for val in init_list:
			self.insert(val)
	
	@classmethod
	def fromFile(self, str fileName = ''):
		cdef char* temp
		returnLList = LList()
		if fileName != '':
			temp = fromStringToChar(fileName)
			
			if returnLList.llist != NULL:
				free(returnLList.llist)
				
			returnLList.llist = readFromFile(temp)
			free(temp)
			
			return returnLList
		
		raise ValueError(f"{fileName} doesn't exist")
	
	def __dealloc__(self):
		if self.llist != NULL:
			freeLinkedList(self.llist)
	
	def isEmpty(self):
		return bool(isEmpty(self.llist[0]))
	
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
	
	cdef int pop_c(self, int index):
		cdef int returnVal
		if index == -1:
			returnVal = deleteTail(self.llist)
		elif index == 0:
			returnVal = deleteHead(self.llist)
		else:
			returnVal = deleteMid(index - 1, self.llist)
		return returnVal
	
	def insert(self, int data, int index = -1):
		self.insert_c(data, index)
	
	def pop(self, index = -1):
		return self.pop_c(index)
