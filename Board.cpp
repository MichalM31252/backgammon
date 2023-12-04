#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <stdio.h>

#include "Board.h"
#include "FileInterface.h"

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

void setUpBar(Board* board, int idOfPlayer) {
	board->bar->playerId = idOfPlayer;
	board->bar->numberOfPawns = 0;
}

void setUpCourt(Board* board, int idOfPlayer) {
	board->court[idOfPlayer]->playerId = idOfPlayer;
	board->court[idOfPlayer]->numberOfPawns = 0;
}

void setUpBoard(Board* board) {
	initBoard(board);
	setupFieldsFromFile(board);
	setUpBar(board, 1);
	setUpCourt(board, 0);
	setUpCourt(board, 1);
	saveBoardToFile(board);
}