#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <stdio.h>

#include "Board.h"

using namespace std;

// Everything related to the board

void initBoard(Board* board) {
	for (int i = 0; i < amountOfFields; i++) {
		board->fields[i] = new Field();
	}

	board->bar = new Bar();

	for (int i = 0; i < amountOfCourt; i++) {
		board->court[i] = new Court();
	}
}

int setupBoardFromFile(Board* board) 
{

	FILE* file = fopen("basic_board.txt", "r");
	if (file == NULL) {
		perror("Error opening the file");
	}

	int idOfPlayer, positionOfPawn;

	for (int i = 0; i < amountOfPawns; i++)
	{

		if (fscanf(file, "%d %d", &idOfPlayer, &positionOfPawn) != 2) {
			printf("Error reading numbers from the file\n");
			fclose(file);
			return 1;
		}

		board->fields[positionOfPawn - 1]->numberOfPawns++;
		board->fields[positionOfPawn - 1]->playerId = idOfPlayer;

		cout << "Player " << idOfPlayer << " has " << board->fields[positionOfPawn-1]->numberOfPawns << " pawns on field " << positionOfPawn << endl;
	}

	board->bar->numberOfPawns = 0;
	board->bar->playerId = 0; // FIX THIS

	for (int i = 0; i < amountOfCourt; i++) {
		board->court[i]->numberOfPawns = 0;
		board->court[i]->playerId = 0; // FIX THIS
	}

	return 0;
}