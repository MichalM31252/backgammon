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
			printf("Error reading numbers from the file\n");
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
			printf("Error reading numbers from the file\n");
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
	handleShowDiceBag(board->diceBag);
}

int setupBoardFromFile(Board* board, Player* red, Player* white)
{

	FILE* file = fopen("basic_board.txt", "r");
	if (file == NULL) {
		perror("Error opening the file");
	}


	setupFieldsFromFile(board, red, white, file);
	setupDiceBagFromFile(board, red, white, file);


	fclose(file);

	return 0;
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