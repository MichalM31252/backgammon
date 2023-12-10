#pragma once

#include "Board.h" // change to player if errors persist

struct EveryMoveBag
{
	int* numbers; // Pointer to the array of numbers (Numbers that were rolled)
	int numberOfElements; // Number of elements in the array
	int sizeOfArray; // Size of the array
};

void initEveryMoveBag(EveryMoveBag* everyMoveBag);
void addMoveToEveryMoveBag(EveryMoveBag* everyMoveBag, int fieldNumber);
void handlePopFront(EveryMoveBag* everyMoveBag);
void emptyEveryMoveBag(EveryMoveBag* everyMoveBag);
void handleShowEveryMoveBag(EveryMoveBag* everyMoveBag);
void genEveryMove(EveryMoveBag* everyMoveBag, Board* board, Player* currentPlayer);