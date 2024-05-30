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
    return Attrtype::DIM; 
}

//////////   TODO END   ////////////////////////////////////
