#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

Player* myPlayer;
GameMechs* myGM;
Food* myFood;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


int main(void)
{
    Initialize();
    while(myGM->getExitFlagStatus() == false){
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
    myFood = new Food(myGM);
    myPlayer = new Player(myGM, myFood);

    // this means tempPlayer is a reference to the player's position arraylist's address
    // might be the most confusing 2 lines in the entire program
    // I personally think these 2 lines encorpates 3/4 of the course
    objPosArrayList& tempPlayerPos = *(myPlayer->getPlayerPos());
    myFood->generateFood(tempPlayerPos, tempPlayerPos.getSize());
}

void GetInput(void)
{
    char input = myGM->getInput();
    myGM->setInput(input);
}

void RunLogic(void)
{
    // Exit check
    if(myGM->getLoseFlag() == true || myGM->getWinFlag() == true){
        myGM->setExitTrue();
    }

    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    // Win/lose check
    if(myPlayer->checkSuicide() == true){
        myGM->setLose();
    }
    // When player occupies all the blank spaces on the board, the player wins
    int blanks = (myGM->getBoardSizeX() - 2) * (myGM->getBoardSizeY() - 2);
    if(myPlayer->getPlayerPos()->getSize() == blanks){
        myGM->setWin();
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    bool drawn;

    objPosArrayList* body;
    body = myPlayer->getPlayerPos();
    objPos tempBody;

    objPosArrayList food;
    myFood->getFoodPos(food);

    //Draw the board
    for(int i = 0; i < myGM->getBoardSizeY(); i++){
        for(int j = 0; j < myGM->getBoardSizeX(); j++){
            
            //when drawn is true, it means that the current position is already occupied by a part of the snake
            //so that we don't need to draw anything else
            drawn = false;
            for(int k = 0; k < body->getSize(); k++){
                body->getElement(tempBody, k);
                if(i == tempBody.y && j == tempBody.x){
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }

            //continued from above: otherwise there will be extra spaces drawn on the screen!
            if(drawn != true){
                bool drawSpace = true;
                if((i == 0 || i == myGM->getBoardSizeY() - 1) || (j == 0 || j == myGM->getBoardSizeX() - 1)){
                    MacUILib_printf("#");
                    drawSpace = false;
                }
                for(int k = 0; k < food.getSize(); k++){
                    // the use of tempBody might be counter intuitive here
                    // but since tempBody is already declared above with the type we need
                    // we can just reuse it here to save some memory
                    // tempBody at this point is not body, it's food
                    food.getElement(tempBody, k);
                    if(i == tempBody.y && j == tempBody.x && tempBody.y != 0){
                        MacUILib_printf("%c", tempBody.symbol);
                        drawSpace = false;
                        break;
                    }
                }
                if(drawSpace == true){
                    MacUILib_printf(" ");
                }
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Current game speed: %d s\n", DELAY_CONST/1000000);
    MacUILib_printf("Score: %d\n", myGM->getScore());
    MacUILib_printf("\n");
    MacUILib_printf("Hints:\n");
    MacUILib_printf("o increases the score and length by 1\n");
    MacUILib_printf("* increases the score by 5 without increasing length\n");
    MacUILib_printf("- decreases the length by 1 but does not increase score\n");
    MacUILib_printf("\n");
    MacUILib_printf("Press <q> to quit.\n");
    if(myGM->getLoseFlag() == true){
        MacUILib_printf("You lose!\n");
    }else if(myGM->getWinFlag() == true){
        MacUILib_printf("You win!\n");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{  
    MacUILib_uninit();
}