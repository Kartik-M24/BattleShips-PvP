#define _CRT_SECURE_NO_WARNINGS
#define MAP_SIZE 7
#include <stdio.h>

int TopLeftPosition(int size, int* row, int* col, int map[MAP_SIZE][MAP_SIZE]) {
	int i, j, direction;

	// check top left position
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (map[i][j] == size) {
				*row = i;
				*col = j;

				//check direction
				if (map[i + 1][j] == size) {
					direction = 2;
				}
				if (map[i][j + 1] == size) {
					direction = 1;
				}
				return direction;
			}
		}
	}
	return -1; // MAY BE AN ERROR DOUBLE CHECK BUT REMOVES WARNING
}

int main(void) {
	int row, col, direction;
	int map[MAP_SIZE][MAP_SIZE] = {
	  {0, 0, 0, 3, 3, 3, 0},
	  {0, 5, 0, 0, 0, 0, 0},
	  {0, 5, 0, 0, 4, 0, 0},
	  {0, 5, 0, 0, 4, 0, 0},
	  {0, 5, 0, 0, 4, 0, 0},
	  {0, 5, 0, 0, 4, 0, 0},
	  {0, 0, 2, 2, 0, 0, 0}
	};
	for (int shipSize = 2; shipSize <= 5; shipSize++) {
		direction = TopLeftPosition(shipSize, &row, &col, map);
		printf("Ship %d is at (%d, %d) facing %d\n", shipSize, row, col, direction);
	}
	return 0;
}