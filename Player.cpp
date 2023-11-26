#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.x = mainGameMechsRef->getBoardSizeX()/2;
    playerPos.y = mainGameMechsRef->getBoardSizeY()/2;
    playerPos.symbol = '@';
}


Player::~Player()
{
    // delete any heap members here
    delete mainGameMechsRef;
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
    // return the reference to the playerPos arrray list
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
        mainGameMechsRef->setInput(0);
    }      
}

void Player::movePlayer()
{
    int col = mainGameMechsRef->getBoardSizeY();
    int row = mainGameMechsRef->getBoardSizeX();

    switch(myDir){
        case UP:
            playerPos.y = (playerPos.y - 1) % (col - 2);
            if(playerPos.y < 0){
                playerPos.y = col - 2;
            }
            break;
        case DOWN:
            playerPos.y = (playerPos.y + 1) % (col - 1);
            break;
        case LEFT:
            playerPos.x = (playerPos.x - 1) % (row - 2);
            if(playerPos.x < 0){
                playerPos.x = row - 2;
            }
            break;
        case RIGHT:
            playerPos.x = (playerPos.x + 1) % (row - 2);
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
}
