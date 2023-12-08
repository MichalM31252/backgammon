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
	setupBarFromFile(board, red, white, file); 
	setupCourtFromFile(board, red, white, file); 
	
	// setup current player from file here

	fclose(file);

}

void saveFieldsToFile(Board* board, FILE* file)
{
	for (int i = 0; i < amountOfFields; i++)
	{
		if (board->fields[i]->numberOfPawns != 0) {
			for (int j = 0; j < board->fields[i]->numberOfPawns; j++) {
				fprintf(file, "%d %d\n", board->fields[i]->player->id, i + 1); // not sure about this line
			}
		}
	}
}

void saveDiceBagToFile(Board* board, FILE* file)
{
	for (int i = 0; i < maximumNumberOfDicesInDiceBag; i++) {
		if (board->diceBag->numberOfElements == 0 ) {
			fprintf(file, "%d %d\n", 0, 0);
		}
		else if (board->diceBag->numbers[i] != 0) {
			fprintf(file, "%d %d\n", board->diceBag->player->id, board->diceBag->numbers[i] < 0 ? 0 : board->diceBag->numbers[i]);
		}
	}
}

void saveBarToFile(Board* board, FILE* file)
{
	fprintf(file, "%d %d\n", board->bar->player->id, board->bar->numberOfPawns);
}

void saveCourtToFile(Board* board, FILE* file)
{
	for (int i = 0; i < amountOfCourt; i++) {
		fprintf(file, "%d %d\n", board->court[i]->player->id, board->court[i]->numberOfPawns);
	}
}

void saveCurrentPlayerToFile(Player* player, FILE* file)
{
	fprintf(file, "%d\n", player->id);
}

int saveBoardToFile(Board* board, Player* player)
{
	FILE* file = fopen("board_save.txt", "w");
	if (file == NULL) {
		perror("Error opening the file");
	}

	saveFieldsToFile(board, file);
	saveDiceBagToFile(board, file);
	saveBarToFile(board, file);
	saveCourtToFile(board, file);
	saveCurrentPlayerToFile(player, file);

	fclose(file);

	return 0;
}