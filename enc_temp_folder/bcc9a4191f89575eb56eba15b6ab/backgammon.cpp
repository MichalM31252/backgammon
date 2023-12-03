#include <iostream>
#include <cstdlib>

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

    srand(time(NULL)); // this line is needed for the random number generator to work properly

    DiceBag diceBag; 
    initDiceBag(&diceBag); 
    handleRoll(&diceBag); // doesn't work


    


    // set up the board
    // 
    // decide who goes first
    //
    // while (game is not over)
    // {
    //     player rolls the dice
    // 
    //     if (player can move)
    //     {
    //         player moves
    //     }
    //     else
    //     {
    //         player passes
    //     }
    // }
    //
    // print the winner


    
}
