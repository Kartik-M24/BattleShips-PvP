/* ENGGEN131 C Project 2023 - Battleships */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAP_SIZE 6
#define HIT 1000

// Prototype declarations of required functions
void PrintArray(int values[MAP_SIZE][MAP_SIZE]);
void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]);
void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE]);
int CountValues(int value, int map[MAP_SIZE][MAP_SIZE]);
int TopLeftPosition(int size, int* row, int* col, int map[MAP_SIZE][MAP_SIZE]);
int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE]);
void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE]);
void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col);
int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE]);


/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go below
*******************************************************************************
*******************************************************************************
******************************************************************************/

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

void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]) {
	int pos;
	int value = 2;

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

void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE]) {
	int i, j, k, value1, value2;
	int ans[4] = { 0 };

	while ((ans[0] != 1) || (ans[1] != 1) || (ans[2] != 1) || (ans[3] != 1)) {
		int map1[MAP_SIZE][MAP_SIZE] = { 0 }; // resets array
		for (i = 2; i < 6; i++) {
			AddRandomShip(i, map1);
		}
		for (j = 2; j < 6; j++) {
			value1 = IsShipValid(j, map1);
			ans[j - 2] = value1;
		}
		for (k = 2; k < 6; k++) {
			value2 = CountValues(k, map1);
			if ((ans[k - 2] == 1) && (value2 == k)) {
				ans[k - 2] = 1;
			}
			else {
				ans[k - 2] = 0;
			}
		}

		if ((ans[0] == 1) && (ans[1] == 1) && (ans[2] == 1) && (ans[3] == 1)) {
			for (i = 0; i < MAP_SIZE; i++) {
				for (j = 0; j < MAP_SIZE; j++) {
					map[i][j] = map1[i][j];
				}
			}
		}
	}
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

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go above
*******************************************************************************
*******************************************************************************
******************************************************************************/

// Provided functions needed for playing the Battleships game:

// First, prototype declarations for the bots:
void GetMoveBot1(int shots[MAP_SIZE][MAP_SIZE], int* row, int* col);
void GetMoveBot2(int shots[MAP_SIZE][MAP_SIZE], int* row, int* col);

// Gets the input for one move from the human player (an alphabetic row and a numeric column)
// This function converts both inputs to numeric values
void GetMoveHuman(int* row, int* col, int player)
{
	char a = ' ';
	int b = -1;
	printf("Player %d: enter move [row/col]: ", player);
	while (!(a >= 'A' && a <= 'Z')) {
		scanf("%c", &a);
	}
	while (!(b >= 0 && b <= 25)) {
		scanf("%d", &b);
	}
	*row = (int)(a - 'A');
	*col = b;
}

// Takes two "shots" arrays as input (which are the visible parts of the game shown to players) and formats them into a string for printing
// The player currently to move is highlighted
void GetDisplayMapString(int shots1[MAP_SIZE][MAP_SIZE], int shots2[MAP_SIZE][MAP_SIZE], int player, char* boardString)
{
	int i, j;
	char numbers[10];
	// Intialise board string to be empty:
	boardString[0] = '\0';
	strcat(boardString, "  ");

	for (i = 0; i < MAP_SIZE; i++) {
		sprintf(numbers, "%d", i % 10);
		strcat(boardString, numbers);
	}
	strcat(boardString, "|");
	for (i = 0; i < MAP_SIZE; i++) {
		sprintf(numbers, "%d", i % 10);
		strcat(boardString, numbers);
	}
	strcat(boardString, "\n  ");

	for (i = 0; i < MAP_SIZE; i++) {
		strcat(boardString, "-");
	}
	strcat(boardString, "|");
	for (i = 0; i < MAP_SIZE; i++) {
		strcat(boardString, "-");
	}
	strcat(boardString, "\n");

	for (i = 0; i < MAP_SIZE; i++) {
		int len = strlen(boardString);
		boardString[len] = (char)('A' + i);
		boardString[len + 1] = '\0';
		strcat(boardString, "|");
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots1[i][j] / HIT > 0) {
				if (shots1[i][j] / HIT == 1) {
					strcat(boardString, "X");
				}
				else {
					sprintf(numbers, "%d", shots1[i][j] / HIT);
					strcat(boardString, numbers);
				}
			}
			else if (shots1[i][j] > 0) {
				strcat(boardString, ".");
			}
			else {
				strcat(boardString, " ");
			}
		}
		strcat(boardString, "|");
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots2[i][j] / HIT > 0) {
				if (shots2[i][j] / HIT == 1) {
					strcat(boardString, "X");
				}
				else {
					sprintf(numbers, "%d", shots2[i][j] / HIT);
					strcat(boardString, numbers);
				}
			}
			else if (shots2[i][j] > 0) {
				strcat(boardString, ".");
			}
			else {
				strcat(boardString, " ");
			}
		}
		strcat(boardString, "|");
		len = strlen(boardString);
		boardString[len] = (char)('A' + i);
		boardString[len + 1] = '\0';
		strcat(boardString, "\n");
	}
	if (player == 1) {
		strcat(boardString, "  P1");
		for (i = 0; i < MAP_SIZE - 2; i++) {
			strcat(boardString, "*");
		}
	}
	else {
		for (i = 0; i < MAP_SIZE; i++) {
			strcat(boardString, " ");
		}
		strcat(boardString, "   P2");
		for (i = 0; i < MAP_SIZE - 2; i++) {
			strcat(boardString, "*");
		}
	}
	strcat(boardString, "\n");
}

