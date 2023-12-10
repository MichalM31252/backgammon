#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include "conio2.h"

#include "Pawn.h"
#include "Board.h"
#include "Bar.h"
#include "FileInterface.h"
#include "EveryMoveBag.h"

#include "Constants.h"

using namespace std;

// Reading input from the user and printing output to the user

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

void decideOnTheColorOfThePawn(Board* board, int* currentField) {
	if (board->fields[*currentField - 1]->player->id == idOfPlayerRed) {
		textcolor(4);
	}
	else {
		textcolor(7);
	}
}

void printTheSymbolForPawn(int i, int j, int startingY, int startingX, int* countToEndOfField, Board* board, int* currentField, const char* const symbol) {
	decideOnTheColorOfThePawn(board, currentField);
	gotoxy(j + startingX - 1, i + startingY - 1);
	cputs(symbol);
	textcolor(7);
}

void printNumberOfHiddenPawns(int i, int j, int startingY, int startingX, int* countToEndOfField, Board* board, int* currentField) {
	int theAmountOfPawnsThatWasPlaced = i - margin;
	int amountOfPawnsLeft = board->fields[*currentField - 1]->numberOfPawns - theAmountOfPawnsThatWasPlaced;
	if (amountOfPawnsLeft == 1) {
		printTheSymbolForPawn(i, j, startingY, startingX, countToEndOfField, board, currentField, pawnSymbol);
	}
	else {
		char apl[20];
		sprintf(apl, "%d", amountOfPawnsLeft + 1);
		const char* aplConstChar = apl;
		printTheSymbolForPawn(i, j, startingY, startingX, countToEndOfField, board, currentField, aplConstChar);
	}
}


