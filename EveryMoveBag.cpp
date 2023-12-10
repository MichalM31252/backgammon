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

		if (i % 2 == 0) {
			cout << " |";
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
		if (isMoveInsideBoard(moveFrom, moveTo) == 1 && canMoveToField(board, currentPlayer, moveFrom, moveTo) == 1) {
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
		if (isMoveInsideBoard(moveFrom, moveTo) == 1 && canMoveToField(board, currentPlayer, moveFrom, moveTo) == 1) {
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
}