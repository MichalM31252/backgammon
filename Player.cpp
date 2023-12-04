#include <iostream>

#include "Player.h"

using namespace std;

// Everything related to the player

int getIdOfNextPlayer(Player* player) {
	return player->id + 1; // Needs a fix
}

void initPlayer(Player* player, int id) {
	player->id = id;
}