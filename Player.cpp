#include <iostream>

#include "Player.h"

using namespace std;

// Everything related to the player

void initPlayer(Player* player, int id) {
	player->id = id;
}

void changeCurrentPlayer(Player* player, Player* red, Player* white) { // TO ZMIENIA ID DRUGIEGO GRACZA A NIE ZMIENIA NA KOLEJNEGO GRACZA
	if (player == red) { 
		player = white;
	}
	if (player == white) {
		player = red;
	}
}