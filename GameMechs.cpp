#include "GameMechs.h"

GameMechs::GameMechs()
{
    boardSizeX = 20;
    boardSizeY = 10;
    loseFlag = false;
    winFlag = false;
    score = 0;
    exitFlag = false;
    input = 0;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    loseFlag = false;
    winFlag = false;
    score = 0;
    exitFlag = false;
    input = 0;
}


bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}


bool GameMechs::getLoseFlag()
{
    return loseFlag;
}


bool GameMechs::getWinFlag()
{
    return winFlag;
}

char GameMechs::getInput()
{
    if(MacUILib_hasChar() == 1){
        input = MacUILib_getChar();
    }
    return input;
}


int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}


int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}


int GameMechs::getScore()
{
    return score;
}


void GameMechs::setLose()
{
    loseFlag = true;
}


void GameMechs::setWin()
{
    winFlag = true;
}


void GameMechs::increaseScore()
{
    score++;
}


void GameMechs::setInput(char this_input)
{
    input = this_input;
}


void GameMechs::clearInput()
{
    input = 0;
}
