#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <cstdio>

#include <stdio.h> // graphical library
#include "conio2.h"

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
    srand(time(NULL));
    bool isGameFinished = false;

     // this line is needed for the random number generator to work properly

    Player red, white; // Creating the players
    initPlayer(&red, idOfPlayerRed);
    initPlayer(&white, idOfPlayerWhite);

    Board board;
    setUpBoard(&board, &red, &white); // set up the board

    handlePrint(&board);

    // handleRoll(board.diceBag); // roll the dice
    // now for each roll, we need to calculate 
    // if the user decided to use the left dice first use handlePopFront
    // if the user decided to use the right dice first use handlePopBack
    // for dublet just use handlePopFront 4 times

    while (!isGameFinished)
    {
        // id of current player
        // 
        // 
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
    }
    // print the winner

    // emptyDiceBag(&diceBag); // this line is needed to free the memory allocated for the vector at the end of the program
}
