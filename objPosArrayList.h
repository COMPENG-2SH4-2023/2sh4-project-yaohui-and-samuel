#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 1000

#include "objPos.h"

class objPosArrayList
{
    private:
        objPos* aList;
        int sizeList;
        int sizeArray;

    public:
        objPosArrayList();
        ~objPosArrayList();

        int getSize();
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void removeItem(int index);
        void removeHead();
        void removeTail();
        void changeItem(int index, objPos thisPos);
        
        void getHeadElement(objPos &returnPos);
        void getTailElement(objPos &returnPos);
        void getElement(objPos &returnPos, int index);
};

#endif