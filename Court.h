#pragma once

// Everything related to the court

#include "Player.h"

struct Court
{
	int numberOfPawns;
	Player* player;
};

void checkIfCourtWorks();
