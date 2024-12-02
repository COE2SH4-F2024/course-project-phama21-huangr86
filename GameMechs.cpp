#include "GameMechs.h"

GameMechs::GameMechs()
{
    //Constructor for snake game
    boardSizeX = 0;
    boardSizeY = 0;
    score = 0;
    exitFlag = false;     
    loseFlag = false;
    input = 0;
    
}

GameMechs::GameMechs(int boardX, int boardY)
{
    //Copy Constructor for snake game
    boardSizeX = boardX;
    boardSizeY = boardY;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    input = 0;

    
}


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
    exitFlag =  true; // Allows game to end
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


