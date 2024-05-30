#include "cellobj/Box.hpp"

Box::Box(Cell* cell) : CellObjBase(cell)
{
}

//////////     TODO     ////////////////////////////////////
// Define overrided functions from Box.hpp.

ObjectType Box::GetType() const{ 
    return ObjectType::BOX; 
}

AttrType Box::GetAttr() { 
    return AttrType::NORMAL; 
}

//////////   TODO END   ////////////////////////////////////
