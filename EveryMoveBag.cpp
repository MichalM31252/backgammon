#include <iostream>
#include "assert.h"

#include "EveryMoveBag.h"
#include "Board.h"
#include "Constants.h"


using namespace std;

void initEveryMoveBag(EveryMoveBag* EveryMoveBag) // this function is used to initialize the Dice Bag
{
	EveryMoveBag->numbers = new int[1]; // this is used to allocate memory
	EveryMoveBag->numberOfElements = 0; // number of elements currently inside
	EveryMoveBag->sizeOfArray = 1;    // starting size
}

void addMoveToEveryMoveBag(EveryMoveBag* EveryMoveBag, int fieldNumber) // this function is used to add a number
{
	if (EveryMoveBag->numberOfElements == EveryMoveBag->sizeOfArray) // if the number of elements is equal to the size of the array
	{
		int* temp = new int[EveryMoveBag->sizeOfArray * 2]; // create a temporary array with double the size of the current array

		for (int i = 0; i < EveryMoveBag->numberOfElements; i++) // copy the elements from the current array to the temporary array
		{
			temp[i] = EveryMoveBag->numbers[i];
		}

		delete[] EveryMoveBag->numbers; // delete the current array

		EveryMoveBag->numbers = temp; // set the current array to the temporary array

		EveryMoveBag->sizeOfArray *= 2; // double the size of the array
	}
	EveryMoveBag->numbers[EveryMoveBag->numberOfElements] = fieldNumber; // the next elements are after the first one
	EveryMoveBag->numberOfElements++; // increase the number of elements
}

void handlePopFront(EveryMoveBag* EveryMoveBag) // in case the user uses the second dice
{
	assert(EveryMoveBag->numberOfElements > 0);
	for (size_t i = 0; i < EveryMoveBag->numberOfElements - 1; i++)
	{
		EveryMoveBag->numbers[i] = EveryMoveBag->numbers[i + 1];
	}
	EveryMoveBag->numberOfElements--;
}

void emptyEveryMoveBag(EveryMoveBag* EveryMoveBag) // this function is used to free the memory allocated for the vector
{
	delete[] EveryMoveBag->numbers; // delete[] only deletes the pointer
}

void handleShowEveryMoveBag(EveryMoveBag* EveryMoveBag) // this function is used to print the elements of the vector
{
	for (int i = 0; i < EveryMoveBag->numberOfElements; i++) // prints the elements of the vector
	{
		if (i % 10 == 0) {
			cout << endl;
		}
		cout << " " << EveryMoveBag->numbers[i]; // prints the elements of the vector
	}
	cout << endl;
}

void addEveryMoveOneDice(EveryMoveBag* everyMoveBag, Board* board, Player* currentPlayer, int currentPosition) {
	int directionOfMoves = getDirectionOfMoves(currentPlayer);
	for (int j = 0; j < board->diceBag->numberOfElements; j++) {
		int moveFrom = currentPosition;
		int moveTo = currentPosition + board->diceBag->numbers[j] * directionOfMoves;
		if (canMoveToField(board, currentPlayer, moveFrom, moveTo) == 1) {
			addMoveToEveryMoveBag(everyMoveBag, moveFrom);                               // add the current position to the list
			addMoveToEveryMoveBag(everyMoveBag, moveTo);  // add the current position + the value of the dice to the list 
		}
	}
}



void addEveryMoveMultipleDice(EveryMoveBag* everyMoveBag, Board* board, Player* currentPlayer, int currentPosition) {
	int directionOfMoves = getDirectionOfMoves(currentPlayer);
	for (int j = 2; j <= board->diceBag->numberOfElements; j++) {
		int pom = 0;
		for (int k = 0; k < j; k++) {
			pom += board->diceBag->numbers[k];
		}

		int moveFrom = currentPosition;
		int moveTo = currentPosition + pom * directionOfMoves;
		if (canMoveToField(board, currentPlayer, moveFrom, moveTo) == 1) {
			addMoveToEveryMoveBag(everyMoveBag, moveFrom);                               // add the current position to the list
			addMoveToEveryMoveBag(everyMoveBag, moveTo);                        // add the current position + the value of the dice to the list 
		}
	}
}

void genEveryMove(EveryMoveBag* everyMoveBag, Board* board, Player* currentPlayer) {
	int directionOfMoves;
	if (currentPlayer->id == 1) {
		directionOfMoves = directionOfMovementWhite;
	}
	else if (currentPlayer->id == 0) {
		directionOfMoves = directionOfMovementRed;
	}
	else {
		assert(0);
	}

	for (int i = 0; i < amountOfFields; i++) {
		if (isOwnerOfField(board, currentPlayer, i + 1) == 1) {
			int currentPosition = i + 1;
			addEveryMoveOneDice(everyMoveBag, board, currentPlayer, currentPosition);
			addEveryMoveMultipleDice(everyMoveBag, board, currentPlayer, currentPosition);
		}
	}

	// add to the list every capturing move
	// if the list is empty add every move
	// ELSE REMOVE EVERY MOVE EXCEPT THE FURTHEST ONE FROM THE CURRENT FIELD

	// for every field
	//    check if currentPlayer == ownerOfTheField
	//      if yes
	//        for every dice in the dice bag
	//          moveOneDice
	//            currentPosition + valueOfDice1
	//            currentPosition + valueOfDice2
	//            currentPosition + valueOfDice3
	//            currentPosition + valueOfDice4
	// 
	//          moveMultipleDice
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
	// FIRST ONLY ADD ONLY CAPTURING MOVES

}