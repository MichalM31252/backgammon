#include <iostream>
#include "assert.h"

#include "EveryMoveForFieldBag.h"
#include "Constants.h"


using namespace std;

void initEveryMoveForFieldBag(EveryMoveForFieldBag* everyMoveForFieldBag) // this function is used to initialize the Dice Bag
{
	everyMoveForFieldBag->numbers = new int[1]; // this is used to allocate memory
	everyMoveForFieldBag->numberOfElements = 0; // number of elements currently inside
	everyMoveForFieldBag->sizeOfArray = 1;    // starting size
}

void addMoveToEveryMoveForFieldBag(EveryMoveForFieldBag* everyMoveForFieldBag, int fieldNumber) // this function is used to add a number
{
	if (everyMoveForFieldBag->numberOfElements == everyMoveForFieldBag->sizeOfArray) // if the number of elements is equal to the size of the array
	{
		int* temp = new int[everyMoveForFieldBag->sizeOfArray * 2]; // create a temporary array with double the size of the current array

		for (int i = 0; i < everyMoveForFieldBag->numberOfElements; i++) // copy the elements from the current array to the temporary array
		{
			temp[i] = everyMoveForFieldBag->numbers[i];
		}

		delete[] everyMoveForFieldBag->numbers; // delete the current array

		everyMoveForFieldBag->numbers = temp; // set the current array to the temporary array

		everyMoveForFieldBag->sizeOfArray *= 2; // double the size of the array
	}
	everyMoveForFieldBag->numbers[everyMoveForFieldBag->numberOfElements] = fieldNumber; // the next elements are after the first one
	everyMoveForFieldBag->numberOfElements++; // increase the number of elements
}

void handlePopBack(EveryMoveForFieldBag* everyMoveForFieldBag) // in case the user uses the first dice
{
	assert(everyMoveForFieldBag->numberOfElements > 0);
	everyMoveForFieldBag->numberOfElements--;
}

void handlePopFront(EveryMoveForFieldBag* everyMoveForFieldBag) // in case the user uses the second dice
{
	assert(everyMoveForFieldBag->numberOfElements > 0);
	for (size_t i = 0; i < everyMoveForFieldBag->numberOfElements - 1; i++)
	{
		everyMoveForFieldBag->numbers[i] = everyMoveForFieldBag->numbers[i + 1];
	}
	everyMoveForFieldBag->numberOfElements--;
}

void emptyEveryMoveForFieldBag(EveryMoveForFieldBag* everyMoveForFieldBag) // this function is used to free the memory allocated for the vector
{
	delete[] everyMoveForFieldBag->numbers; // delete[] only deletes the pointer
}

void handleShowEveryMoveForFieldBag(EveryMoveForFieldBag* everyMoveForFieldBag) // this function is used to print the elements of the vector
{
	for (int i = 0; i < everyMoveForFieldBag->numberOfElements; i++) // prints the elements of the vector
	{
		cout << " " << everyMoveForFieldBag->numbers[i]; // prints the elements of the vector
	}
	cout << endl;
}

void genEveryMoveForFieldBag(EveryMoveForFieldBag* everyMoveForFieldBag, Board* board, Player* currentPlayer, int fieldNumber) {
	int directionOfMoves;
	if (currentPlayer->id == 0) {
		directionOfMoves = directionOfMovementRed;
	}
	if (currentPlayer->id == 1) {
		directionOfMoves = directionOfMovementWhite;
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
	// FIRST ONLY ADD ONLY CAPTURING MOVES

}