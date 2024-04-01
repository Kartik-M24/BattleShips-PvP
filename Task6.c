#define _CRT_SECURE_NO_WARNINGS
#define MAP_SIZE 6
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

int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE]) {
	int row, col, value;

	value = CountValues(size, map);
	if (value != size) {
		return 0;
	}

	for (row = 0; row < MAP_SIZE; row++) {
		for (col = 0; col < MAP_SIZE; col++) {
			if (map[row][col] == size) {
				if ((row != (MAP_SIZE - 1)) && (map[row + 1][col] != size) && (map[row + 1][col] != 0)) {
					return 0;
				}
				if ((row != 0) && (map[row - 1][col] != size) && (map[row - 1][col] != 0)) {
					return 0;
				}
				if ((col != (MAP_SIZE - 1)) && (map[row][col + 1] != size) && (map[row][col + 1] != 0)) {
					return 0;
				}
				if ((col != 0) && (map[row][col - 1] != size) && (map[row][col - 1] != 0)) {
					return 0;
				}
			}
		}
	}
	return 1;
}

int main(void) {

	return 0;
}