#define _CRT_SECURE_NO_WARNINGS
#define MAP_SIZE 6

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

int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE]) {
	int i, j, k, l, value_small, value_large, row, col, direction, count;

	//Find smallest and largest ship value in map
	value_large = 0;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (value_large < map[i][j]) {
				value_large = map[i][j];
			}
		}
	}
	value_small = value_large;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if ((value_small > map[i][j]) && (map[i][j] != 0)) {
				value_small = map[i][j];
			}
		}
	}

	// Check if all ships are destroyed
	for (k = value_small; k <= value_large; k++) {
		direction = TopLeftPosition(k, &row, &col, map);
		count = 0;
		for (l = 0; l < k; l++) {
			if (direction == 1) { // horizontal
				if ((shots[row][col + l]) / (k * 1000) == 1) {
					count++;
				}
			}
			else { // vertical
				if ((shots[row + l][col]) / (k * 1000) == 1) {
					count++;
				}
			}
		}
		if (count != k) { //if any ships aren't fully destroyed
			return 0;
		}
	}

	return 1; // if all ships didn't return 0 then all ships are fully destroyed

}

int main(void) {
	
	return 0;
}

