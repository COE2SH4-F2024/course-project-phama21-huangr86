#include "Food.h"

Food::Food(GameMechs* thisGMRef){
    mainGameMechsRef = thisGMRef;
    foodBucket = new objPosArrayList();
}

void Food:: generateFood(objPosArrayList* blockOff){
    int i,j,k, flag, itemPlaced = 0;
    bool check;
    int randX = 0, randY = 0;

    for(k = foodBucket->getSize(); k > 0 ;k--){
            foodBucket->removeTail();
    }
    

    while(itemPlaced < 5){
        check = itemPlaced < 2;

        
        do{
            flag = 1;
            randX = rand() % (mainGameMechsRef->getBoardSizeX() - 2) + 1;
            randY = rand() % (mainGameMechsRef->getBoardSizeY()- 2) + 1;
        
            for(i = 0 ; i < blockOff->getSize(); i++){
                if (blockOff->getElement(i).pos->x == randX && blockOff->getElement(i).pos->y == randY){
                    flag = 0;
                    break;
                }
            }

            for(j = 0; j < itemPlaced; j++){
                if(foodBucket->getElement(j).pos->x == randX && foodBucket->getElement(j).pos->y == randY){
                    flag = 0;
                    break;
                }
            }
        
        } while(!flag);

        
        foodBucket->insertHead(objPos(randX,randY, check ? '@' : '&'));
        itemPlaced++;
        
    }
     
}

objPosArrayList* Food::getFoodPos() const{
    return foodBucket;
}

Food::~Food() {
    delete foodBucket;
}
