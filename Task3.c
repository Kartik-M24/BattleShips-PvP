#define _CRT_SECURE_NO_WARNINGS
#define MAP_SIZE 6

//CHECK IF THIS IS CORRECT AGAIN 
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

int main(void) {

	return 0;
}