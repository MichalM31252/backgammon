#define _CRT_SECURE_NO_DEPRECATE

#include <fstream>

#include "FileInterface.h"
#include "Board.h"

using namespace std;

// Reading and writing to files

int setupFieldsFromFile(Board* board, Player* red, Player* white, FILE* file) {
	int idOfPlayer, positionOfPawn, numberOnDice;

	for (int i = 0; i < amountOfPawns; i++)
	{
		if (fscanf(file, "%d %d", &idOfPlayer, &positionOfPawn) != 2) {
			fclose(file);
			return 1;
		}

		board->fields[positionOfPawn - 1]->numberOfPawns++;

		if (idOfPlayer == 0) {
			board->fields[positionOfPawn - 1]->player = red;
		}
		else {
			board->fields[positionOfPawn - 1]->player = white;
		}
	}
}

int setupDiceBagFromFile(Board* board, Player* red, Player* white, FILE* file)
{
	int idOfPlayer, numberOnDice;
	for (int i = 0; i < maximumNumberOfDicesInDiceBag; i++) {
		if (fscanf(file, "%d %d", &idOfPlayer, &numberOnDice) != 2) {
			fclose(file);
			return 1;
		}
		if (numberOnDice == 0) {
			continue;
		}
		if (i == 0) {
			if (idOfPlayer == idOfPlayerRed) {
				initDiceBag(board->diceBag, red);
			}
			if (idOfPlayer == idOfPlayerWhite) {
				initDiceBag(board->diceBag, white);
			}
		}
		addNumberToDiceBag(board->diceBag, numberOnDice);
	}
}

int setupBarFromFile(Board* board, Player* red, Player* white, FILE* file)
{
	int idOfPlayer, numberOfElementsInBar;

	for (int i = 0; i < numberOfBars; i++) {
		if (fscanf(file, "%d %d", &idOfPlayer, &numberOfElementsInBar) != 2) {
			fclose(file);
			return 1;
		}

		if (idOfPlayer == idOfPlayerRed) {
			board->bar->player = red;
		}
		if (idOfPlayer == idOfPlayerWhite) {
			board->bar->player = white;
		}
		board->bar->numberOfPawns = numberOfElementsInBar;
	}
}

int setupCourtFromFile(Board* board, Player* red, Player* white, FILE* file)
{
	int idOfPlayer, numberOfElementsInCourt;

	for (int i = 0; i < amountOfCourt; i++) {
		if (fscanf(file, "%d %d", &idOfPlayer, &numberOfElementsInCourt) != 2) {
			fclose(file);
			return 1;
		}

		if (idOfPlayer == idOfPlayerRed) {
			board->court[idOfPlayer]->player = red;
		}
		if (idOfPlayer == idOfPlayerWhite) {
			board->court[idOfPlayer]->player = white;
		}
		board->court[idOfPlayer]->numberOfPawns = numberOfElementsInCourt;
	}
}

void setupBoardFromFile(Board* board, Player* red, Player* white)
{

	FILE* file = fopen("basic_board.txt", "r");
	if (file == NULL) {
		perror("Error opening the file");
	}


	setupFieldsFromFile(board, red, white, file);
	setupDiceBagFromFile(board, red, white, file);
	setupBarFromFile(board, red, white, file); // this is not working
	setupCourtFromFile(board, red, white, file); // this is not working

	fclose(file);

}

int saveBoardToFile(Board* board)
{
	FILE* file = fopen("board_save.txt", "w");
	if (file == NULL) {
		perror("Error opening the file");
	}

	for (int i = 0; i < amountOfFields; i++)
	{
		if (board->fields[i]->numberOfPawns != 0) {
			for (int j = 0; j < board->fields[i]->numberOfPawns; j++) {
				fprintf(file, "%d %d\n", board->fields[i]->player->id, i + 1);
			}
		}
	}

	fclose(file);

	return 0;
}