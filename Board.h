#pragma once

// Everything related to the board
#include "Field.h"
#include "Player.h"
#include "Bar.h"
#include "Court.h"

#include "Constants.h"

struct Board
{
	Field* fields[amountOfFields];
	Bar* bar;
	Court* court[amountOfCourt];
};

void initBoard(Board* board);
void setUpBar(Board* board, int idOfPlayer);
void setUpCourt(Board* board, int idOfPlayer);
void setUpBoard(Board* board);