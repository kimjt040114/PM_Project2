//////////     TODO     ////////////////////////////////////
// Implement the methods of your Home class
#include "cell/Home.hpp"
#include "utils/Terminal.hpp"

Home::Home(Map* map, int row, int col) : Cell(map, row, col){
    this->cellType = CellType::HOME;
}

Home::~Home(){
}

// Implement Home::GetAttr.
// Default attr is UNDERLINE, but if this cell has an object, then UNDERLINE | DIM.
AttrType Home::GetAttr() const{
    if(this->obj != nullptr){
        return Terminal::Attr::UNDERLINE;
    }
    else{
        return Terminal::Attr::UNDERLINE | Terminal::Attr::DIM;
    }
}

// Implement Home::GetColorPair.
// Default ColorPair is NORMAL, but if this->object is a player, then return PLAYER_NORMAL.
ColorPair Home::GetColorPair() const{
    
}

// Implement Home::GetIcon.
// Default value is its target number (e.g., ‘5’). If this has an object, then use its icon instead.
char Home::GetIcon() const{
    if(this->obj != nullptr){
        return this->obj->GetIcon();
    }
    else{
        return (char)(this->targetNumber + (int)'0');
    }
}


















//////////   TODO END   ////////////////////////////////////