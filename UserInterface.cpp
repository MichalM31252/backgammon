#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdio.h>
#include"conio2.h"

#include "Pawn.h"
#include "Board.h"

#include "Constants.h"

using namespace std;

// Reading input from the user and printing output to the user



void printFieldNumbersTop() {
	int currentFieldNumberAddition = 1;
	int countUntillNextNumber = 0;
	for (int i = 3; i < boardWidth - 1; i++) {
		char s[4];
		int currentFieldNumber = amountOfFields / 2 + currentFieldNumberAddition;

		if (i == (boardWidth - 1) / 2) {
			countUntillNextNumber++;
		}

		if (countUntillNextNumber == 0) {
			sprintf(s, "%ld", currentFieldNumber);
			gotoxy(i, startingX);
			cputs(s);
			currentFieldNumberAddition++;
			countUntillNextNumber = 4;
		}
		countUntillNextNumber--;

	}
}

void printFieldNumbersBottom() {
	int currentFieldNumberAddition = -1;
	int countUntillNextNumber = 0;
	for (int i = 3; i < boardWidth - 1; i++) {
		char s[4];
		int currentFieldNumber = amountOfFields / 2 + 1 + currentFieldNumberAddition;

		if (i == (boardWidth - 1) / 2) {
			countUntillNextNumber++;
		}

		if (countUntillNextNumber == 0) {
			if (currentFieldNumber < 10) {
				sprintf(s, " %ld", currentFieldNumber);
			}
			else {
				sprintf(s, "%ld", currentFieldNumber);
			}
			gotoxy(i, boardHeight);
			cputs(s);
			currentFieldNumberAddition--;
			countUntillNextNumber = 4;
		}
		countUntillNextNumber--;

	}
}

bool decideIfCornerShouldBePrinted(int i, int j, int startingY, int startingX, int* countToEndOfField) {
	if ((i == 1 && j == 1) || (i == quarterHeight && j == 1) || (i == 1 && j == quarterWidth) || (i == quarterHeight && j == quarterWidth)) {
		gotoxy(j + startingX - 1, i + startingY - 1);
		cputs(cornerSymbol);
		return true;
	}
	return false;
}

bool decideIfBorderShouldBePrinted(int i, int j, int startingY, int startingX, int* countToEndOfField, int* currentField, int monotonicity) { // i is for the row, j is for the column
	if (i == 1 || i == quarterHeight) {
		gotoxy(j + startingX - 1, i + startingY - 1);
		cputs(topAndBottomBorderSymbol);
		return true;
	}
	if (j == 1 || j == quarterWidth) {
		gotoxy(j + startingX - 1, i + startingY - 1);
		cputs(leftAndRightBorderSymbol);
		return true;
	}
	if (*countToEndOfField == fieldWidth && (i > 1 && i < quarterHeight)) {
		gotoxy(j + startingX - 1, i + startingY - 1);
		cputs(leftAndRightBorderSymbol);
		if (i == fieldHeight - margin/2 ) {
			*countToEndOfField = 1;
			*currentField += monotonicity;
		}
		return true;
	}
	return false;
}

bool decideIfCounterSymbolShouldBePrinted(int i, int j, int startingY, int startingX, int* countToEndOfField) {
	if (i == fieldHeight - margin) {
		if (*countToEndOfField == 2) {
			gotoxy(j + startingX - 1, i + startingY - 1);
			cputs(leftCounterSymbol);
			return true;
		}
		if (*countToEndOfField == 4) {
			gotoxy(j + startingX - 1, i + startingY - 1);
			cputs(rightCounterSymbol);
			return true;
		}
	}
	return false;
}

bool decideIfPawnShouldBePrinted(int i, int j, int startingY, int startingX, int* countToEndOfField, Board* board, int *currentField) {
	if (*countToEndOfField == fieldWidth / 2 + 1) { // check if we are currently in the middle of the field
		if (i > margin && i < fieldHeight - margin) { // check if we are in a place where we can place checkers
			if (board->fields[*currentField - 1]->numberOfPawns >= i - margin) { // check if there are any checkers in the field
				gotoxy(j + startingX - 1, i + startingY - 1);
				cputs(pawnSymbol);
				return true;
			}
		}
	}
	return false;
}

void printPartOfTheQuarter(int i, int j, int startingY, int startingX, int* countToEndOfField, Board* board, int *currentField, int monotonocity) {
	if (decideIfCornerShouldBePrinted(i, j, startingY, startingX, countToEndOfField)) {
		return;
	}
	if (decideIfBorderShouldBePrinted(i, j, startingY, startingX, countToEndOfField, currentField, monotonocity)) {
		return;
	}
	if (decideIfCounterSymbolShouldBePrinted(i, j, startingY, startingX, countToEndOfField)) {
		return;
	}
	if (decideIfPawnShouldBePrinted(i, j, startingY, startingX, countToEndOfField, board, currentField)) {
		return;
	}
	gotoxy(j + startingX - 1, i + startingY - 1);
	cputs(space);
}

void printQuarterField(int startingY, int startingX, Board* board, int *currentField, int monotonocity) {
	// inside these loops I could overwrite previous characters with user data
	int countToEndOfField = 1;
	for (int j = 1; j <= quarterWidth; j++ ) { // j is for the column
		for (int i = 1; i <= quarterHeight; i++) { // i is for the row
			printPartOfTheQuarter(i, j, startingY, startingX, &countToEndOfField, board, currentField, monotonocity);
			// it should be around here
		}
		countToEndOfField++;
	}
}

void handlePrint(Board* board) {
	int zn = 0, x = 40, y = 12, attr = 7, back = 0, zero = 0;
	char txt[32];

	// if the program is compiled in pure C, then we need to initialize
	// the library ourselves; __cplusplus is defined only if a C++ compiler
	// is used

	#ifndef __cplusplus
		Conio2_Init();
	#endif

	settitle("First name, Last Name, Student number"); // settitle sets the window title

	_setcursortype(_NOCURSOR); // hide the blinking cursor

	textbackground(BLACK);
	clrscr(); // clear the screen : we fill it out with spaces with 
	textcolor(7); // we set the text color (7 == LIGHTGRAY)

	// we move the coursor to column 48 and row 1
	// rows and column are numbered starting with 1
	gotoxy(48, 1);
	// we print out a text at a given cursor position
	// the cursor will move by the length of the text

		//printFieldNumbers(1);
	printFieldNumbersTop();

	// Upper left quarter
	int currentField = 13;
	int monotonicity = 1;
	printQuarterField(2, 1, board, &currentField, monotonicity);

	// Lower left quarter
	currentField = 12;
	monotonicity = -1;
	printQuarterField(2 + quarterHeight + 1, 1, board, &currentField, monotonicity);
	
	// Upper right quarter
	currentField = 19;
	monotonicity = 1;
	printQuarterField(2, 1 + quarterWidth + 1, board, &currentField, monotonicity);
	
	// Lower right quarter
	currentField = 6;
	monotonicity = -1;
	printQuarterField(2 + quarterHeight + 1, 1 + quarterWidth + 1, board, &currentField, monotonicity);

	printFieldNumbersBottom();

	// visible after the program ends
	return;
}