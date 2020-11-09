#include <iostream>

int linearSearch(int searchKey, int arr[], int n)
{
	for(int i = 0; i < n; ++i)
		if(arr[i] == searchKey)
			return i;
	return -1;
}

int main()
{
	int arr[] = {2,1,4,3,7,0}, n = 6;
	std::cout << arr[0] << " at position " << linearSearch(arr[0], arr, 6) << "\n";
	std::cout << arr[1] << " at position " << linearSearch(arr[1], arr, 6) << "\n";
	std::cout << arr[2] << " at position " << linearSearch(arr[2], arr, 6) << "\n";
	return 0;
}
