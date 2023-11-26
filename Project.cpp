#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

Player* myPlayer;
GameMechs* myGM;

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
    
    myGM = new GameMechs(26, 13);
    myPlayer = new Player(myGM);

    objPos tempReturn = objPos();
    myPlayer->getPlayerPos(tempReturn);
    
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
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    objPos tempReturn = objPos();
    myPlayer->getPlayerPos(tempReturn);

    //Draw the board
    for(int i = 0; i < myGM->getBoardSizeY(); i++){
        for(int j = 0; j < myGM->getBoardSizeX(); j++){
            if((i == 0 || i == myGM->getBoardSizeY() - 1) || (j == 0 || j == myGM->getBoardSizeX() - 1)){
               MacUILib_printf("#");
            }else if(i == tempReturn.y && j == tempReturn.x){
               MacUILib_printf("%c", tempReturn.symbol);
            }else{
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }
    objPos tempPos;
    myPlayer->getPlayerPos(tempPos);
    MacUILib_printf("BoardSize: %dx%d, Player Pos: <%d, %d> + %c\n", myGM->getBoardSizeX(), myGM->getBoardSizeY(), tempPos.x, tempPos.y, tempPos.symbol);
    MacUILib_printf("%d, %d", myGM->getBoardSizeX(), myGM->getBoardSizeY());
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
