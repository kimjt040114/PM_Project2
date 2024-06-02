//////////     TODO     ////////////////////////////////////
// Implement the methods of your Home class
#include "cell/Home.hpp"
#include "Enums.hpp"
#include "utils/Terminal.hpp"

Home::Home(Map* map, int row, int col) : Cell(map, row, col){
    this->cellType = CellType::HOME;
}

Home::~Home(){
}

bool Home::Check() const{
    if(this->obj != nullptr && this->obj->GetItem() != nullptr && this->obj->GetItem()->GetType() == ItemType::NUMBER){
        if(targetNumber == int(this->obj->GetItem()->GetIcon()) - int('0')){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
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
ColorPair Home::GetColorPair() const{
    if(this->obj != nullptr){
        if(this->Check()){
            if(this->obj->GetType() == ObjectType::PLAYER){
                return ColorPair::PLAYER_CORRECT;
            }
            else{
                return ColorPair::CORRECT;
            }
        }
        else{
            if(this->obj->GetType() == ObjectType::PLAYER){
                return ColorPair::PLAYER_WRONG;
            }
            else{
                return ColorPair::WRONG;
            }
        }
    }
    else{
        return ColorPair::NORMAL;
    }
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