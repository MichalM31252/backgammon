#pragma once

// Reading and writing to files

#include "Field.h"
#include "Board.h"

#include "Constants.h"

int setupBoardFromFile(Board* board, Player* red, Player* white);

int setupDiceBagFromFile(Board* board, Player* red, Player* white, FILE* file);
int setupFieldsFromFile(Board* board, Player* red, Player* white, FILE* file);

int saveBoardToFile(Board* board);