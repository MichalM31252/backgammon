#pragma once

// Reading and writing to files

#include "Field.h"
#include "Board.h"

#include "Constants.h"

int setupFieldsFromFile(Board* board, Player* red, Player* white);
int saveBoardToFile(Board* board);