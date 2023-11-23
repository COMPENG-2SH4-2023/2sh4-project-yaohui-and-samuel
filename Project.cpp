#include <iostream>
#include "MacUILib.h"
#include "objPos.h"


using namespace std;

#define DELAY_CONST 100000
#define ROW 10
#define COL 20

Player* myPlayer;
GameMechs* myGM;

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


int main(void)
{

    Initialize();

    while(exitFlag == false)  
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

    myGM = new GameMechs(20, 10);
    myPlayer = new Player(myGM);

    

    exitFlag = false;
}

void GetInput(void)
{
    char input = MacUILib_getChar();
    mech.setInput(input);
    
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

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
