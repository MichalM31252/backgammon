#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdio.h>
#include"conio2.h"
#include "Pawn.h"

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

bool decideIfBorderShouldBePrinted(int i, int j, int startingY, int startingX, int* countToEndOfField) {
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
		*countToEndOfField = 1;
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

void printPartOfTheQuarter(int i, int j, int startingY, int startingX, int* countToEndOfField) {
	if (decideIfCornerShouldBePrinted(i, j, startingY, startingX, countToEndOfField)) {
		return;
	}
	if (decideIfBorderShouldBePrinted(i, j, startingY, startingX, countToEndOfField)) {
		return;
	}
	if (decideIfCounterSymbolShouldBePrinted(i, j, startingY, startingX, countToEndOfField)) {
		return;
	}
	gotoxy(j + startingX - 1, i + startingY - 1);
	cputs(space);
}

void printQuarterField(int startingY, int startingX) {
	for (int i = 1; i <= quarterHeight; i++) {
		int countToEndOfField = 1;
		for (int j = 1; j <= quarterWidth; j++) {
			printPartOfTheQuarter(i, j, startingY, startingX, &countToEndOfField);
			countToEndOfField++;
		}
	}
}

void handlePrint() {
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

	do {
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

		printQuarterField(2, 1);
		printQuarterField(2 + quarterHeight + 1, 1);
		printQuarterField(2, 1 + quarterWidth + 1);
		printQuarterField(2 + quarterHeight + 1, 1 + quarterWidth + 1);

		printFieldNumbersBottom();


		// print out the code of the last key pressed
		//if (zero) sprintf(txt, "key code: 0x00 0x%02x", zn);
		//else sprintf(txt, "key code: 0x%02x", zn);
		//gotoxy(48, 5);
		//cputs(txt);

		// we draw a star
		gotoxy(x, y);
		textcolor(attr);
		textbackground(back);
		// putch prints one character and moves the cursor to the right
		/*putch('*');*/

		// we wait for key press and get its code
		// most key codes correspond to the characters, like
		// a is 'a', 2 is '2', + is '+', but some special keys
		// like cursors provide two characters, where the first
		// one is zero, e.g., "up arrow" is zero and 'H'
		zero = 0;
		zn = getch();
		// we do not want the key 'H' to play role of "up arrow"
		// so we check if the first code is zero
		if (zn == 0) {
			zero = 1;		// if this is the case then we read
			zn = getch();		// the next code knowing that this
			if (zn == 0x48) y--;	// will be a special key
			else if (zn == 0x50) y++;
			else if (zn == 0x4b) x--;
			else if (zn == 0x4d) x++;
		}
		else if (zn == ' ') attr = (attr + 1) % 16;
		else if (zn == 0x0d) back = (back + 1) % 16;	// enter key is 0x0d or '\r'
	} while (zn != 'q');

	_setcursortype(_NORMALCURSOR);	// show the cursor so it will be
	// visible after the program ends
	return;
}