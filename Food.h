#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"

class Food
{
    private:
        objPosArrayList *bucket;

    public:
        Food();
        Food(objPosArrayList *foodList);
        ~Food();

        void generateFood(objPosArrayList *blockOff);
        void getFoodPos(objPosArrayList &returnPos);
};