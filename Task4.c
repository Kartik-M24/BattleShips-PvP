#define MAP_SIZE 6
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int CountValues(int value, int map[MAP_SIZE][MAP_SIZE]) {
	int row, col, count;

	count = 0;
	for (row = 0; row < MAP_SIZE; row++) {
		for (col = 0; col < MAP_SIZE; col++) {
			if (map[row][col] == value) {
				count++;
			}
		}
	}
	return count;
}


int main(void) {

	return 0;
}