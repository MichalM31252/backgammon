#pragma once

#include "Board.h" // change to player if errors persist

struct EveryMoveBag
{
	int* numbers; // Pointer to the array of numbers (Numbers that were rolled)
	int numberOfElements; // Number of elements in the array
	int sizeOfArray; // Size of the array
};

void initEveryMoveBag(EveryMoveBag* EveryMoveBag);
void addMoveToEveryMoveBag(EveryMoveBag* EveryMoveBag, int fieldNumber);
void handlePopBack(EveryMoveBag* EveryMoveBag);
void handlePopFront(EveryMoveBag* EveryMoveBag);
void emptyEveryMoveBag(EveryMoveBag* EveryMoveBag);
void handleShowEveryMoveBag(EveryMoveBag* EveryMoveBag);
void genEveryMoveBag(EveryMoveBag* EveryMoveBag, Board* board, Player* currentPlayer, int fieldNumber);