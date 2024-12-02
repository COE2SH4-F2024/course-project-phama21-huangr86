#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFoodRef;
    myDir = STOP;
    playerPos = objPos(15,7,'*');
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(playerPos);

    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
    
    
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray 
    return playerPosList;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
    if(input != 0)  // if not null character
         
    {
        switch(input)  //Cases for the enum, same concept as PPA3
        {                      
            case 27:
                mainGameMechsRef->setExitTrue();
                break;
            case 'w':
                if(myDir != DOWN){
                   myDir = UP;
                }
                break;
            case 's':
                if(myDir != UP){
                    myDir = DOWN;
                }
                break;  
            case 'a':
                if(myDir != RIGHT){
                    myDir = LEFT;
                }
                break;
            case 'd':
                if(myDir != LEFT){
                    myDir = RIGHT;
                }
                break; 
            default:
                break;
        }
        mainGameMechsRef->clearInput();
    }
    
}

void Player::movePlayer()
{
     int foodCollected = 0;
    // PPA3 Finite State Machine logic, same logic as PPA3
    switch (myDir) {
        case UP:
            playerPos.pos->y--;
            if (playerPos.pos->y < 1) playerPos.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
            break;
        case DOWN:
            playerPos.pos->y++;
            if (playerPos.pos->y > mainGameMechsRef->getBoardSizeY() - 2) playerPos.pos->y = 0;
            break;
        case LEFT:
            playerPos.pos->x--;
            if (playerPos.pos->x < 1) playerPos.pos->x = mainGameMechsRef->getBoardSizeX() -2;
            break;
        case RIGHT:
            playerPos.pos->x++;
            if (playerPos.pos->x> mainGameMechsRef->getBoardSizeX() - 2) playerPos.pos->x = 0;
            break;
        default:
            break;
        

    }  
    for(int i = 1; i < playerPosList->getSize(); i++){
            objPos elementPos = playerPosList->getElement(i);
            //When snake collides with its own body the user loses and game ends
            if(playerPosList->getHeadElement().isPosEqual(&elementPos)){
                mainGameMechsRef->setLoseFlag();
                
            }
        }
   
    for(int j = 0; j < mainFoodRef->getFoodPos()->getSize(); j++){
        objPos foodPos = mainFoodRef->getFoodPos()->getElement(j);
        if(playerPosList->getHeadElement().isPosEqual(&foodPos)){
            foodCollected = 1;
            if(foodPos.getSymbol() == '&'){
                playerPosList->insertHead(playerPos);
                mainGameMechsRef->incrementScore();
                mainFoodRef->generateFood(playerPosList);
                break;
            } else if(foodPos.getSymbol() == '@'){  //Special food, score increases by 10 however the snake body doesn't change
                mainGameMechsRef->incrementScore();
                mainFoodRef->generateFood(playerPosList);
                break;
            }
            
        }    
    }

    if(!foodCollected){
        //As whole snake body moves, it inputs the head in its new position whilst delete the tail
        playerPosList->insertHead(playerPos);
        playerPosList->removeTail();
        
    }
          
}

// More methods to be added