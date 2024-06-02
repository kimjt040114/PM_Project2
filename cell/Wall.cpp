//////////     TODO     ////////////////////////////////////
// Define overrided functions from Wall.hpp.

#include "cell/Wall.hpp"
#include "Enums.hpp"
#include "utils/Terminal.hpp"

Wall::Wall(Map* map, int row, int col) : Cell(map, row, col)
{
    this->cellType = CellType::WALL;
}

Wall::~Wall(){
}

// Implement Wall::GetAttr.
// Default attr is REVERSE, but if this cell has an object, then OR(|) with the object's attr.
AttrType Wall::GetAttr() const{
    if(this->obj != nullptr){
        return Terminal::Attr::REVERSE | this->obj->GetAttr();
    }
    else{
        return Terminal::Attr::REVERSE;
    }
}

// Implement Wall::GetColorPair.
// Default ColorPair is NORMAL, but if this->object is a player, then return PLAYER_NORMAL.
ColorPair Wall::GetColorPair() const{
    if(this->obj != nullptr && this->obj->GetType() == ObjectType::PLAYER){
        return ColorPair::PLAYER_NORMAL;
    }
    else{
        return ColorPair::NORMAL;
    }
}

// Implement Wall::GetIcon.
// Default icon is ' ', but if this cell has an object, then return the object's icon.
char Wall::GetIcon() const{
    if(this->obj != nullptr){
        return this->obj->GetIcon();
    }
    else{
        return ' ';
    }
}




//////////   TODO END   ////////////////////////////////////
