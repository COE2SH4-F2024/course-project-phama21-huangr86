#include "GameMechs.h"

GameMechs::GameMechs()
{
    boardSizeX = 0;
    boardSizeY = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    input = 0;
    foodPos = objPos(0,0,'@');
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    input = 0;
    foodPos = objPos(0,0,'@');
    
}

// do you need a destructor?
GameMechs :: ~GameMechs(){
    
}
bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score+= 10;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag =  true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here
void GameMechs:: generateFood(objPosArrayList* blockOff){
    int i, flag;
    
     do{
        flag = 1;
        foodPos.pos->x = rand() % (boardSizeX - 2) + 1;
        foodPos.pos->y = rand() % (boardSizeY - 2) + 1;
        
        for(int i = 0 ; i < blockOff->getSize(); i++){
            if (foodPos.pos->x  == blockOff->getElement(i).pos->x && foodPos.pos->y == blockOff->getElement(i).pos->y){
            flag = 0;
        }
        }
        

    } while(!flag);
}

objPos GameMechs:: getFoodPos() const{
    return foodPos;
}