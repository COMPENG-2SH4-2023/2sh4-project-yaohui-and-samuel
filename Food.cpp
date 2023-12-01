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

    // Copy the preset foodList into the bucket
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

    /*
    The random coordination generation is the most brilliant part of this program (just my personal opinion)

    Unlike what was taught in class, I didn't use a vector array to check for duplicates
    I used THE ArrayList WE CREATED to store all the possible coordinations before random number generation
    (that means coordinates other than the borders and the player)
    Then, randomly pick one from the list, store it seperately and then remove it from the list
    so that it will not be picked again (YES I ADDED SOME MORE METHODS TO THE ARRAYLIST CLASS)
    The process will be repeated until all the food elements' coordinations are generated

    Such practices ensures every random coordination generated is unique,
    therefore the program will NOT fall into infinate loop when there are very few spaces left on the board
    Vector array method only saves time on searching for duplicates, but it doesn't ensure uniqueness upon generation
    It will have a time complexity of O(infinite) if really really unlucky, just like bogo sort,
    (I know it's not a real "time complexity", but it's the best way to describe it)
    especially when the board is almost full of the snake's body and the player is about to win!
    Think about how the player will feel when the player is about to win but the program crashes/falls into infinate loop
    (well it's funny that a lot of game software companies are doing shitty jobs like this quite often, yeah I'm talking about you Bethseda)

    It was mentioned in class that the instructors actually wanted to encropate linked lists into the course
    That would be actually a better way to do this, but I guess there is no time for teaching that
    Afterall, this course is not named "Data Structures and Algorithms"
    */

    objPosArrayList coordPool;
    int xlength = mainGameMechsRef->getBoardSizeX();
    int ylength = mainGameMechsRef->getBoardSizeY();
    int blockOffSize = blockOff.getSize();
    int totalSpaces = (mainGameMechsRef->getBoardSizeX() - 2) * (mainGameMechsRef->getBoardSizeY() - 2);
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
                // p variable represents the size of the coordination pool
                // Although there is listSize attribute in the objPosArrayList class
                // but I don't know why it stays at 0 after the program enters the loop below
                // so I had to use the getSize() prior to the loop to get the size of the list
                // even if I don't use the p variable in the later loop, the program still works
                // but the listSize attribute will be 0 without the p variable decleared???
                // it's the strangest thing in this program, really
                // like black magic (why??????????????????????????????????)
                p++;
            }
            nonBlock = true;
        }
    }

    // The maxItem is the number of food that will be generated
    // if the totalSpaces is less than the number of food in the bucket
    // then the maxItem will be the totalSpaces
    // to avoid the food from generating on occupied spaces, like on the snake's body
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
        int randIndex = rand() % poolSize;
        coordPool.getElement(tempPos, randIndex);
        coordPool.removeItem(randIndex);

        objPos tempFood;
        bucket->getElement(tempFood, i);
        x = tempPos.x;
        y = tempPos.y;
        symbol = tempFood.symbol;
        tempFood.setObjPos(x, y, symbol);
        bucket->changeItem(i, tempFood);

        // If the player size is 1, then we don't need the shortenFood
        // because the player is already at its shortest length
        // otherwise the program will fall into infinate loop
        // I just tweaked the coordinate of - to a negative number when this happens
        // so that it will not be drawn on the screen
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