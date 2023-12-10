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

//////////////// Removing pawns to court functionality

int getNumberOfPawnsInBase(Board* board, Player* currentPlayer) { // returns the number of pawns in the base
	int numberOfPawnsInBase = 0;
	int directionOfMoves = getDirectionOfMoves(currentPlayer);
	int positionOfCourt = getPositionOfCourt(currentPlayer);

	if (positionOfCourt == 0) {
		for (int i = 1; i <= 6; i++) {
			if (isOwnerOfField(board, currentPlayer, i) == 1) {
				numberOfPawnsInBase += board->fields[i - 1]->numberOfPawns;
			}
		}
	}
	if (positionOfCourt == 25) {
		for (int i = 19; i <= 24; i++) {
			if (isOwnerOfField(board, currentPlayer, i) == 1) {
				numberOfPawnsInBase += board->fields[i - 1]->numberOfPawns;
			}
		}
	}
	return numberOfPawnsInBase;
}

void addPawnToCourt(Board* board, Player* currentPlayer, int moveFrom) { // moves the pawn from the field to court
	board->court[currentPlayer->id]->numberOfPawns++;
}

int canStartRemovingPawns(Board* board, Player* currentPlayer) { // checks if it is possible to start removing pawns from the board
	int numberOfPawnsInBase = getNumberOfPawnsInBase(board, currentPlayer);
	if (board->court[currentPlayer->id]->numberOfPawns + numberOfPawnsInBase == amountOfPawnsForAPlayer) {
		return 1;
	}
	return 0;
}

///////////////////

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

