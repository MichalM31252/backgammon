#pragma once

// change to player if errors persist

struct EveryMoveBag
{
	int* numbers; // Pointer to the array of numbers (Numbers that were rolled)
	int numberOfElements; // Number of elements in the array
	int sizeOfArray; // Size of the array
};

void initEveryMoveBag(EveryMoveBag* everyMoveBag);
void addMoveToEveryMoveBag(EveryMoveBag* everyMoveBag, int fieldNumber);
void removeEverythingExceptTheseTwo(EveryMoveBag* everyMoveBag, int moveFrom, int moveTo);
void handlePopFrontEveryMove(EveryMoveBag* everyMoveBag);
void handlePopBack(EveryMoveBag* EveryMoveBag);
void emptyEveryMoveBag(EveryMoveBag* everyMoveBag);
void handleShowEveryMoveBag(EveryMoveBag* everyMoveBag);