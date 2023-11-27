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

    objPosArrayList* tempPlayerPos;
    tempPlayerPos = myPlayer->getPlayerPos();

    myGM->generateFood(tempPlayerPos);

    srand(time(NULL));
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
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    bool drawn;

    objPosArrayList* body;
    body = myPlayer->getPlayerPos();
    objPos tempBody;

    objPos tempFood;
    myGM->getFoodPos(tempFood);

    //Draw the board
    for(int i = 0; i < myGM->getBoardSizeY(); i++){
        for(int j = 0; j < myGM->getBoardSizeX(); j++){

            drawn = false;

            for(int k = 0; k < body->getSize(); k++){
                body->getElement(tempBody, i);
                if(i == tempBody.y && j == tempBody.x){
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }

            if((i == 0 || i == myGM->getBoardSizeY() - 1) || (j == 0 || j == myGM->getBoardSizeX() - 1)){
               MacUILib_printf("#");
            }else if(i == tempFood.y && j == tempFood.x){
               MacUILib_printf("%c", tempFood.symbol);
            }else{
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }
    
    //MacUILib_printf("BoardSize: %dx%d, Player Pos: <%d, %d> + %c\n", myGM->getBoardSizeX(), myGM->getBoardSizeY(), tempReturn.x, tempReturn.y, tempReturn.symbol);
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
