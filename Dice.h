#pragma once

// Everything related to the dice


struct DiceBag
{
	int* numbers; // Pointer to the array of numbers (Numbers that were rolled)
	int numberOfElements; // Number of elements in the array
	int sizeOfArray; // Size of the array
};

void initDiceBag(DiceBag* DiceBag); // this function is used to initialize the Dice Bag
void addNumberToDiceBag(DiceBag* DiceBag, int number); // this function is used to add a number to the Dice Bag
void handlePopBack(DiceBag* DiceBag); // in case the user uses the first dice
void handlePopFront(DiceBag* DiceBag); // in case the user uses the second dice
void emptyDiceBag(DiceBag* DiceBag); // this function is used to free the memory allocated for the vector
void handleShow(DiceBag* DiceBag); // this function is used to print the elements of the vector
void handleRoll(DiceBag* DiceBag); // this function is used to roll the dice