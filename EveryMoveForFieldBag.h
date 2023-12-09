#pragma once

#include "Board.h" // change to player if errors persist

struct EveryMoveForFieldBag
{
	int* numbers; // Pointer to the array of numbers (Numbers that were rolled)
	int numberOfElements; // Number of elements in the array
	int sizeOfArray; // Size of the array
};

void initEveryMoveForFieldBag(EveryMoveForFieldBag* everyMoveForFieldBag);
void addMoveToEveryMoveForFieldBag(EveryMoveForFieldBag* everyMoveForFieldBag, int fieldNumber);
void handlePopBack(EveryMoveForFieldBag* everyMoveForFieldBag);
void handlePopFront(EveryMoveForFieldBag* everyMoveForFieldBag);
void emptyEveryMoveForFieldBag(EveryMoveForFieldBag* everyMoveForFieldBag);
void handleShowEveryMoveForFieldBag(EveryMoveForFieldBag* everyMoveForFieldBag);
void genEveryMoveForFieldBag(EveryMoveForFieldBag* everyMoveForFieldBag, Board* board, Player* currentPlayer, int fieldNumber);