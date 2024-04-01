#define _CRT_SECURE_NO_WARNINGS
#define MAP_SIZE 6

#include <stdio.h>
#include <stdlib.h>

void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE]) {
	int horz_or_vert, hpos, vpos, row, col;
	horz_or_vert = rand() % 2; //horz - 0 vert - 1

	if (horz_or_vert == 0) {
		hpos = rand() % (MAP_SIZE - size + 1);
		vpos = rand() % (MAP_SIZE);
		for (row = hpos; row < (hpos + size); row++) {
			map[vpos][row] = size;
		}
	}
	if (horz_or_vert == 1) {
		hpos = rand() % (MAP_SIZE);
		vpos = rand() % (MAP_SIZE - size + 1);
		for (col = vpos; col < (vpos + size); col++) {
			map[col][hpos] = size;
		}
	}
}

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
	int row, col;

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

void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE]) {
	int i, j, k, value1, value2;
	int ans[4] = { 0 };

	while ((ans[0] != 1) || (ans[1] != 1) || (ans[2] != 1) || (ans[3] != 1)) {
		int l, m;
		for (l = 0; l < MAP_SIZE; l++) {
			for (m = 0; m < MAP_SIZE; m++) {
				 map[l][m] = 0; // resets array
			}
		}

		for (i = 2; i < 6; i++) {
			AddRandomShip(i, map);
		}
		for (j = 2; j < 6; j++) {
			value1 = IsShipValid(j, map);
			ans[j - 2] = value1;
		}
		for (k = 2; k < 6; k++) {
			value2 = CountValues(k, map);
			if ((ans[k - 2] == 1) && (value2 == k)) {
				ans[k - 2] = 1;
			}
			else {
				ans[k - 2] = 0;
			}
		}
	}
}

int main(void) {

	return 0;
}