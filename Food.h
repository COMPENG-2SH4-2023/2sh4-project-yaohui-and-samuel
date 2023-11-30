#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

class Food
{
    private:
        objPosArrayList *bucket;
        GameMechs *mainGameMechsRef;

    public:
        Food(GameMechs* thisGMRef);
        Food(objPosArrayList *foodList, GameMechs* thisGMRef);
        ~Food();

        void generateFood(objPosArrayList &blockOff, int playerSize);
        void getFoodPos(objPosArrayList &returnPos);
};

#endif