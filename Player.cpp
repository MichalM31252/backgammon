#include <iostream>

#include "Player.h"
#include "Constants.h"

using namespace std;

// Everything related to the player

void initPlayer(Player* player, int id) {
	player->id = id;
}

void changeCurrentPlayer(Player** player, Player* red, Player* white) { // changes the current player
	if (*player == white) {
		*player = red;
	}
	else {
		*player = white;
	}
}

int getDirectionOfMoves(Player* currentPlayer) {
	if (currentPlayer->id == 0) {
		return directionOfMovementRed;
	}
	else if (currentPlayer->id == 1) {
		return directionOfMovementWhite;
	}
	else {
		perror("");
	}
}

int getPositionOfCourt(Player* currentPlayer) {
	if (currentPlayer->id == 0) {
		return courtFieldNumberRed;
	}
	else if (currentPlayer->id == 1) {
		return courtFieldNumberWhite;
	}
}