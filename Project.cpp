#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000
#define LENGTH 21
#define WIDTH 11

Player* myPlayer;
GameMechs* myGM;

char board[WIDTH][LENGTH];

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


int main(void)
{
    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    
    myGM = new GameMechs(LENGTH - 1, WIDTH - 1);
    myPlayer = new Player(myGM);

    //Board initialization
    for(int i = 0; i < WIDTH - 1; i++){
        for(int j = 0; j < LENGTH - 1; j++){
            if(i == 0 || i == WIDTH - 2){
                board[i][j] = '#';
            }
            else if(j == 0 || j == LENGTH - 2){
                board[i][j] = '#';
            }
            else{
                board[i][j] = ' ';
            }
        }
    }

    objPos tempReturn = objPos();
    myPlayer->getPlayerPos(tempReturn);
    board[tempReturn.x][tempReturn.y] = tempReturn.symbol;
}

void GetInput(void)
{
    char input = myGM->getInput();
    myGM->setInput(input);
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    objPos tempReturn = objPos();
    myPlayer->getPlayerPos(tempReturn);
    board[tempReturn.x][tempReturn.y] = tempReturn.symbol;
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    //Draw the board
    for(int i = 0; i < (WIDTH - 1); i++){
        for(int j = 0; j < (LENGTH - 1); j++){
           MacUILib_printf("%c", board[i][j]);
        }
        MacUILib_printf("\n");
    }
    objPos tempPos;
    myPlayer->getPlayerPos(tempPos);
    MacUILib_printf("BoardSize: %dx%d, Player Pos: <%d, %d> + %c\n", myGM->getBoardSizeX(), myGM->getBoardSizeY(), tempPos.x, tempPos.y, tempPos.symbol);
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    MacUILib_uninit();
}