// Plays one game of Battleships, beginning with the specified starting player
// Game type = 1 (human vs human) or 2 (human vs bot) or 3 (bot vs bot)
int PlayOneGame(int startingPlayer, int gameType)
{
	int row, col, player, gameOver;

	// String to display the boards
	char displayBoardString[(2 * MAP_SIZE + 5) * (MAP_SIZE + 5)];

	// The maps containing the locations of the ships
	int mapPlayer1[MAP_SIZE][MAP_SIZE] = { 0 };
	int mapPlayer2[MAP_SIZE][MAP_SIZE] = { 0 };

	// The locations of the shots
	int shotsPlayer1[MAP_SIZE][MAP_SIZE] = { 0 };
	int shotsPlayer2[MAP_SIZE][MAP_SIZE] = { 0 };

	player = startingPlayer;
	gameOver = 0;

	// Create random maps for each player
	InitialiseRandomMap(mapPlayer1);
	InitialiseRandomMap(mapPlayer2);

	// Display the board if a human is playing
	if (gameType != 3) {
		GetDisplayMapString(shotsPlayer1, shotsPlayer2, player, displayBoardString);
		printf("%s", displayBoardString);
	}

	// Process one move for the current player
	while (!gameOver) {
		if (gameType == 1) {
			GetMoveHuman(&row, &col, player);
			if (player == 1) {
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			}
			else {
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		}
		else if (gameType == 2) {
			if (player == 1) {
				GetMoveHuman(&row, &col, player);
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			}
			else {
				GetMoveBot1(shotsPlayer2, &row, &col);
				printf("Player 2 (bot) moves: %c%d\n", (char)(row + 'A'), col);
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		}
		else {
			if (player == 1) {
				GetMoveBot1(shotsPlayer1, &row, &col);
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			}
			else {
				GetMoveBot2(shotsPlayer2, &row, &col);
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		}

		// Swap players
		if (!gameOver) {
			player = 3 - player;
		}
		if (gameType != 3) {
			GetDisplayMapString(shotsPlayer1, shotsPlayer2, player, displayBoardString);
			printf("%s", displayBoardString);
		}
	}
	return player;
}

// Play a Battleships tournament
// If the tournament is between a human and a bot, only one game is played
// If the tournament is between two bots, the number of games is requested
void PlayBattleships(void)
{
	int gameType, numberOfGames, result;
	int i, wins1, wins2, player;

	// Get play options:
	printf("Options:\n");
	printf(" [1] = Human vs. Human\n");
	printf(" [2] = Human vs. Bot1\n");
	printf(" [3] = Bot1 vs. Bot2\n");
	printf("Choose game type: ");
	scanf("%d", &gameType);
	numberOfGames = 1;
	result = 0;

	// If two bots are playing a tournament, let the user choose how many games
	if (gameType == 3) {
		printf("Number of games: ");
		scanf("%d", &numberOfGames);
	}

	// Set win counts to zero
	wins1 = 0;
	wins2 = 0;

	// Player 1 will always start the first game
	// If a tournament is played (between two bots), the starting player alternates
	player = 1;

	for (i = 0; i < numberOfGames; i++) {
		result = PlayOneGame(player, gameType);
		if (result == 1) {
			wins1++;
		}
		else {
			wins2++;
		}
		// Switch the starting player for the next game
		player = 3 - player;
	}

	// Show the outcome (of a single game or tournament)
	if (numberOfGames == 1) {
		printf("\nGame over! Congratulations! Winner is Player %d\n\n", result);
	}
	else {
		printf("\nTournament over! Games played = %d\nPlayer 1 wins = %d / Player 2 wins = %d\n\n", numberOfGames, wins1, wins2);
	}
}

// The main function for the Battleships program
int main(void)
{
	// Initialise the seed for the random number generator
	srand((unsigned int)time(NULL));

	printf("ENGGEN131 - C Project 2023\n");
	printf("                          ... presents ...\n");
	printf(" ___    __   _____ _____  _     ____  __   _     _   ___   __  \n");
	printf("| |_)  / /\\   | |   | |  | |   | |_  ( (` | |_| | | | |_) ( (` \n");
	printf("|_|_) /_/--\\  |_|   |_|  |_|__ |_|__ _)_) |_| | |_| |_|   _)_) \n");
	printf("\n                __/___            \n");
	printf("          _____/______|           \n");
	printf("  _______/_____\\_______\\_____     \n");
	printf("  \\              < < <       |    \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n");

	PlayBattleships();

	return 0;
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the two bots can be provided below
// The existing implementations are naive:
// - Bot 1 simply takes random shots (without checking for repeated shots)
// - Bot 2 also takes random shots (but makes a single test on each turn for a repeated shot)
*******************************************************************************
*******************************************************************************
******************************************************************************/

// Strategy for Bot 1
void GetMoveBot1(int shots[MAP_SIZE][MAP_SIZE], int* row, int* col)
{
	int rand_row;
	int rand_col;

	rand_row = shots[0][0]; // to prevent compiler warning (because otherwise "shots" array is not accessed)
	rand_row = rand() % MAP_SIZE;
	rand_col = rand() % MAP_SIZE;

	*row = rand_row;
	*col = rand_col;
}

// Strategy for Bot 2
void GetMoveBot2(int shots[MAP_SIZE][MAP_SIZE], int* row, int* col)
{
	int rand_row;
	int rand_col;

	rand_row = shots[0][0]; // to prevent compiler warning (because otherwise "shots" array is not accessed)
	rand_row = rand() % MAP_SIZE;
	rand_col = rand() % MAP_SIZE;

	// If the shot has been tried before, try one more time
	if (shots[rand_row][rand_col] > 0) {
		rand_row = rand() % MAP_SIZE;
		rand_col = rand() % MAP_SIZE;
	}

	*row = rand_row;
	*col = rand_col;
}













