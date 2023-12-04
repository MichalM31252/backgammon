#include <iostream>
#include <stdio.h>


#include "Board.h"

using namespace std;

// Everything related to the board

void initBoard(Board* board) {
	for (int i = 0; i < amountOfFields; i++) {
		board->fields[i] = new Field();
	}

	board->bar = new Bar();

	for (int i = 0; i < amountOfCourt; i++) {
		board->court[i] = new Court();
	}
}

int setupBoardFromFile(Board* board) {

	cout << "jest git" << endl;
	//FILE* file;

	//file = fopen("basic_board.txt", "r");

	//if (file == NULL) {
	//	perror("Error opening the file");
	//}

	//int idOfPlayer, positionOfPawn;

	//for (int i = 0; i < amountOfFields; i++) 
	//{
	//	fscanf(file, "%d %d", &idOfPlayer, &positionOfPawn);
	//	board->fields[positionOfPawn-1]->numberOfPawns++;
	//	board->fields[i]->playerId =idOfPlayer;
	//}

	//board->bar->numberOfPawns = 0;
	//// board->bar->player = nullptr;

	//for (int i = 0; i < amountOfCourt; i++) {
	//	board->court[i]->numberOfPawns = 0;
	//	board->court[i]->player = nullptr;
	//}

	return 0;
}