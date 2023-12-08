#include <iostream>

#include "Player.h"

using namespace std;

// Everything related to the player

void initPlayer(Player* player, int id) {
	player->id = id;
}

void changeCurrentPlayer(Player* player) {
	if (player->id == 0) {
		player->id = 1;
	}
	else {
		player->id = 0;
	}
}