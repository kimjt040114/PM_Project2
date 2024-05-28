#include "cell/Cell.hpp"

#include <string>
#include "utils/Terminal.hpp"

#include "Map.hpp"
#include "cellobj/Box.hpp"
#include "cellobj/Player.hpp"


Cell::Cell(Map* map, int row, int col) : parent(map), row(row), col(col)
{
    this->cellType = CellType::CELL;
}

Cell::~Cell()
{
    //////////     TODO     ////////////////////////////////////
    // Modify destructor if you needed.

    //////////   TODO END   ////////////////////////////////////
}

void Cell::InitObject(const std::string& objType)
{
    //////////     TODO     ////////////////////////////////////
    // Initialize object.
    // 1. Delete existing object.
    // 2. Check objType and make corresponding object.
    // 3. push_back the object to the corresponding map->objects[].

    delete this->obj;

    if(objType == ObjectType::BOX){
        
    }
    this->obj = new CellObjBase(this);

    parent->objects[]
    

    //////////   TODO END   ////////////////////////////////////
}

void Cell::SwapObject(Cell* other)
{
    //////////     TODO     ////////////////////////////////////
    // Implement object swapping.
    // 1. If this->obj exists: change parent of this->obj.
    // 2. If other->obj exists: change parent of other->obj.
    // 3. Swap this->obj and other->obj.

    

    //////////   TODO END   ////////////////////////////////////
}

void Cell::Print() const
{
    Terminal::PrintIconAt(row, col, this->GetIcon(), this->GetAttr(), this->GetColorPair());
}

AttrType Cell::GetAttr() const
{
    //////////     TODO     ////////////////////////////////////
    // Implement Cell::GetAttr.
    // Default attr is NORMAL, but if this cell has an object, then OR(|) with the object's attr.



    //////////   TODO END   ////////////////////////////////////
}

ColorPair Cell::GetColorPair() const
{
    //////////     TODO     ////////////////////////////////////
    // Implement Cell::GetColorPair.
    // Default ColorPair is NORMAL, but if this->object is a player, then return PLAYER_NORMAL.



    //////////   TODO END   ////////////////////////////////////
}

char Cell::GetIcon() const
{
    //////////     TODO     ////////////////////////////////////
    // Implement Cell::GetIcon.
    // Default icon is ' ', but if this cell has an object, then return the object's icon.



    //////////   TODO END   ////////////////////////////////////
}

Cell* Cell::GetNeighbor(Direction dir) const
{
    //////////     TODO     ////////////////////////////////////
    // Get neighbor of that direction.
    // If the cell is placed at the border of the map and the direction is outside the map, return nullptr.
    // Else return the neighbor cell.







    //////////   TODO END   ////////////////////////////////////
}
