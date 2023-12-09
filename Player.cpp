#include <iostream>

#include "Player.h"

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