int canCapturePawn(Board* board, Player* currentPlayer, int moveFrom, int moveTo) { // THIS SHOULD NOT HAPPEND WHEN YOU ARE MOVING A PAWN TO A COURT
	if (board->fields[moveTo - 1]->numberOfPawns == 1) {         // if there is only one pawn on the field
		if (isOwnerOfField(board, currentPlayer, moveTo) == 0) { // if current player is not the owner of the field
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
	if (moveTo == courtFieldNumberRed || moveTo == courtFieldNumberWhite) {
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
		if (canStartRemovingPawns(board, currentPlayer) == 1) { // if every pawn is in the base
			if (isMoveToCourt(moveFrom, moveTo) == 1) { // if the move is to court
				return 1;
			}
		}
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

	if (isMoveInsideBoardValid(board, currentPlayer, moveFrom, moveTo, everyMoveBag) == 1) { // for moving inside the board (ONLY FIELDS)
		return 1;
	}
	if (isMoveToCourt(moveFrom, moveTo) == 1) { // for moving to court
		if ((moveTo == courtFieldNumberRed || moveTo == courtFieldNumberWhite)) {
			return 1;
		}
	}
	return 0;

	// else 
	// check if move is to court

}

void removePawn(Board* board, int fieldNumber) {
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

	removePawn(board, moveFrom);
	addPawn(board, player, moveTo);
}

/////////////

void addMoveBase(EveryMoveBag* everyMoveBag, Board* board, Player* currentPlayer, int currentPosition, int collectCapturingMoves, int moveFrom, int moveTo) {
	if (isMoveInsideBoard(moveFrom, moveTo) == 1 && canMoveToField(board, currentPlayer, moveFrom, moveTo) == 1) { // if you add here a 3rd && statement that checks if the values are the same then you will get rid of the bug that shows the same move multiple times
		if (canCapturePawn(board, currentPlayer, moveFrom, moveTo) == collectCapturingMoves) { // if the move is a capturing move and we want to collect only capturing moves
			addMoveToEveryMoveBag(everyMoveBag, moveFrom);                               // add the current position to the list
			addMoveToEveryMoveBag(everyMoveBag, moveTo);  // add the current position + the value of the dice to the list 
		}
	}
}

void addMoveOneDice(EveryMoveBag* everyMoveBag, Board* board, Player* currentPlayer, int currentPosition, int collectCapturingMoves) { // adds moves that are possible using one dice
	int directionOfMoves = getDirectionOfMoves(currentPlayer);
	for (int j = 0; j < board->diceBag->numberOfElements; j++) {
		int moveFrom = currentPosition;
		int moveTo = currentPosition + board->diceBag->numbers[j] * directionOfMoves;
		addMoveBase(everyMoveBag, board, currentPlayer, currentPosition, collectCapturingMoves, moveFrom, moveTo);
	}
}

void addMoveMultipleDice(EveryMoveBag* everyMoveBag, Board* board, Player* currentPlayer, int currentPosition, int collectCapturingMoves) { // adds moves that are possible using multiple dice
	int directionOfMoves = getDirectionOfMoves(currentPlayer);
	for (int j = 2; j <= board->diceBag->numberOfElements; j++) {
		int pom = 0;
		for (int k = 0; k < j; k++) {
			pom += board->diceBag->numbers[k];
		}
		int moveFrom = currentPosition;
		int moveTo = currentPosition + pom * directionOfMoves;
		addMoveBase(everyMoveBag, board, currentPlayer, currentPosition, collectCapturingMoves, moveFrom, moveTo);
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

void capturingMovesPresent(EveryMoveBag* everyMoveBag, Board* board, Player* currentPlayer) { // check if there are any capturing moves present, if yes then get the one that is the closest to the court
	int courtPosition = getPositionOfCourt(currentPlayer);
	int currentClosestToCourt = everyMoveBag->numbers[1];
	int currentClosestToCourtIndex = 1;
	for (int i = 1; i < everyMoveBag->numberOfElements; i += 2) {
		if (abs(courtPosition - everyMoveBag->numbers[i]) < abs(courtPosition - currentClosestToCourt)) {
			currentClosestToCourt = everyMoveBag->numbers[i];
			currentClosestToCourtIndex = i;
		}
	}
	removeEverythingExceptTheseTwo(everyMoveBag, everyMoveBag->numbers[currentClosestToCourtIndex - 1], currentClosestToCourt); // get the one that is the closest to court
}

/////////////////////////////

int addMoveBaseRemoving(EveryMoveBag* everyMoveBag, Board* board, Player* currentPlayer, int currentPosition, int courtPosition, int moveFrom, int moveTo) {
	if (moveTo == courtPosition) { // if you add here a 3rd && statement that checks if the values are the same then you will get rid of the bug that shows the same move multiple times
		addMoveToEveryMoveBag(everyMoveBag, moveFrom);                               // add the current position to the list
		addMoveToEveryMoveBag(everyMoveBag, moveTo);  // add the current position + the value of the dice to the list 
		return moveFrom;
	}
	return 0;
}


int addMoveOneDiceRemoving(EveryMoveBag* everyMoveBag, Board* board, Player* currentPlayer, int currentPosition, int courtPosition) { // adds moves that are possible using one dice
	int directionOfMoves = getDirectionOfMoves(currentPlayer);
	int temp = 0;
	for (int j = 0; j < board->diceBag->numberOfElements; j++) {
		int moveFrom = currentPosition;
		int moveTo = currentPosition + board->diceBag->numbers[j] * directionOfMoves; // To this field the dice can move the pawn
		temp = addMoveBaseRemoving(everyMoveBag, board, currentPlayer, currentPosition, courtPosition, moveFrom, moveTo); // check if we can move it to court
		if (temp != 0) {
			break;
		}
	}
	return temp; // returns the number of the field which is the furthest from the court (The move is already in the everymovebag);
}

int addMoveMultipleDiceRemoving(EveryMoveBag* everyMoveBag, Board* board, Player* currentPlayer, int currentPosition, int courtPosition) { // adds moves that are possible using multiple dice
	int directionOfMoves = getDirectionOfMoves(currentPlayer);
	int temp = 0;
	for (int j = 2; j <= board->diceBag->numberOfElements; j++) {
		int pom = 0;
		for (int k = 0; k < j; k++) {
			pom += board->diceBag->numbers[k];
		}
		int moveFrom = currentPosition;
		int moveTo = currentPosition + pom * directionOfMoves;
		temp = addMoveBaseRemoving(everyMoveBag, board, currentPlayer, currentPosition, courtPosition, moveFrom, moveTo);
		if (temp != 0) {
			break;
		}
	}
	return temp;
}

/////////////////////////////

void collectMovesForRemoving(EveryMoveBag* eMB, Board* board, Player* currentP, int directionOfMoves) { // collects moves for removing pawns from the board
	int fP = getFirPosOfBase(currentP); // first position
	int sP = getSecPosOfBase(currentP);
	int cP = getPositionOfCourt(currentP); // court position
	int dis1 = 0; // distance from court 1
	int dis2 = 0; // distance from court 2
	//  19, 20, 21, 22, 23, 24     RED BASE    DIRECTION OF MOVE IS 1
	//   6,  5,  4,  3,  2,  1     WHITE BASE  DIRECTION OF MOVE IS -1
	for (int i = fP; i != sP + 1; i += directionOfMoves) {
		if (isOwnerOfField(board, currentP, i) == 1) {
			// if cyfry po lewej wieksze to usun po prawej
			// if cyfru po prawej wieksze to usun po lewej
			dis1 = addMoveOneDiceRemoving(eMB, board, currentP, i, cP);
			dis2 = addMoveMultipleDiceRemoving(eMB, board, currentP, i, cP);
			if (dis1 > dis2) {
				removeEverythingExceptTheseTwo(eMB, i, cP);
				break;
			}
			if (dis1 < dis2) {
				removeEverythingExceptTheseTwo(eMB, i, cP);
				break;
			}
			if (dis1 == dis2 && dis1 > 0) { // scenario where both distances are the same for ex. 4, 4 and are not equal to 0 (show multiple moves)
				break;
			}
			//else if (distanceFromCourt1 == 0 && distanceFromCourt2 == 0) { the scenario where you can't move the pawn straight to the court (but you can move it closer to the court)
			//	just add normal moves to the list
			//}
		}
	}
}

void genEveryMoveDefault(EveryMoveBag* everyMoveBag, Board* board, Player* currentPlayer, int directionOfMoves) {
	collectMoves(everyMoveBag, board, currentPlayer, directionOfMoves, 1); // only get capturing moves first
	if (everyMoveBag->numberOfElements == 0) { // if there are no capturing moves
		collectMoves(everyMoveBag, board, currentPlayer, directionOfMoves, 0); // just collect move that fit the rest of criteria
	}
	else { // if there are capturing moves
		capturingMovesPresent(everyMoveBag, board, currentPlayer); // get the capturing moves that are the closest to the court
	}
}

void genEveryMove(EveryMoveBag* everyMoveBag, Board* board, Player* currentPlayer) {
	int directionOfMoves = getDirectionOfMoves(currentPlayer);

	// if every pawn in the base then start removing
	// otherwise do usual stuff

	if (canStartRemovingPawns(board, currentPlayer) == 1) { // if every pawn is in the base}
		collectMovesForRemoving(everyMoveBag, board, currentPlayer, directionOfMoves);
		// IF THE LIST HERE IS EMPTY FILL IT WITH NORMAL MOVES
		if (everyMoveBag->numberOfElements == 0) {
			genEveryMoveDefault(everyMoveBag, board, currentPlayer, directionOfMoves);
		}
	}
	else { // if not every pawn is in the base do the usual
		genEveryMoveDefault(everyMoveBag, board, currentPlayer, directionOfMoves);
	}
}



