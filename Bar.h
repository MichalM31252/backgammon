#pragma once

// Everything related to the bar
#include "Player.h"


struct Bar
{
	int numberOfPawns;
	Player* player;
};

void checkBar();