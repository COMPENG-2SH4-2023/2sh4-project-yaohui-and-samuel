#include "Food.h"

Food::Food()
{
    bucket = new objPosArrayList();
    
}


void GameMechs::generateFood(objPosArrayList *blockOff)
{
    srand(time(NULL));
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