#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>
#include <iostream>
#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"


class Food
{
    private:
        GameMechs* mainGameMechsRef;

        objPosArrayList* foodBucket;
    
    public:
        Food(GameMechs* thisGMRef);
        ~Food();

        void generateFood(objPosArrayList* blockOff);
        objPosArrayList* getFoodPos() const;

};

#endif