#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // create a temp objPos to store the head first
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');

    // then insert the head into the playerPos array list
    playerPos = new objPosArrayList();
    playerPos->insertHead(tempPos);
}


Player::~Player()
{
    // delete any heap members here
    delete mainGameMechsRef;
    delete playerPos;
}


objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos array list
    return playerPos;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();

    if(input != 0)  // if not null character
    {
        switch(input){
            case 'w':
                if(myDir != DOWN){
                    myDir = UP;
                }
                break;
            case 'a':
                if(myDir != RIGHT){
                    myDir = LEFT;
                }
                break;
            case 's':
                if(myDir != UP){
                    myDir = DOWN;
                }
                break;
            case 'd':
                if(myDir != LEFT){
                    myDir = RIGHT;
                }
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
                myDir = EXIT;
                break;
            default:
                break;
        }
        mainGameMechsRef->clearInput();
    }      
}

void Player::movePlayer()
{
    int row = mainGameMechsRef->getBoardSizeX();
    int col = mainGameMechsRef->getBoardSizeY();
    
    objPos newHead;
    objPos currHead;
    playerPos->getHeadElement(currHead);

    switch(myDir){
        case UP:
            currHead.y = (currHead.y - 1) % (col - 2);
            if(currHead.y < 0){
                currHead.y = col - 2;
            }
            break;
        case DOWN:
            currHead.y = (currHead.y + 1) % (col - 1);
            break;
        case LEFT:
            currHead.x = (currHead.x - 1) % (row - 2);
            if(currHead.x < 0){
                currHead.x = row - 2;
            }
            break;
        case RIGHT:
            currHead.x = (currHead.x + 1) % (row - 2);
            break;
        case STOP:
            break;
        case EXIT:
            mainGameMechsRef->setExitTrue();
            break;
        // case CHEAT:
        //     win = 1;
        //     break;
        default:
            break;
    }

    bool consumption = checkConsumption();
    if(consumption){
        //increaseLength();
        playerPos->insertHead(currHead);
        mainGameMechsRef->increaseScore();
        mainGameMechsRef->generateFood(playerPos);
    }else{
        playerPos->insertHead(currHead); //Insert the new head into the head of the list
        playerPos->removeTail(); //Remove the tail of the list
    }
    
}


bool Player::checkConsumption()
{
    objPos tempFood;
    mainGameMechsRef->getFoodPos(tempFood);

    objPos tempHead;
    playerPos->getHeadElement(tempHead);

    if(tempHead.isPosEqual(&tempFood)){
        return true;
    }else{
        return false;
    }
}


// void Player::increaseLength()
// {
    
// }