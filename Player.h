#pragma once

// Everything related to the player

struct Player
{
	int id; // Id of the player

	// char* name; // Pointer to the name of the player for hall of fame
	// int numberOfWins; // Number of wins for hall of fame
};


void initPlayer(Player* player, int id);
void changeCurrentPlayer(Player** player, Player* red, Player* white);
int getDirectionOfMoves(Player* currentPlayer);
int getPositionOfCourt(Player* currentPlayer);