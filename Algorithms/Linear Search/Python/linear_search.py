
def linearSearch(L, searchVal):
	'''
		Perform linear search on list
		Params:
			L: list, array-like
				Array to search value in
			searchVal: Suitable type to parameter L
				Value to be searched in L
		Returns: index i such that L[i] == searchVal, returns -1 if no such value in array L
	'''
	for index, obj in enumerate(L):
		if obj == searchVal:
			return index
	return -1

def main():
	'''
		Test linearSearch on list
	'''
	L = [4,1,6,5,2]
	print(f'L = {L}')
	print('{} is at index: {}'.format(L[0], linearSearch(L, L[0])))
	print('{} is at index: {}'.format(L[1], linearSearch(L, L[1])))
	print('{} is at index: {}'.format(L[-1], linearSearch(L, L[-1])))
	
	'''
		Test linearSearch on set
	'''
	L = {4,1,6,5,2}
	print(f'L = {L}')
	print('{} is at index: {}'.format(4, linearSearch(L, 4)))
	print('{} is at index: {}'.format(1, linearSearch(L, 1)))
	print('{} is at index: {}'.format(2, linearSearch(L, 2)))
	
	'''
		Test linearSearch on tuple
	'''
	L = (4,1,6,5,2)
	print(f'L = {L}')
	print('{} is at index: {}'.format(4, linearSearch(L, 4)))
	print('{} is at index: {}'.format(1, linearSearch(L, 1)))
	print('{} is at index: {}'.format(2, linearSearch(L, 2)))

if __name__ == '__main__':
	main()