bool decideIfPawnShouldBePrinted(int i, int j, int startingY, int startingX, int* countToEndOfField, Board* board, int *currentField) {
	if (*countToEndOfField == fieldWidth / 2 + 1) { // check if we are currently in the middle of the field
		if (board->fields[*currentField - 1]->numberOfPawns >= i - margin) { // check if there are any checkers in the field
			if (i > margin && i < fieldHeight - margin) { // check if we are in a place where we can place checkers
				printTheSymbolForPawn(i, j, startingY, startingX, countToEndOfField, board, currentField, pawnSymbol);
				return true;
			}
			if (i > margin && i == fieldHeight - margin) {
				printNumberOfHiddenPawns(i, j, startingY, startingX, countToEndOfField, board, currentField);
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

void printBoard(Board *board) {
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

int getNumberOfPawnsOnBar(Board* board, int playerId)
{
	return board->bar->player->id == playerId ? board->bar->numberOfPawns : 0;
}

int getNumberOfPawnsInCourt(Board* board, int playerId)
{
	return board->court[playerId]->numberOfPawns;
}

void printBarStatus(Board* board) {
	int currentY = boardHeight + 2;
	int currentX = 1;

	gotoxy(currentX, currentY);
	char temp[50];
	sprintf(temp, "Number of red player's pawns in the bar: %d", getNumberOfPawnsOnBar(board, idOfPlayerRed));
	cputs((const char*)temp);

	gotoxy(currentX, currentY+1);
	sprintf(temp, "Number of white player's pawns in the bar: %d", getNumberOfPawnsOnBar(board, idOfPlayerWhite));
	cputs((const char*)temp);
}

void printCourtStatus(Board* board) {
	int currentY = boardHeight + 2 + 3;
	int currentX = 1;

	gotoxy(currentX, currentY);
	char temp[50];
	sprintf(temp, "Number of red player's pawns in the court: %d", getNumberOfPawnsInCourt(board, idOfPlayerRed));
	cputs((const char*)temp);

	gotoxy(currentX, currentY + 1);
	sprintf(temp, "Number of white player's pawns in the court: %d", getNumberOfPawnsInCourt(board, idOfPlayerWhite));
	cputs((const char*)temp);
}

void printCurrentTurn(Player* currentPlayer) {
	int currentY = boardHeight + 2 + 3 + 3;
	int currentX = 1;

	gotoxy(currentX, currentY);
	if (currentPlayer->id == 0) {
		cputs((const char*) "Current turn: Red");
	}
	if (currentPlayer->id == 1) {
		cputs((const char*)"Current turn: White");
	}
}

void printCurrentRolledNumbers(Board* board) {
	int currentY = boardHeight + 2 + 3 + 3 + 1;
	int currentX = 1;

	gotoxy(currentX, currentY);
	cputs((const char*)"Rolled numbers:");
	handleShowDiceBag(board->diceBag);
}

void printMenu(Board* board) {
	int currentY = boardHeight + 2 + 3 + 3 + 2 + 3;
	int currentX = 1;
	char temp[50];

	gotoxy(currentX, currentY);
	sprintf(temp, "M)OVE");
	cputs((const char*)temp);
	currentX += 7;

	gotoxy(currentX, currentY);
	sprintf(temp, "S)AVE");
	cputs((const char*)temp);
	currentX += 7;

	gotoxy(currentX, currentY);
	sprintf(temp, "L)OAD");
	cputs((const char*)temp);
	currentX += 7;

	gotoxy(currentX, currentY);
	sprintf(temp, "Q)UIT");
	cputs((const char*)temp);
}

void setupPrint(){
	settitle("Michal, Malinowski, 197928"); // settitle sets the window title

	//_setcursortype(_NOCURSOR); // hide the blinking cursor
	textmode(8); // set the text mode to 80x50

	textbackground(BLACK);
	clrscr(); // clear the screen : we fill it out with spaces with 
	textcolor(7); // we set the text color (7 == LIGHTGRAY)
}

void handlePrint(Board* board, Player* currentPlayer) {
	// if the program is compiled in pure C, then we need to initialize
	// the library ourselves; __cplusplus is defined only if a C++ compiler
	// is used

	#ifndef __cplusplus
		Conio2_Init();
	#endif

	setupPrint();

	printFieldNumbersTop();
	printBoard(board);
	printFieldNumbersBottom();

	printBarStatus(board);
	printCourtStatus(board);

	printCurrentTurn(currentPlayer);
	printCurrentRolledNumbers(board);

	printMenu(board);

	_setcursortype(_NOCURSOR);
}

void clearMenuResponseField() {
	int currentY = boardHeight + 2 + 3 + 3 + 2 + 1;
	int currentX = 1;

	for (int i = 0; i < 75; i++) {
		gotoxy(currentX + i, currentY);
		cputs((const char*)" ");
	}
}

void removeDices(Board* board, Player* currentPlayer, int sizeOfMove) { // remove the dices untill there are only unused dices left
	int temp = 0;
	for (int i = 0; i < board->diceBag->numberOfElements; i++) {
		if (temp == sizeOfMove) {
			break;
		}
		else {
			if (board->diceBag->numbers[i] == sizeOfMove) {
				temp += handlePopFront(board->diceBag);
			}
			else {
				temp += handlePopBack(board->diceBag);
			}
		}
	}
}

void handleMoveInput(int* fieldFrom, int* fieldTo) {
	int currentY = boardHeight + 2 + 3 + 3 + 2 + 1;
	int currentX = 1;

	clearMenuResponseField();

	gotoxy(currentX, currentY);
	cputs((const char*)"Input the number of the field from which the pawn will be taken: ");

	cin >> *fieldFrom;

	clearMenuResponseField();

	gotoxy(currentX, currentY);
	cputs((const char*)"Input the number of the field on which we will place the pawn: ");

	cin >> *fieldTo;
}

void handleMoveInit(Board* board, Player* currentPlayer, EveryMoveBag* everyMoveBag) {
	initEveryMoveBag(everyMoveBag);
	genEveryMove(everyMoveBag, board, currentPlayer);

	int currentY = boardHeight + 2 + 3 + 3 + 2 + 3 + 2;
	int currentX = 1;

	gotoxy(currentX, currentY);
	handlePrint(board, currentPlayer);
	handleShowEveryMoveBag(everyMoveBag);
}

void handleMove(Board* board, Player* currentPlayer) {

	int currentY, currentX;

	EveryMoveBag* everyMoveBag = new EveryMoveBag();

	handleMoveInit(board, currentPlayer, everyMoveBag);

	if (everyMoveBag->numberOfElements > 0) { // if there are possible moves

		int fieldFrom, fieldTo;

		handleMoveInput(&fieldFrom, &fieldTo);

		clearMenuResponseField();

		if (isMoveValid(board, currentPlayer, fieldFrom, fieldTo, everyMoveBag) == 1) {
			////////////////////////////////////////////////////////////////////////////////// DELETING ENEMY PAWN AFTER BEATING IT HERE
			if (canCapturePawn(board, currentPlayer, fieldFrom, fieldTo) == 1) {
				removePawn(board, fieldTo);
			}
			// 

			movePawn(board, currentPlayer, fieldFrom, fieldTo);
			//gotoxy(currentX, currentY);
			//cputs((const char*)"Pawn was moved!"); It just flicks for a second
			int sizeOfMove = abs(fieldFrom - fieldTo);
			removeDices(board, currentPlayer, sizeOfMove);
		}
		handleMove(board, currentPlayer);
	}


	// CHECK IF EVERY DICE WAS USED -> CHECK IF SUM OF DICE IN THE BAG IS EQUAL TO THE LENFTH OF THE MOVE
	// 
	// IF NOT REMOVE THE DICES FROM THE DICEBAG
	// REPEAT THIS FUNCTION
	// 
	// IF EVERY DICE WAS USED  DO NOTHING

}

void handleUserResS(Board* board, Player* currentPlayer, int* isGameFinished) {
	saveBoardToFile(board, currentPlayer);
	clearMenuResponseField();

	int currentY = boardHeight + 2 + 3 + 3 + 2 + 1;
	int currentX = 1;
	gotoxy(currentX, currentY);
	cputs((const char*)"Saved!");
}

void handleUserResL(Board* board, Player* currentPlayer, int* isGameFinished, Player* red, Player* white) {

	freeBoard(board);
	setUpBoard(board, red, white, currentPlayer);
	handlePrint(board, currentPlayer);
	clearMenuResponseField();

	int currentY = boardHeight + 2 + 3 + 3 + 2 + 1;
	int currentX = 1;
	gotoxy(currentX, currentY);
	cputs((const char*)"Loaded!");
}

void handleM(Board* board, Player* currentPlayer, char character) {
	if (character == 'm') {
		handleMove(board, currentPlayer);
		initDiceBag(board->diceBag, currentPlayer); // reset the dicebag
	}
}

void handleQ(Board* board, Player* currentPlayer, char character, int* isGameFinished) {
	if (character == 'q') {
		*isGameFinished = 1;
	}
}

int isCharacterCorrect(char character) {
	if (character == 'm' || character == 's' || character == 'l' || character == 'q') {
		return 1;
	}
	return 0;
}

void handleMQ(Board* board, Player* currentPlayer, int* isGameFinished, Player* red, Player* white, char character) {
	_setcursortype(_NORMALCURSOR);
	handleM(board, currentPlayer, character);
	handleQ(board, currentPlayer, character, isGameFinished);
}

void handleUserRes(Board* board, Player* currentPlayer, int* isGameFinished, Player* red, Player* white) {
	char character;
	cin >> character;
	if (isCharacterCorrect(character) == 1) { // user given correct input
		handleMQ(board, currentPlayer, isGameFinished, red, white, character);
		if (character == 's') {
			handleUserResS(board, currentPlayer, isGameFinished);
			handleUserRes(board, currentPlayer, isGameFinished, red, white); // after saving the board, we need to ask the user for another input
		}
		if (character == 'l') {
			handleUserResL(board, currentPlayer, isGameFinished, red, white);
			handleUserRes(board, currentPlayer, isGameFinished, red, white); // after loading the board, we need to ask the user for another input
		}
	}
	else{ // user gave incorrect input
		handleUserRes(board, currentPlayer, isGameFinished, red, white);
	}
}