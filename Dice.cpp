#include <iostream>
#include "assert.h"

#include "Dice.h"
#include "Constants.h"

using namespace std;

// Everything related to the dice

void initDiceBag(DiceBag* DiceBag, Player* player) // this function is used to initialize the Dice Bag
{
	DiceBag->numbers = new int[1]; // this is used to allocate memory for the Dice Bag
	DiceBag->numberOfElements = 0; // number of elements currently inside the Dice Bag
	DiceBag->sizeOfArray = 1;    // starting size of the Dice Bag
	DiceBag->player = player;
}

void addNumberToDiceBag(DiceBag* DiceBag, int number) // this function is used to add a number to the Dice Bag
{
	if (DiceBag->numberOfElements == DiceBag->sizeOfArray) // if the number of elements is equal to the size of the array
	{
		int* temp = new int[DiceBag->sizeOfArray * 2]; // create a temporary array with double the size of the current array

		for (int i = 0; i < DiceBag->numberOfElements; i++) // copy the elements from the current array to the temporary array
		{
			temp[i] = DiceBag->numbers[i];
		}

		delete[] DiceBag->numbers; // delete the current array

		DiceBag->numbers = temp; // set the current array to the temporary array

		DiceBag->sizeOfArray *= 2; // double the size of the array
	}

	DiceBag->numbers[DiceBag->numberOfElements] = number; // WHY THIS LINE DOESNT ADD THE SECOND ELEMENT
	DiceBag->numberOfElements++; // increase the number of elements
}

void handlePopBack(DiceBag* DiceBag) // in case the user uses the first dice
{
	assert(DiceBag->numberOfElements > 0);
	DiceBag->numberOfElements--;
}

void handlePopFront(DiceBag* DiceBag) // in case the user uses the second dice
{
	assert(DiceBag->numberOfElements > 0);
	for (size_t i = 0; i < DiceBag->numberOfElements - 1; i++)
	{
		DiceBag->numbers[i] = DiceBag->numbers[i + 1];
	}
	DiceBag->numberOfElements--;
}

void emptyDiceBag(DiceBag* DiceBag) // this function is used to free the memory allocated for the vector
{
	delete[] DiceBag->numbers; // delete[] only deletes the pointer
}

void handleShowDiceBag(DiceBag* DiceBag) // this function is used to print the elements of the vector
{
	for (int i = 0; i < DiceBag->numberOfElements; i++) // prints the elements of the vector
	{
		cout << " " << DiceBag->numbers[i]; // prints the elements of the vector
	}
	cout << endl;
}

void handleRoll(DiceBag* DiceBag) // this function is used to roll the dice
{
	int firstDice = rand() % 6 + 1; // generates a random number between 1 and 6
	int secondDice = rand() % 6 + 1; // generates a random number between 1 and 6

	if (firstDice == secondDice) // if the first dice is equal to the second dice
	{ 
		addNumberToDiceBag(DiceBag, firstDice); // adds the first dice to the Dice Bag
		addNumberToDiceBag(DiceBag, firstDice); // adds the first dice to the Dice Bag
		addNumberToDiceBag(DiceBag, firstDice); // adds the first dice to the Dice Bag
		addNumberToDiceBag(DiceBag, firstDice); // adds the first dice to the Dice Bag
	}
	else {
		addNumberToDiceBag(DiceBag, firstDice); // adds the first dice to the Dice Bag
		addNumberToDiceBag(DiceBag, secondDice); // adds the second dice to the Dice Bag
	}

	handleShowDiceBag(DiceBag); // prints the elements of the vector
}

int decideWhichPlayerGoesFirst() {

	int firstDice = rand() % maximumNumberDiceCanRoll + 1; // generates a random number between 1 and 6
	int secondDice = rand() % maximumNumberDiceCanRoll + 1; // generates a random number between 1 and 6

	cout << "First player (Red) rolled: " << firstDice << endl;
	cout << "Second player (White) rolled: " << secondDice << endl;

	if (firstDice > secondDice) {
		cout << "Red goes first!" << endl;
		return idOfPlayerRed;
	}
	if (firstDice < secondDice) {
		cout << "White goes first!" << endl;
		return idOfPlayerWhite;
	}
	if (firstDice == secondDice) {
		cout << "Same result was rolled! Program will throw the dice again to decide who goes first" << endl;
		return decideWhichPlayerGoesFirst();
	}
	return -1;
}