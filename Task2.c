#define _CRT_SECURE_NO_WARNINGS
#define MAP_SIZE 6
#include <stdio.h>

void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]) {
	int pos, i, j;
	int value = 2;

	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			map[i][j] = 0;
		}
	}

	while (value < 6) {
		if (value == 2) {
			map[MAP_SIZE - 2][MAP_SIZE - 1] = value;
			map[MAP_SIZE - 1][MAP_SIZE - 1] = value;
		}
		else if (value == 5) {
			for (pos = 0; pos < value; pos++) {
				map[0][pos] = value;
			}
		}
		else if (value == 3) {
			for (pos = 0; pos < value; pos++) {
				map[2][pos] = value;
			}
		}
		else if (value == 4) {
			for (pos = 0; pos < value; pos++) {
				map[4][pos] = value;
			}
		}
		value++;
	}
}

void PrintArray(int values[MAP_SIZE][MAP_SIZE]) {
	int i, j;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j <= MAP_SIZE; j++) {
			if (j == MAP_SIZE) {
				printf("\n");
			}
			else {
				printf("%d ", values[i][j]);
			}
		}
	} //Not sure if last line (i and j = MAP_SIZE should not equal new line)
}

int main(void) {
	int map[MAP_SIZE][MAP_SIZE] = { 0 };
	InitialiseMap(map);
	PrintArray(map);
	return 0;
}