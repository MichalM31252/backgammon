#pragma once

// Everything related to the player

struct Player
{
	int id;

	// char* name; // Pointer to the name of the player for hall of fame
	// int numberOfWins; // Number of wins for hall of fame
};

void checkIfPlayerWorks();
int getIdOfNextPlayer(Player* player);