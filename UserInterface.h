#pragma once

// Reading input from the user and printing output to the user

#include "Board.h";

void printFieldNumbersTop();
void printFieldNumbersBottom();
bool decideIfCornerShouldBePrinted(int i, int j, int startingY, int startingX, int* countToEndOfField);
bool decideIfBorderShouldBePrinted(int i, int j, int startingY, int startingX, int* countToEndOfField);
bool decideIfCounterSymbolShouldBePrinted(int i, int j, int startingY, int startingX, int* countToEndOfField);
void printPartOfTheQuarter(int i, int j, int startingY, int startingX, int* countToEndOfField, Board* board, int startingField);
void printQuarterField(int startingY, int startingX, Board* board, int startingField);
void handlePrint(Board *board);