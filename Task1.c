#define MAP_SIZE 10
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


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
	int values[MAP_SIZE][MAP_SIZE];
	PrintArray(values[MAP_SIZE][MAP_SIZE]);

	return 0;
}