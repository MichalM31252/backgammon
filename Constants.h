#pragma once

// Constants

// Game constants
const int amountOfPlayers = 2;
const int amountOfPawns = 30;
const int amountOfPawnsForAPlayer = 15;
const int maximumNumberDiceCanRoll = 6;
const int maximumNumberOfDicesInDiceBag = 4;

// Player constants
const int idOfPlayerRed = 0;
const int idOfPlayerWhite = 1;

// Board constants
const int amountOfFields = 24; // DEFAULT 24
const int amountOfCourt = 2;
const int quarters = 4;
const int numberOfBars = 1;

const int startingPointRed = 24;
const int startingPointWhite = 1;

const int directionOfMovementRed = 1;
const int directionOfMovementWhite = -1;

const int startOfTheHomeBoardRed = 19;
const int endOfTheHomeBoardRed = 24;
const int startOfTheHomeBoardWhite = 1;
const int endOfTheHomeBoardWhite = 6;

// Visual constants
const int startingX = 1;
const int startingY = 1;

const int boardStartingX = 2;
const int boardStartingY = 1;

const int amountOfFieldsInQuarter = amountOfFields / quarters;
const int fieldHeight = 11; // DEFAULT 11
const int fieldWidth = 5;

const int quarterWidth = amountOfFieldsInQuarter * (fieldWidth - 1) + 1; // this is because after the first verical line the next line is printed after 4 rows
const int quarterHeight = fieldHeight;

const int boardHeight = 2 * quarterHeight + 3; // with space in the middle
const int boardWidth = quarterWidth * 2 + 1; // with space in the middle

const int margin = 2;
const int lengthBetweenNumbers = 4;

const int baseColor = 7; // This is for visaual purposes only
const int specialColor = 4; // This is for visaual purposes only

const char* const cornerSymbol = "+";
const char* const topAndBottomBorderSymbol = "-";
const char* const leftAndRightBorderSymbol = "|";
const char* const leftCounterSymbol = "\\";
const char* const rightCounterSymbol = "/";
const char* const pawnSymbol = "o";
const char* const space = " ";







