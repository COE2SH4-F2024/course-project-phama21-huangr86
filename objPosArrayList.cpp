#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;

}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    

    for(int i = listSize; i  > 0; i--){
        aList[i] = aList[i - 1];  //Shifts items in the array back so new head doesnt overwrite over values
    }

    aList[0] = thisPos;
    listSize++;
    
}

void objPosArrayList::insertTail(objPos thisPos)
{
    aList[listSize] = thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
    for(int i = 0 ; i < listSize- 1; i++){
        aList[i] = aList[i + 1]; // Shifts item foward in the array as head gets removed
    }
    listSize--;
    
}

void objPosArrayList::removeTail()
{
    aList[listSize] = aList[listSize + 1];
    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    return aList[index];
}
