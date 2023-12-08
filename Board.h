#pragma once

// Everything related to the board
#include "Field.h"
#include "Player.h"
#include "Bar.h"
#include "Court.h"
#include "Dice.h"

#include "Constants.h"

struct Board
{
	Field* fields[amountOfFields];
	Bar* bar;
	Court* court[amountOfCourt];
	DiceBag* diceBag;
};

void initBoard(Board* board);
void setUpBoard(Board* board, Player* red, Player* white);
void setUpDiceBag(Board* board, Player* red, Player* white);
void setUpBar(Board* board);
void setUpCourt(Board* board, Player* p, int idOfPlayer);