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
    Player* currentPlayer = getPlayerWhichGoesFirst(&red, &white); // currentPlayer is a pointer to a pointer
    initPlayer(&red, idOfPlayerRed);
    initPlayer(&white, idOfPlayerWhite);

    Board board;
    setUpBoard(&board, &red, &white, currentPlayer); // set up the board (this is the most basic board loaded from the file)
    // if in the file every value of the dice is 0 then the dicebag is not set to any player

    while (isGameFinished != 1)
    {
        handleRoll(board.diceBag, currentPlayer); // roll the dice, this function should overwrite the diceBag with the new values // loading of the board from the file from the menu function should be below this one because handleRoll overwrites the dicebag 
        handlePrint(&board, currentPlayer);
        handleUserRes(&board, currentPlayer, &isGameFinished, &red, &white);
        changeCurrentPlayer(&currentPlayer, &red, &white);
    }
    _setcursortype(_NORMALCURSOR);
}