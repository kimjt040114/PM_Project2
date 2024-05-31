//////////     TODO     ////////////////////////////////////
// Declare your Home class
#pragma once
#include "cell/Cell.hpp"

class Home : public Cell
{
private:
    int targetNumber;

public:
    Home(Map* map, int row, int col);
    ~Home();
    int getTargetNumber() { return targetNumber; }    
    
    bool Check();

};























//////////   TODO END   ////////////////////////////////////