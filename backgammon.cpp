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
    int isGameFinished = 0;

     // this line is needed for the random number generator to work properly

    Player red, white; // Creating the players
    initPlayer(&red, idOfPlayerRed);
    initPlayer(&white, idOfPlayerWhite);

    Board board;
    setUpBoard(&board, &red, &white); // set up the board (this is the most basic board loaded from the file)
    // why isn't the dicebag read from the file here? 
    // if in the file every value of the dice is 0 then the dicebag is not set to any player

    Player* currentPlayer = getPlayerWhichGoesFirst(&red, &white); // decides which player goes first


    while (isGameFinished != 1)
    {
        handleRoll(board.diceBag, currentPlayer); // roll the dice, this function should overwrite the diceBag with the new values
        // loading of the board from the file from the menu function should be below this one because handleRoll overwrites the dicebag 

        // now for each roll, we need to calculate 
        // if the user decided to use the left dice first use handlePopFront
        // if the user decided to use the right dice first use handlePopBack
        // for dublet just use handlePopFront 4 times

        handlePrint(&board, currentPlayer);

        handleUserResponse(&board, currentPlayer, &isGameFinished);

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
    _setcursortype(_NORMALCURSOR);
    // print the winner

    // emptyDiceBag(&diceBag); // this line is needed to free the memory allocated for the vector at the end of the program 
}
