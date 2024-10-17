// e.g. 2d array: array of array
// buffer in memory with collection of pointers, and each pointer points to an array
#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

int main() {
	int* arr = new int[50]; // allocaation of memory = ( arr size ) x ( each size of element ) = 50 x 4
	int** arr2d = new int* [50]; // collection of pointers pointing to int* array (NOT pointing to int)
	// allocation of memory = ( size of int* ) x ( number of arrays ) = 4 x 50

	// now we have 50 pointers to point to 50 arrarys
	for (int i = 0; i < 50; i++) {
		arr2d[i] = new int[50]; // for each i, allocated size-50 array = 50 x 4
	}

	// 3d array
	int*** arr3d = new int**[50];
	for (int i = 0; i < 50; i++) {
		arr3d[i] = new int*[50];
		for (int j = 0; j < 50; j++) {
			int** ptr2d = arr3d[i];
			ptr2d[j] = new int[50];
		}
	}

	std::cout << sizeof(arr3d[0][0][0]) << std::endl; // int - 4 byte

	// Back to 2d array
	arr2d[0][0] = 0; // [index of pointer][index to integer]

	// deleting heap allocated multidimensional array
	// delete[] arr2d; // only delete 200 bytes of array of interger pointers -> memory leak
	for (int i = 0; i < 50; i++) // Correct approach
		delete[] arr2d[i];
	delete[] arr2d;

	// resolving memory fragmentation
	int* arr2 = new int[5]; 
	int** arr2d2 = new int* [5];  // arr2d has 25 integers - but they are not in a contiguous space in memory, thus cache miss issue may occur

	for (int i = 0; i < 5; i++) { // this is much slower than 25 elements is contigious space
		arr2d2[i] = new int[5]; 
	}

	for (int y = 0; y < 5; y++) { // accessing 25 elements
		for (int x = 0; x < 5; x++) {
			arr2d2[y][x] = 0;
		}
	}

	// optimize memory accessing - reduce cache misses
	int* array = new int[5 * 5]; // 25 elements in a row

	for (int i = 0; i < 25; i++)
		array[i] = 0;

	// or access like...
	for (int y = 0; y < 5; y++) { 
		for (int x = 0; x < 5; x++) {
			array[x + y * 5] = 0;
		}
	}
	// therefore, avoid multi dimensional array if possible 
	std::cin.get();
}