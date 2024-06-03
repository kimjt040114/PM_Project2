#include "cellobj/Ghost.hpp"

Ghost::Ghost(Cell* cell) : CellObjBase(cell)
{
}

//////////     TODO     ////////////////////////////////////
// Define overrided functions from Ghost.hpp.

ObjectType Ghost::GetType() const{
    return ObjectType::GHOST; 
}

AttrType Ghost::GetAttr() const{
    return Terminal::Attr::DIM; 
}

char Ghost::GetIcon() const{
    if(this->item != nullptr){
        return this->item->GetIcon();
    }
    else{
        return ' ';
    }
}

//////////   TODO END   ////////////////////////////////////
