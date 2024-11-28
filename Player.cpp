#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
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
        switch(input)
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
    // PPA3 Finite State Machine logic
    switch (myDir) {
        case UP:
            playerPos.pos->y--;
            if (playerPos.pos->y < 2) playerPos.pos->y = mainGameMechsRef->getBoardSizeY() - 1;
            break;
        case DOWN:
            playerPos.pos->y++;
            if (playerPos.pos->y > mainGameMechsRef->getBoardSizeY() - 3) playerPos.pos->y = 0;
            break;
        case LEFT:
            playerPos.pos->x--;
            if (playerPos.pos->x < 2) playerPos.pos->x = mainGameMechsRef->getBoardSizeX() - 1;
            break;
        case RIGHT:
            playerPos.pos->x++;
            if (playerPos.pos->x> mainGameMechsRef->getBoardSizeX() - 3) playerPos.pos->x = 0;
            break;
        default:
            break;
        

    }  
    for(int i = 1; i < playerPosList->getSize(); i++){
            objPos elementPos = playerPosList->getElement(i);
            if(playerPosList->getHeadElement().isPosEqual(&elementPos)){
                mainGameMechsRef->setExitTrue();
                mainGameMechsRef->setLoseFlag();
            }
        }

        objPos foodPos = mainGameMechsRef->getFoodPos();
        if(playerPosList->getHeadElement().isPosEqual(&foodPos)){
             playerPosList->insertHead(playerPos);
            mainGameMechsRef->incrementScore();
            mainGameMechsRef->generateFood(playerPosList);
        } else {
            playerPosList->insertHead(playerPos);
            playerPosList->removeTail();
        }       
}

// More methods to be added