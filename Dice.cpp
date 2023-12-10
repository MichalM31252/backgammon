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
	DiceBag->numbers[DiceBag->numberOfElements] = number; // the next elements are after the first one
	DiceBag->numberOfElements++; // increase the number of elements
}

int handlePopBack(DiceBag* DiceBag) // in case the user uses the first dice
{
	int temp = DiceBag->numbers[DiceBag->numberOfElements - 1]; // the last element is the one that will be popped
	assert(DiceBag->numberOfElements > 0);
	DiceBag->numberOfElements--;
	return temp; // return the popped element
}

int handlePopFront(DiceBag* DiceBag) // in case the user uses the second dice
{
	assert(DiceBag->numberOfElements > 0);
	int temp = DiceBag->numbers[0];
	for (size_t i = 0; i < DiceBag->numberOfElements - 1; i++)
	{
		DiceBag->numbers[i] = DiceBag->numbers[i + 1];
	}
	DiceBag->numberOfElements--;
	return temp; // return the popped element
}

void emptyDiceBag(DiceBag* DiceBag) // this function is used to free the memory allocated for the vector
{
	delete[] DiceBag->numbers; // delete[] only deletes the pointer

	delete[] DiceBag->player; // NOT SURE IF THIS IS NEEDED
}

void handleShowDiceBag(DiceBag* DiceBag) // this function is used to print the elements of the vector
{
	for (int i = 0; i < DiceBag->numberOfElements; i++) // prints the elements of the vector
	{
		cout << " " << DiceBag->numbers[i]; // prints the elements of the vector
	}
	cout << endl;
}

void handleRoll(DiceBag* DiceBag, Player* player) // this function is used to roll the dice
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

	DiceBag->player = player;

	// handleShowDiceBag(DiceBag); // prints the elements of the vector
}

Player* getPlayerWhichGoesFirst(Player* red, Player* white) {

	int firstDice = rand() % maximumNumberDiceCanRoll + 1; // generates a random number between 1 and 6
	int secondDice = rand() % maximumNumberDiceCanRoll + 1; // generates a random number between 1 and 6

	if (firstDice > secondDice) {
		return red;
	}
	if (firstDice < secondDice) {
		return white;
	}
	if (firstDice == secondDice) {
		return getPlayerWhichGoesFirst(red, white);
	}
}

int getDiceBagSum(DiceBag* DiceBag) {
	int sum = 0;
	for (int i = 0; i < DiceBag->numberOfElements; i++) // prints the elements of the vector
	{
		sum += DiceBag->numbers[i];
	}
	return sum;
}

void removeDices() {

}