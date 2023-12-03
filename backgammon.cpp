#include <iostream>

#include "Dice.h"
#include "Board.h"
#include "Pawn.h"
#include "UserInterface.h"
#include "FileInterface.h"
#include "Player.h"
#include "Bar.h"
#include "Court.h"

#include "Constants.h"


using namespace std;

int main()
{
    checkIfDiceWorks();
    checkIfBoardWorks();
    checkIfPawnWorks();
    checkIfUserInterfaceWorks();
    checkIfFileInterfaceWorks();
    checkIfPlayerWorks();
    checkIfBarWorks();
    checkIfCourtWorks();
}
