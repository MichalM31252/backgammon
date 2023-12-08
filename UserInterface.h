#pragma once

// Reading input from the user and printing output to the user

#include "Board.h";

void printFieldNumbersTop();
void printFieldNumbersBottom();
bool decideIfCornerShouldBePrinted(int i, int j, int startingY, int startingX, int* countToEndOfField);
bool decideIfBorderShouldBePrinted(int i, int j, int startingY, int startingX, int* countToEndOfField, int* currentField, int monotonicity);
bool decideIfCounterSymbolShouldBePrinted(int i, int j, int startingY, int startingX, int* countToEndOfField);
void printPartOfTheQuarter(int i, int j, int startingY, int startingX, int* countToEndOfField, Board* board, int* currentField, int monotonocity);
void printQuarterField(int startingY, int startingX, Board* board, int* currentField, int monotonocity);
void handlePrint(Board *board, Player* currentPlayer);
void printTheSymbolForPawn(int i, int j, int startingY, int startingX, int* countToEndOfField, Board* board, int* currentField, const char* const symbol);
int getNumberOfPawnsOnBar(Board* board, int playerId);
void printBarStatus(Board* board);
void printCourtStatus(Board* board);
void printMenu(Board* board);