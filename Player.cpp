#include "Player.h"

Player::Player(GameMechs* thisGMRef, Food* foodRef)
{
    foodBucket = foodRef;
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
    delete foodBucket;
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


int Player::checkConsumption()
{
    objPosArrayList tempFood;
    foodBucket->getFoodPos(tempFood);

    int size = tempFood.getSize();
    for(int i = 0; i < size; i++){
        objPos tempPos;
        tempFood.getElement(tempPos, i);
        char symbol = tempPos.getSymbol();
        objPos tempHead;
        playerPos->getHeadElement(tempHead);
        
        //returns a specific number depending on the food type for identification in movePlayer() later on
        //1 for normal food, 2 for high score food, 3 for shorten food
        if(tempPos.isPosEqual(&tempHead)){
            switch(symbol){
                case 'o':
                    return 1;
                    break;
                case '*':
                    return 2;
                    break;
                case '-':
                    return 3;
                    break;
                default:
                    break;
            }
        }
    }
    return -1;
}


bool Player::checkSuicide()
{
    objPos tempHead;
    playerPos->getHeadElement(tempHead);

    objPos tempBody;
    for(int i = 1; i < playerPos->getSize(); i++){
        playerPos->getElement(tempBody, i);
        if(tempHead.isPosEqual(&tempBody)){
            return true;
        }
    }
    return false;
}


void Player::movePlayer()
{
    int row = mainGameMechsRef->getBoardSizeX();
    int col = mainGameMechsRef->getBoardSizeY();
    
    objPos currHead;
    playerPos->getHeadElement(currHead);

    switch(myDir){
        case UP:
            currHead.y = (currHead.y - 1) % (col - 1);
            if(currHead.y == 0){
                currHead.y = col - 2;
            }
            break;
        case DOWN:
            currHead.y = (currHead.y + 1) % (col - 1);
            if(currHead.y == 0){
                currHead.y = 1;
            }
            break;
        case LEFT:
            currHead.x = (currHead.x - 1) % (row - 2);
            if(currHead.x == 0){
                currHead.x = row - 2;
            }
            break;
        case RIGHT:
            currHead.x = (currHead.x + 1) % (row - 1);
            if(currHead.x == 0){
                currHead.x = 1;
            }
            break;
        case STOP:
            break;
        case EXIT:
            mainGameMechsRef->setExitTrue();
            break;
        default:
            break;
    }

    int consumption = checkConsumption();
    int playerSize = playerPos->getSize();
    
    //Food 'o' increases the score and length by 1
    //High score food '*' increases the score by 5
    //Shorten food '-' decreases the length by 1
    if(consumption > 0){
        // 1 for normal food, 2 for high score food, 3 for shorten food
        switch(consumption){
            case 1:
                playerPos->insertHead(currHead);
                mainGameMechsRef->increaseScore();
                break;
            case 2:
                for(int i = 0; i < 5; i++){
                    mainGameMechsRef->increaseScore();
                }
                break;
            case 3:
                playerPos->removeTail();
                break;
            default:
                break;
        }
        objPosArrayList& playerPosRef = *playerPos; // Create a reference to playerPos
        foodBucket->generateFood(playerPosRef, playerSize); // Pass the reference to generateFood
    }else{
        playerPos->insertHead(currHead); // Insert the new head into the head of the list
        playerPos->removeTail(); // Remove the tail of the list
    }
}