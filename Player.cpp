#include <iostream>

#include "Player.h"

using namespace std;

// Everything related to the player

void checkIfPlayerWorks() {
	cout << "Player" << endl;
}

int getIdOfNextPlayer(Player* player) {
	return player->id + 1; // Needs a fix
}