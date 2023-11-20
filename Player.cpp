#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.x = 
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
    // return the reference to the playerPos arrray list
}

void Player::updatePlayerDir()
{
    char input = 
    // PPA3 input processing logic
    if(input != 0)  // if not null character
    {
        switch(input){
            case 'w':
                if(direction != DOWN){
                    direction = UP;
                }
                break;
            case 'a':
                if(direction != RIGHT){
                    direction = LEFT;
                }
                break;
            case 's':
                if(direction != UP){
                    direction = DOWN;
                }
                break;
            case 'd':
                if(direction != LEFT){
                    direction = RIGHT;
                }
                break;
            case 'p':
                direction = CHEAT;
                break;
            // case 'm':
            //     if(speedFlag.level < 2){
            //         speedFlag.level++;
            //     }
            //     break;
            // case 'n':
            //     if(speedFlag.level > -2){
            //         speedFlag.level--;
            //     }
            //     break;
            case 'q':
                exitFlag = 1;
                break;
            default:
                break;
        }
        input = 0;
    }      
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}

