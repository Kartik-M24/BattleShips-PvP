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

void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col) {
	int i, j, k, l, order_num, shipval, row_pos, col_pos, direction, count;

	// Keeps track of shot order
	order_num = 1;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots[i][j] != 0) {
				order_num++;
			}
		}
	}

	if ((map[row][col] == 2) || (map[row][col] == 3) || (map[row][col] == 4) || map[row][col] == 5) {
		shipval = map[row][col];
		direction = TopLeftPosition(shipval, &row_pos, &col_pos, map);
		if (shots[row][col] == 0) {
			shots[row][col] = 1000 + order_num;
		}
		count = 0;
		for (k = 0; k < shipval; k++) { // checks to see if ship is destroyed
			if (direction == 1) { // horizontal
				if ((shots[row_pos][col_pos + k]) / 1000 == 1) {
					count++;
				}
			}
			else { // vertical
				if ((shots[row_pos + k][col_pos]) / 1000 == 1) {
					count++;
				}
			}
		}

		if (count == shipval) {
			for (l = 0; l < shipval; l++) {
				if (direction == 1) { // horizontal
					shots[row_pos][col_pos + l] = shots[row_pos][col_pos + l] + (1000 * (shipval - 1));
				}
				else { // vertical
					shots[row_pos + l][col_pos] = shots[row_pos + l][col_pos] + (1000 * (shipval - 1));
				}
			}
		}
	}
	else { // shot missed
		if (shots[row][col] == 0) { //shot hasn't already been made
			shots[row][col] = order_num;
		}
	}

}

int main(void) {

	return 0;
}