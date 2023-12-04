#define _CRT_SECURE_NO_DEPRECATE

#include <fstream>

#include "FileInterface.h"
#include "Board.h"

using namespace std;

// Reading and writing to files

int setupFieldsFromFile(Board* board)
{

	FILE* file = fopen("basic_board.txt", "r");
	if (file == NULL) {
		perror("Error opening the file");
	}

	int idOfPlayer, positionOfPawn;

	for (int i = 0; i < amountOfPawns; i++)
	{
		if (fscanf(file, "%d %d", &idOfPlayer, &positionOfPawn) != 2) {
			printf("Error reading numbers from the file\n");
			fclose(file);
			return 1;
		}

		board->fields[positionOfPawn - 1]->numberOfPawns++;
		board->fields[positionOfPawn - 1]->playerId = idOfPlayer;
	}

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
				fprintf(file, "%d %d\n", board->fields[i]->playerId, i + 1);
			}
		}
	}

	fclose(file);

	return 0;
}