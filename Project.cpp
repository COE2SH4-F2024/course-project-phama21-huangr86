#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000
#define HEIGHT 15
#define WIDTH 30


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

GameMechs* game; 
Player* player;
Food* food;




int main(void)
{

    Initialize();

    while(!game->getExitFlagStatus())  
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
   
    game = new GameMechs(WIDTH,HEIGHT); //Allocating dynamic memory
    food = new Food(game);
    player = new Player(game, food);
    food->generateFood(player->getPlayerPos());

   

}

void GetInput(void)
{
    if(MacUILib_hasChar() == 1){
        game->setInput(MacUILib_getChar());//Allows user to interact with keyboard to move the snake
    }
    
   
}

void RunLogic(void)
{

    player->updatePlayerDir(); //Runs functions from player.cpp to determine the direction then moving the player
    player->movePlayer();
    
    
}

void DrawScreen(void)
{
    int i,j,k,l,size;
    objPosArrayList* playerPosList = player->getPlayerPos(); //Creates a new Arraylist for the snake body
    size = playerPosList->getSize();
    MacUILib_clearScreen(); 
    //Display lose status
    if(!game->getLoseFlagStatus()){
        for (i = 0; i < HEIGHT; i++ ){
            for (j = 0; j < WIDTH; j++){
                int itemFound = 0;
                if(i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1){
                        MacUILib_printf("#");
                
                } else {
                    //Draws all food items on the display board
                    for(l = 0; l < food->getFoodPos()->getSize();l++){
                        if (food->getFoodPos()->getElement(l).pos->x == j && food->getFoodPos()->getElement(l).pos->y == i){
                                MacUILib_printf("%c",food->getFoodPos()->getElement(l).getSymbol());
                                itemFound = 1;
                                break;
                        }
                    }
                    if(!itemFound){
                        //Draws position of player on the board
                        for(k = 0; k < size; k++){
                            objPos playerPosition = playerPosList->getElement(k);
                            if (i == playerPosition.pos->y && j == playerPosition.pos->x ){
                                MacUILib_printf("%c",playerPosition.getSymbol());
                                itemFound = 1;
                                break;  
                            }
                    }
                    } 
                    if(!itemFound) {
                        //Draws the rest of the board/empty spaces
                        MacUILib_printf(" ");
                    }
                }                   
            }
            MacUILib_printf("\n");
    }
    MacUILib_printf("Score: %d", game->getScore());   
    MacUILib_printf("\n& increases score by 10 and length by 1");
    MacUILib_printf("\n@ only increases score by 10");
    } else {
        MacUILib_printf("Oh No GoodLuck Next Time\n");
        MacUILib_printf("Score: %d", game->getScore());
    }
   
    

    

    
       
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    MacUILib_uninit();

    //Deallocating memory
    delete game;
    delete food;
    delete player;
}
