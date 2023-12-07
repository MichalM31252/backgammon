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

void setUpBar(Board* board) {
	// i don't need to set up the player here, because i don't know which player is going to be on the bar first
	board->bar->numberOfPawns = 0;
}

void setUpCourt(Board* board, Player* p, int idOfPlayer) {
	board->court[idOfPlayer]->player = p;
	board->court[idOfPlayer]->numberOfPawns = 0;
}

void setUpBoard(Board* board, Player *red, Player *white) {
	// also add here the list of players

	initBoard(board);

	setUpDiceBag(board, red, white);

	setupBoardFromFile(board, red, white);
	setUpBar(board);
	//setUpCourt(board, players->id, red.id);
	//setUpCourt(board, &white, white.id);
	saveBoardToFile(board);

	// also here should be saveCourtToFile
	// save Bar to file 
}

void currentOwnerOfDiceBag(Board* board, Player* player) {
	board->diceBag->player = player;
}

void setUpDiceBag(Board* board, Player* red, Player* white) {

	int currentPlayerNumber = decideWhichPlayerGoesFirst();
	DiceBag diceBag; // create the dice bag
	if (currentPlayerNumber == idOfPlayerRed) {
		initDiceBag(&diceBag, red);
	}
	if (currentPlayerNumber == idOfPlayerWhite) {
		initDiceBag(&diceBag, white);
	}

	board->diceBag = new DiceBag();
}