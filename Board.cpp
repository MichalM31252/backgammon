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

	board->diceBag = new DiceBag();
}

void setUpBar(Board* board) {
	// i don't need to set up the player here, because i don't know which player is going to be on the bar first
	board->bar->numberOfPawns = 0;
}

void setUpCourt(Board* board, Player* p, int idOfPlayer) {
	board->court[idOfPlayer]->player = p;
	board->court[idOfPlayer]->numberOfPawns = 0;
}

void setUpBoard(Board* board, Player *red, Player *white) { // this only takes the most basic board from file (default settings from file)
	// also add here the list of players
	initBoard(board);

	// I need to initialize the DiceBag, Bar and court here

	 setUpDiceBag(board, red, white);
	 setUpBar(board);
	 setUpCourt(board, red, red->id);
	 setUpCourt(board, white, white->id);


	setupBoardFromFile(board, red, white); // this just writes the data into the structures from the file, the structures must be initialized by this point



	// saveBoardToFile(board, currentPlayer); this line is for saving the currently loaded board into the file, add currentPlayer where this needs to be saved

}

void setUpDiceBag(Board* board, Player* red, Player* white) {

	// 

	//int currentPlayerNumber = decideWhichPlayerGoesFirst();
	//DiceBag diceBag; // create the dice bag
	//if (currentPlayerNumber == idOfPlayerRed) {
	//	initDiceBag(&diceBag, red);
	//}
	//if (currentPlayerNumber == idOfPlayerWhite) {
	//	initDiceBag(&diceBag, white);
	//}

	board->diceBag = new DiceBag(); // doesnt this line create a memory leak ???
}