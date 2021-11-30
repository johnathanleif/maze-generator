#include "array_functions.h"
#include <stdio.h>

enum{false, true};

void printArraySeperated(const int length, const int array[], const char seperator) {
	for(int i = 0; i < length; i++) {
		printf("%d%c", array[i], seperator);
	}
	printf("\n");
}

void printArray(const int length, const int array[]) {
	printArraySeperated(length, array, '\0');
}

void print2dArray(const int height, const int width, const int array[height][width]) {
	for(int i = 0; i < height; i++) {
		printArray(width, array[i]);
	}
}

int inArray(const int elem, const int length, const int array[]) {
	for(int i = 0; i < length; i++) {
		if(array[i] == elem)
			return true;
	}
	return false;
}

