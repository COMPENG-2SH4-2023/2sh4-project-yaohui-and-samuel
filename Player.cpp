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
    //objPos temp = objPos(playerPos.x, playerPos.y, playerPos.symbol);
    objPos temp = objPos(playerPos);
    int row = mainGameMechsRef->getBoardSizeY();
    int col = mainGameMechsRef->getBoardSizeX();

    switch(myDir){
        case UP:
            playerPos.x = (playerPos.x - 1 + (row - 2)) % (row - 2);
            if(playerPos.x == 0){
                playerPos.x = row - 3; //boundary control
            }else if(playerPos.x == row - 2){
                playerPos.x = 1;
            }
            break;
        case DOWN:
            playerPos.x = (playerPos.x + 1) % (row - 2);
            if(playerPos.x == 0){
                playerPos.x = 1;
            }
            break;
        case LEFT:
            playerPos.y = (playerPos.y - 1 + (col - 2)) % (col - 2);
            if(playerPos.y == 0){
                playerPos.y = col - 3;
            }
            break;
        case RIGHT:
            playerPos.y = (playerPos.y + 1) % (col - 2);
            if(playerPos.y > (col - 3)){
                playerPos.y = 1;
            }else if(playerPos.y == 0){
                playerPos.y = 1;
            }
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

    // board[playerPos.x][playerPos.y] = playerPos.symbol;
    // if(myDir != STOP){
    //     if(temp.x == 0 || temp.x == (row - 2)){
    //         board[temp.x][temp.y] = '#';
    //     }
    //     else if(temp.y == 0 || temp.y == (col - 2)){
    //         board[temp.x][temp.y] = '#';
    //     }else{
    //         board[temp.x][temp.y] = ' ';
    //     }
    // }
}
