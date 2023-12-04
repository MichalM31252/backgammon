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
#include "Field.h"

#include "Constants.h"


using namespace std;

int main()
{

    srand(time(NULL)); // this line is needed for the random number generator to work properly
    
    int currentPlayerNumber = decideWhichPlayerGoesFirst();

    DiceBag diceBag; 
    initDiceBag(&diceBag); 
    handleRoll(&diceBag);

    Board board;

    emptyDiceBag(&diceBag); // this line is needed to free the memory allocated for the vector at the end of the program

    // if the user decided to use the left dice first use handlePopFront
    // if the user decided to use the right dice first use handlePopBack
    // for dublet just use handlePopFront 4 times
    

    // now for each roll, we need to calculate 


    


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
