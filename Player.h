#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP, EXIT};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* foodRef);
        ~Player();

        objPosArrayList* getPlayerPos();
        void updatePlayerDir();
        void movePlayer();

        bool checkCollision();
        int checkConsumption();
        //void increaseLength();    //do we need this?

    private:
        objPosArrayList *playerPos;
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        Food* foodBucket;
};

#endif