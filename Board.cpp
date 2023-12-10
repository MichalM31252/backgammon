#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <stdio.h>

#include "Board.h"
#include "FileInterface.h"
#include "EveryMoveBag.h""

#include <stdio.h> // graphical library
#include "conio2.h"

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

void setUpBoard(Board* board, Player *red, Player *white, Player* currentPlayer) { // this only takes the most basic board from file (default settings from file)
	// also add here the list of players
	initBoard(board);

	// I need to initialize the DiceBag, Bar and court here

	 setUpDiceBag(board, red, white);
	 setUpBar(board);
	 setUpCourt(board, red, red->id);
	 setUpCourt(board, white, white->id);


	setupBoardFromFile(board, red, white, currentPlayer); // this just writes the data into the structures from the file, the structures must be initialized by this point

	 // this line is for saving the currently loaded board into the file, add currentPlayer where this needs to be saved

}

void setUpDiceBag(Board* board, Player* red, Player* white) {

	board->diceBag = new DiceBag(); // doesnt this line create a memory leak ???
}

void freeBoard(Board* board) {
	for (int i = 0; i < amountOfFields; i++) {
		delete board->fields[i];
	}

	delete board->bar;

	for (int i = 0; i < amountOfCourt; i++) {
		delete board->court[i];
	}

	delete board->diceBag;
}

int isOwnerOfField(Board* board, Player* currentPlayer, int fieldNumber) { // if the owner of the selected field is the currentPlayer return 1 (true) else 0
	if (board->fields[fieldNumber - 1]->player == currentPlayer) {
		return 1;
	}
	return 0;
}

int canMoveToField(Board* board, Player* currentPlayer, int moveFrom, int moveTo) {
	if (board->fields[moveFrom - 1]->numberOfPawns < 1) {
		return 0; // can't move from a field that has no pawns
	}
	if (board->fields[moveTo - 1]->numberOfPawns == 0) {
		return 1; // can place the pawn since its empty
	}
	if (board->fields[moveTo - 1]->numberOfPawns > 0) {
		if (isOwnerOfField(board, currentPlayer, moveTo) == 1) { // if there are multiple pawns of the current player we can place the pawn
			return 1;
		}
		if (isOwnerOfField(board, currentPlayer, moveTo) == 0) { // if not owner of the field
			if (board->fields[moveTo - 1]->numberOfPawns == 1) {
				return 1; // REMEMBER TO CAPTURE PAWN
			}
			if (board->fields[moveTo - 1]->numberOfPawns > 1) {
				return 0;
			}
		}
	}
	return 0;
}

int canCapturePawn(Board* board, Player* currentPlayer, int moveFrom, int moveTo) {
	if (board->fields[moveTo - 1]->numberOfPawns == 1) {         // if there is only one pawn on the field
		if (isOwnerOfField(board, currentPlayer, moveTo) == 0) { // if enemy is owner of the field
			return 1;
		}
	}
	return 0;
}

int isMoveInsideBoard(int moveFrom, int moveTo){
	if ((moveTo > 0 && moveTo < amountOfFields + 1) && (moveFrom > 0 && moveFrom < amountOfFields + 1)) {
		return 1;
	}
	return 0;
}

int isMoveToCourt(int moveFrom, int moveTo) {
	if (moveTo == courtIndexRed + 1 || moveTo == courtIndexWhite + 1) {
		return 1;
	}
	return 0;
}

int isMovePossibleUsingDicebag(Board* board, Player* currentPlayer, int moveFrom, int moveTo, EveryMoveBag* everyMoveBag) {
	// get the array of every possible move and check if current move is in the array
	// if yes return 1	
	// if no return 0

	for (int i = 0; i < everyMoveBag->numberOfElements; i++) {
		if (everyMoveBag->numbers[i] == moveFrom) {
			if (everyMoveBag->numbers[i + 1] == moveTo) {
				return 1;
			}
		}
	}
	return 0;
}

int isMoveInsideBoardValid(Board* board, Player* currentPlayer, int moveFrom, int moveTo, EveryMoveBag* everyMoveBag) {
	if (isMoveInsideBoard(moveFrom, moveTo) == 0) { // checks if the move is inside the board
		return 0;
	}
	if (isOwnerOfField(board, currentPlayer, moveFrom) == 0) { // checks if the field we want to move from belongs to the current player
		return 0;
	}
	if (canMoveToField(board, currentPlayer, moveFrom, moveTo) == 0) { // checks if we can move to the field
		return 0;
	}
	if (isMovePossibleUsingDicebag(board, currentPlayer, moveFrom, moveTo, everyMoveBag) == 0) { // checks if the move is possible using the dicebag
		return 0;
	}
	// add a function to check if there are any pawns in the field we want to move from
	// add a function to check if there are any pawns in the bar (do it outside of this function it will be more readable)
	return 1;
}

int isMoveValid(Board* board, Player* currentPlayer, int moveFrom, int moveTo, EveryMoveBag* everyMoveBag) {
	// different function for movint to court 
	// different function for moving from field to field

	// also check if there are any pawns in the bar
	if (isMoveInsideBoardValid(board, currentPlayer, moveFrom, moveTo, everyMoveBag) == 1) { // for moving inside the board (ONLY FIELDS)
		return 1;
	}
	return 0;

	// else 
	// check if move is to court

}

