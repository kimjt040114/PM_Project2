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
    
    bool Check() const;

    // Implement Home::GetAttr.
    // Default attr is REVERSE, but if this cell has an object, then OR(|) with the object's attr.
    AttrType GetAttr() const;

    // Implement Home::GetColorPair.
    // Default ColorPair is NORMAL, but if this->object is a player, then return PLAYER_NORMAL.
    ColorPair GetColorPair() const;
    
    // Implement Home::GetIcon.
    // Default icon is ' ', but if this cell has an object, then return the object's icon.
    char GetIcon() const;

};























//////////   TODO END   ////////////////////////////////////