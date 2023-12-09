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

int canMoveToField(Board* board, Player* currentPlayer, int fieldNumber) {
	if (board->fields[fieldNumber - 1]->numberOfPawns == 0) {
		return 1; // can place the pawn since its empty
	}
	if (board->fields[fieldNumber - 1]->numberOfPawns > 0) {
		if (isOwnerOfField(board, currentPlayer, fieldNumber) == 1) { // if there are multiple pawns of the current player we can place the pawn
			return 1;
		}
		if (isOwnerOfField(board, currentPlayer, fieldNumber) == 0) { // if not owner of the field
			if (board->fields[fieldNumber - 1]->numberOfPawns == 1) {
				return 1; // REMEMBER TO CAPTURE PAWN
			}
			if (board->fields[fieldNumber - 1]->numberOfPawns > 1) {
				return 0;
			}
		}
	}
}


int isMoveInsideBoard(int moveFrom, int moveTo){
	if (moveTo > 0 || moveTo < amountOfFields + 1) {
		return 1;
	}
	if (moveFrom > 0 || moveFrom < amountOfFields + 1) {
		return 1;
	}
	return 0;
}

int isMoveToCourt(int moveFrom, int moveTo) {
	if (moveTo == courtPositionRed || moveTo == courtPositionWhite) {
		return 1;
	}
	return 0;
}

int isMovePossibleUsingDicebag(Board* board, int moveFrom, int moveTo) {
	// get the array of every possible move and check if current move is in the array
	// if yes return 1	
	// if no return 0

	return 1; // FIX THIS
}

int isMoveInsideBoardValid(Board* board, Player* currentPlayer, int moveFrom, int moveTo) {
	if (isOwnerOfField(board, currentPlayer, moveFrom) == 0) { // checks if the field we want to move from belongs to the current player
		return 0;
	}
	if (isMoveInsideBoard(moveFrom, moveTo) == 0) { // checks if the move is inside the board
		return 0;
	}
	if (canMoveToField(board, currentPlayer, moveTo) == 0) { // checks if we can move to the field
		return 0;
	}
	if (isMovePossibleUsingDicebag(board, moveFrom, moveTo) == 0) { // checks if the move is possible using the dicebag
		return 0;
	}
	return 1;
}

int isMoveValid(Board* board, Player* currentPlayer, int moveFrom, int moveTo) {
	// different function for movint to court 
	// different function for moving from field to field

	if (isMoveInsideBoardValid(board, currentPlayer, moveFrom, moveTo) == 1) { // for moving inside the board (ONLY FIELDS)
		return 1;
	}
	return 0;

	// else 
	// check if move is to court

}

void getEveryValidMove(Board* board, Player* currentPlayer) {
	// for every field
	//    check if currentPlayer == ownerOfTheField
	//      if yes
	//        for every dice in the dice bag
	//          moveOneDice
	//            currentPosition + valueOfDice1
	//            currentPosition + valueOfDice2
	//            currentPosition + valueOfDice3
	//            currentPosition + valueOfDice4
	//          moveMultipleDice
	// 
	//            for (int i = 2; i <= amountInitializedDice; i++)
	//              int pom = 0;
	//              for (int j = 0; j < i; j++)
	//                pom += valueOfDice[j];
	//              cout << pom << endl;
	//
	//            2: 1 2
	//            3: 3 3 3 <- its impossible to have 3 dices, only 2 or 4
	//            4: 4 4 4 4
	//
	//             so the problem is 
	//                it will show 
	//                  1 2
	//                  1 2 3
	//
	//                but it wont show
	//                  1 3 or 2 3
    // 
	//               NO THIS IS CORRECT
	//               IF THERE ARE MORE THAN 2 DICE
	//               THEN JUST ADD THE SAME VALUE THE SCENARIO 1 3 and 2 3 WILL NEVER HAPPEN SINCE 
	//               THE DICE CAN ONLY DO X X X X PAST 2 DICES

	// EVERY TIME THERE IS A MOVE YOU NEED TO CALCULATE EVERY POSSIBLE MOVE TO CHECK FOR FORCED BEATING 
	// IF THERE IS A BEATING POSSIBLE YOU CANT DO ANYTHING ELSE
	// IF THERE ARE MULTIPLE BEATINGS GET THE ONE THAT WILL MOVE THE PAWN THE FURTHEST

	// THE ONLY WAY TO GET EVERY POSSIBLE MOVE IS TO MAKE AN ARRAY THAT WILL STORE THEM
	// IF YOU FIND ONE BEATING YOU NEED TO CLEAR THE ARRAY AND ADD THE BEATING MOVE
	// AFTER THAT YOU CAN ONLY ADD THE BEATING MOVES
	// AFTER YOU HAVE ONLY BEATING MOVES YOU NEED TO REMOVE EVERY MOVE EXCEPT THE FURTHEST ONE

}

void movePawn(Board* board, Player* player, int moveFrom, int moveTo) {
	
}