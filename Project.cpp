#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"

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
   
    game = new GameMechs(WIDTH,HEIGHT);
    player = new Player(game);
    game->generateFood(player->getPlayerPos());
   

}

void GetInput(void)
{
    if(MacUILib_hasChar() == 1){
        game->setInput(MacUILib_getChar());
    }
    
   
}

void RunLogic(void)
{

    player->updatePlayerDir();
    player->movePlayer();
    
   
    
    
}

void DrawScreen(void)
{
    int i,j,size;
    objPosArrayList* playerPosList = player->getPlayerPos();
    size = playerPosList->getSize();
    MacUILib_clearScreen(); 
    for (i = 0; i < HEIGHT; i++ ){
        for (j = 0; j < WIDTH; j++){
            int itemFound = 0;
            if(i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1){
                    MacUILib_printf("#");
            
            } else {
                for(int k = 0; k < size; k++){
                    objPos playerPosition = playerPosList->getElement(k);
                     if (i == playerPosition.pos->y && j == playerPosition.pos->x ){
                        MacUILib_printf("%c",playerPosition.getSymbol());
                        itemFound = 1;
                        break;
                     }
                }
                if (!itemFound && game->getFoodPos().pos->x == j && game->getFoodPos().pos->y == i){
                        MacUILib_printf("%c",game->getFoodPos().getSymbol());
                }
                else if (!itemFound){
                    MacUILib_printf(" ");
                }
            
            }
                            
        }
        MacUILib_printf("\n");
        
    }
    MacUILib_printf("Score: %d", game->getScore());

    if(game->getLoseFlagStatus()){
        MacUILib_printf("You Fucking Suck\n");
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
    delete game;
}