void removePawn(Board* board, Player* player, int fieldNumber) {
	board->fields[fieldNumber - 1]->numberOfPawns--;
	if (board->fields[fieldNumber - 1]->numberOfPawns == 0) {
		board->fields[fieldNumber - 1]->player = NULL;
	}
}

void addPawn(Board* board, Player* player, int fieldNumber) {
	board->fields[fieldNumber - 1]->numberOfPawns++;
	board->fields[fieldNumber - 1]->player = player;
}

void movePawn(Board* board, Player* player, int moveFrom, int moveTo) {
	// need to make sure that there is a function for taking the pawn from the enemy and placing it into the bar (if the enemy has only one pawn on the field) BEFORE EXECUTING THIS FUNCTION SO THERE ARENT TWO PLAYERS
	// ON THE SAME FIELD

	// need to make sure that there is a function that takes care of the most optimal placing the pawn to the court 

	removePawn(board, player, moveFrom);
	addPawn(board, player, moveTo);
	initDiceBag(board->diceBag, player); // reset the dicebag
}

/////////////

void addMoveOneDice(EveryMoveBag* everyMoveBag, Board* board, Player* currentPlayer, int currentPosition, int collectCapturingMoves) {
	int directionOfMoves = getDirectionOfMoves(currentPlayer);
	for (int j = 0; j < board->diceBag->numberOfElements; j++) {
		int moveFrom = currentPosition;
		int moveTo = currentPosition + board->diceBag->numbers[j] * directionOfMoves;
		if (isMoveInsideBoard(moveFrom, moveTo) == 1 && canMoveToField(board, currentPlayer, moveFrom, moveTo) == 1) { // if you add here a 3rd && statement that checks if the values are the same then you will get rid of the bug that shows the same move multiple times
			if (canCapturePawn(board, currentPlayer, moveFrom, moveTo) == collectCapturingMoves) { // if the move is a capturing move and we want to collect only capturing moves
				addMoveToEveryMoveBag(everyMoveBag, moveFrom);                               // add the current position to the list
				addMoveToEveryMoveBag(everyMoveBag, moveTo);  // add the current position + the value of the dice to the list 
			}
		}
	}
}

void addMoveMultipleDice(EveryMoveBag* everyMoveBag, Board* board, Player* currentPlayer, int currentPosition, int collectCapturingMoves) {
	int directionOfMoves = getDirectionOfMoves(currentPlayer);
	for (int j = 2; j <= board->diceBag->numberOfElements; j++) {
		int pom = 0;
		for (int k = 0; k < j; k++) {
			pom += board->diceBag->numbers[k];
		}

		int moveFrom = currentPosition;
		int moveTo = currentPosition + pom * directionOfMoves;
		if (isMoveInsideBoard(moveFrom, moveTo) == 1 && canMoveToField(board, currentPlayer, moveFrom, moveTo) == 1) {
			if (canCapturePawn(board, currentPlayer, moveFrom, moveTo) == collectCapturingMoves) { // if the move is a capturing move and we want to collect only capturing moves
				addMoveToEveryMoveBag(everyMoveBag, moveFrom);                               // add the current position to the list
				addMoveToEveryMoveBag(everyMoveBag, moveTo);                        // add the current position + the value of the dice to the list 
			} 
		}
	}
}

void collectMoves(EveryMoveBag* everyMoveBag, Board* board, Player* currentPlayer, int directionOfMoves, int collectCapturingMoves) { // if last arguement 1 then collect only capturing moves, otherwise collect only non capturing moves
	for (int i = 0; i < amountOfFields; i++) {
		if (isOwnerOfField(board, currentPlayer, i + 1) == 1) {
			int currentPosition = i + 1;
			addMoveOneDice(everyMoveBag, board, currentPlayer, currentPosition, collectCapturingMoves);
			addMoveMultipleDice(everyMoveBag, board, currentPlayer, currentPosition, collectCapturingMoves);
		}
	}
}



void genEveryMove(EveryMoveBag* everyMoveBag, Board* board, Player* currentPlayer) {
	int directionOfMoves = 0;
	if (currentPlayer->id == 1) {
		directionOfMoves = directionOfMovementWhite;
	}
	else if (currentPlayer->id == 0) {
		directionOfMoves = directionOfMovementRed;
	}
	
	collectMoves(everyMoveBag, board, currentPlayer, directionOfMoves, 1); // only get capturing moves first
	if(everyMoveBag->numberOfElements == 0) { // if there are no capturing moves
		collectMoves(everyMoveBag, board, currentPlayer, directionOfMoves, 0); // just collect move that fit the rest of criteria
	}
	else {
		int courtPosition = getPositionOfCourt(currentPlayer);
		int currentClosestToCourt = everyMoveBag->numbers[1];
		int currentClosestToCourtIndex = 1;
		for (int i = 1; i < everyMoveBag->numberOfElements; i+=2) {
			if(abs(courtPosition - everyMoveBag->numbers[i]) < abs(courtPosition - currentClosestToCourt)) {
				currentClosestToCourt = everyMoveBag->numbers[i];
				currentClosestToCourtIndex = i;
			}
		}

		removeEverythingExceptTheseTwo(everyMoveBag, everyMoveBag->numbers[currentClosestToCourtIndex-1], currentClosestToCourt);
	}
}

