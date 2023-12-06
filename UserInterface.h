#pragma once

// Reading input from the user and printing output to the user

void printFieldNumbersTop();
void printFieldNumbersBottom();
bool decideIfCornerShouldBePrinted(int i, int j, int startingY, int startingX, int* countToEndOfField);
bool decideIfBorderShouldBePrinted(int i, int j, int startingY, int startingX, int* countToEndOfField);
bool decideIfCounterSymbolShouldBePrinted(int i, int j, int startingY, int startingX, int* countToEndOfField);
void printPartOfTheQuarter(int i, int j, int startingY, int startingX, int* countToEndOfField);
void printQuarterField(int startingY, int startingX);
void handlePrint();
