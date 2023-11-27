#include "GameMechs.h"

GameMechs::GameMechs()
{
    boardSizeX = 20;
    boardSizeY = 10;
    loseFlag = false;
    score = 0;
    exitFlag = false;
    input = 0;

    foodPos.setObjPos(-1, -1, 'o');
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    loseFlag = false;
    score = 0;
    exitFlag = false;
    input = 0;

    foodPos.setObjPos(-1, -1, 'o');
}


bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}


bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
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


int GameMechs::getscore()
{
    return score;
}


// void setLoseFlag()
// {
//     loseFlag = true;
// }


void GameMechs::increaseScore()
{
    score++;
}


void GameMechs::generateFood(objPosArrayList *blockOff)
{
    int count = 0;
    bool pass = false;
    bool identical = false;
    int xcoord;
    int ycoord;

    while(pass != true){
        //generate a random position for food
        int x = rand() % (boardSizeX - 2);
        if(x == 0){
            x++;
        }
        int y = rand() % (boardSizeY - 2);
        if(y == 0){
            y++;
        }

        //check if the position is identical to any of the positions in the blockOff list
        for(int i = 0; i < blockOff->getSize(); i++){
            objPos tempPos;
            blockOff->getElement(tempPos, i);
            if(tempPos.x == x && tempPos.y == y){
                identical = true;
                break;
            }
        }

        if(identical == false){
            pass = true;
            xcoord = x;
            ycoord = y;
        }
    }

    foodPos.setObjPos(xcoord, ycoord, 'o');
}


void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos);
}


void GameMechs::setInput(char this_input)
{
    input = this_input;
}


void GameMechs::clearInput()
{
    input = 0;
}
