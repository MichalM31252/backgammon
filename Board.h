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
void setUpBoard(Board* board, Player* red, Player* white, Player* currentPlayer);
void setUpDiceBag(Board* board, Player* red, Player* white);
void setUpBar(Board* board);
void setUpCourt(Board* board, Player* p, int idOfPlayer);
void freeBoard(Board* board);

int isMoveValid(Board* board, Player* currentPlayer, int moveFrom, int moveTo);
void movePawn(Board* board, Player* player, int moveFrom, int moveTo);

