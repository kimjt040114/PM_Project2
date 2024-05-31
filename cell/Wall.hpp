#pragma once
#include "cell/Cell.hpp"

class Wall : public Cell
{
public:
    Wall(Map* map, int row, int col);
    ~Wall();
    //////////     TODO     ////////////////////////////////////
    // Override virtual functions from Cell.
    // You don't have to override them if you want to keep using the Cell functions.

    // Implement Wall::GetAttr.
    // Default attr is REVERSE, but if this cell has an object, then OR(|) with the object's attr.
    
    // Implement Wall::GetColorPair.
    // Default ColorPair is NORMAL, but if this->object is a player, then return PLAYER_NORMAL.

    // Implement Cell::GetIcon.
    // Default icon is ' ', but if this cell has an object, then return the object's icon.

    //////////   TODO END   ////////////////////////////////////
};
