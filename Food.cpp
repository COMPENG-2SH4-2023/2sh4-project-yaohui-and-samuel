#include "Food.h"

Food::Food(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    bucket = new objPosArrayList();
    
    objPos regularFood;
    regularFood.setObjPos(-1, -1, 'o');
    objPos highScoreFood;
    highScoreFood.setObjPos(-2, -2, '*');
    objPos shortenFood;
    shortenFood.setObjPos(-3, -3, '-');

    for(int i = 0; i < 3; i++){
        bucket->insertTail(regularFood);
    }
    bucket->insertTail(highScoreFood);
    bucket->insertTail(shortenFood);
}

Food::Food(objPosArrayList *foodList, GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    bucket = new objPosArrayList();

    int length = foodList->getSize();
    for(int i = 0; i < length; i++){
        objPos tempPos;
        foodList->getElement(tempPos, i);
        bucket->insertTail(tempPos);
    }
}

Food::~Food()
{
    delete bucket;
    delete mainGameMechsRef;
}

void Food::generateFood(objPosArrayList &blockOff, int playerSize)
{
    srand(time(NULL));
    int totalSpaces = (mainGameMechsRef->getBoardSizeX() - 2) * (mainGameMechsRef->getBoardSizeY() - 2);

    objPosArrayList coordPool;
    int xlength = mainGameMechsRef->getBoardSizeX();
    int ylength = mainGameMechsRef->getBoardSizeY();
    int blockOffSize = blockOff.getSize();
    bool nonBlock = true;
    int p = 0;

    for(int i = 2; i < xlength - 2; i++){
        for(int j = 2; j < ylength - 2; j++){
            // Filter out the positions that are blocked off
            for(int k = 0; k < blockOffSize; k++){
                objPos tempPos;
                blockOff.getElement(tempPos, k);
                if(tempPos.x == i && tempPos.y == j){
                    nonBlock = false;
                    break;
                }
            }

            // If the position is not blocked off, add it to the pool

            // I know it has an additional attribute 'symbol'
            // but it doesn't matter because we are only using the x and y attributes 
            // afterall C++ doesn't have a built-in arraylist class, unlike Java
            if(nonBlock == true){
                objPos tempPos;
                tempPos.setObjPos(i, j, '1');
                coordPool.insertTail(tempPos);
                p++;
            }
            nonBlock = true;
        }
    }


    int maxItem;
    if(totalSpaces < bucket->getSize()){
        maxItem = totalSpaces;
    }

    for(int i = 0; i < maxItem; i++){
        int x;
        int y;
        char symbol;

        objPos tempPos;
        int poolSize = coordPool.getSize();
        int randIndex = rand() % p;
        coordPool.getElement(tempPos, randIndex);
        coordPool.removeItem(randIndex);

        objPos tempFood;
        bucket->getElement(tempFood, i);
        x = tempPos.x;
        y = tempPos.y;
        symbol = tempFood.symbol;
        tempFood.setObjPos(x, y, symbol);
        bucket->changeItem(i, tempFood);

        if(playerSize == 1){
            objPos replace;
            replace.setObjPos(-3, -3, '-');
            bucket->changeItem(4, replace);
        }
    }
}


void Food::getFoodPos(objPosArrayList &returnPos)
{
    int length = bucket->getSize();
    for(int i = 0; i < length; i++){
        objPos tempPos;
        bucket->getElement(tempPos, i);
        returnPos.insertTail(tempPos);
    }
}