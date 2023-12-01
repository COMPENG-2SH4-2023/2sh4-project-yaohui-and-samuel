#include "objPosArrayList.h"

objPosArrayList::objPosArrayList(){
    aList = new objPos[ARRAY_MAX_CAP];
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
}

objPosArrayList::~objPosArrayList(){
    delete[] aList;
}

int objPosArrayList::getSize(){
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos){
    if(sizeList < sizeArray && sizeList >= 0){
        sizeList++;
        for(int i = sizeList; i > 0; i--){
            aList[i] = aList[i - 1];
        }
        aList[0] = thisPos;
    }else if(sizeList == sizeArray){
        //cout << "Array is full" << endl;
        return;
    }
}

void objPosArrayList::insertTail(objPos thisPos){
    if(sizeList == sizeArray){
        //cout << "Array is full" << endl;
        return;
    }else if(sizeList < sizeArray && sizeList >= 0){
        sizeList++;
        aList[sizeList - 1] = thisPos;
    }
}

void objPosArrayList::removeItem(int index){
    if(index < 0 || index >= sizeList){
        //cout << "Index out of bounds" << endl;
        return;
    }else{
        for(int i = index; i < sizeList - 1; i++){
            aList[i] = aList[i + 1];
        }
        sizeList--;
    }
}

void objPosArrayList::removeHead(){
    if(sizeList == 0){
        //cout << "Array is empty" << endl;
        return;
    }else{
        for(int i = 1; i < sizeList; i++){
            aList[i - 1] = aList[i];
        }
        sizeList--;
    }
}

void objPosArrayList::removeTail(){
    if(sizeList == 0){
        //cout << "Array is empty" << endl;
        return;
    }else{
        sizeList--;
    }
}

void objPosArrayList::changeItem(int index, objPos thisPos){
    if(index < 0 || index >= sizeList){
        //cout << "Index out of bounds" << endl;
        return;
    }else{
        aList[index] = thisPos;
    }
}

void objPosArrayList::getHeadElement(objPos &returnPos){
    returnPos.setObjPos(aList[0].x, aList[0].y, aList[0].symbol);
}

void objPosArrayList::getTailElement(objPos &returnPos){
    returnPos.setObjPos(aList[sizeList - 1].x, aList[sizeList - 1].y, aList[sizeList - 1].symbol);
}

void objPosArrayList::getElement(objPos &returnPos, int index){
    if(index < 0 || index >= sizeList){
        //cout << "Index out of bounds" << endl;
        return;
    }else{
        returnPos.setObjPos(aList[index].x, aList[index].y, aList[index].symbol);
    }
}

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.