#pragma once

// Reading and writing to files

#include "Field.h"
#include "Board.h"

#include "Constants.h"

void setupBoardFromFile(Board* board, Player* red, Player* white, Player* currentPlayer);

int setupFieldsFromFile(Board* board, Player* red, Player* white, FILE* file);
int setupDiceBagFromFile(Board* board, Player* red, Player* white, FILE* file);
int setupBarFromFile(Board* board, Player* red, Player* white, FILE* file);
int setupCourtFromFile(Board* board, Player* red, Player* white, FILE* file);

int saveBoardToFile(Board* board, Player* Player);