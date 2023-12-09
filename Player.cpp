#include <iostream>

#include "Player.h"

using namespace std;

// Everything related to the player

void initPlayer(Player* player, int id) {
	player->id = id;
}

void changeCurrentPlayer(Player** player, Player* red, Player* white) { // TO ZMIENIA ID DRUGIEGO GRACZA A NIE ZMIENIA NA KOLEJNEGO GRACZA
	// tutaj player to pointer to a pointer, red i white to 
	// I assing something that points to a user to an another pointer
	if (*player == white) {
		*player = red;
	}
	else {
		*player = white;
	}
}