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

    if(this->obj != nullptr){
        delete this->obj;
    }
    //I love you
    if(objType == "Box"){
        this->obj = new Box(this);
        parent->objects[ObjectType::BOX].push_back(this->obj);
    }
    else if(objType == "Player"){
        this->obj = new Player(this);
        parent->objects[ObjectType::PLAYER].push_back(this->obj);
    }

    //////////   TODO END   ////////////////////////////////////
}

void Cell::SwapObject(Cell* other)
{
    //////////     TODO     ////////////////////////////////////
    // Implement object swapping.
    // 1. If this->obj exists: change parent of this->obj.
    // 2. If other->obj exists: change parent of other->obj.
    // 3. Swap this->obj and other->obj.

    if(this->obj != nullptr) this->obj->parent = other; 
    
    if(other->obj != nullptr) other->obj->parent = this;

    CellObjBase* tempObj = this->obj;

    this->obj = other->obj;

    other->obj = tempObj;

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

    if(this->obj != nullptr){
        return this->obj->GetAttr() | Terminal::Attr::NORMAL;
    }
    else{
        return Terminal::Attr::NORMAL;
    }
    //////////   TODO END   ////////////////////////////////////
}

ColorPair Cell::GetColorPair() const
{
    //////////     TODO     ////////////////////////////////////
    // Implement Cell::GetColorPair.
    // Default ColorPair is NORMAL, but if this->object is a player, then return PLAYER_NORMAL.
    if(this->obj != nullptr && this->obj->GetType() == ObjectType::PLAYER) {
        return ColorPair::PLAYER_NORMAL;
    }
    else{
        return ColorPair::NORMAL;
    }

    //////////   TODO END   ////////////////////////////////////
}

char Cell::GetIcon() const
{
    //////////     TODO     ////////////////////////////////////
    // Implement Cell::GetIcon.
    // Default icon is ' ', but if this cell has an object, then return the object's icon.

    if(this->obj == nullptr){
        return ' ';
    }
    else{
        return this->obj->GetIcon();
    }

    //////////   TODO END   ////////////////////////////////////
}

Cell* Cell::GetNeighbor(Direction dir) const
{
    //////////     TODO     ////////////////////////////////////
    // Get neighbor of that direction.
    // If the cell is placed at the border of the map and the direction is outside the map, return nullptr.
    // Else return the neighbor cell.

    if(dir == Direction::UP){
        if(row == 0) return nullptr;
        else return parent->GetCell(row-1, col);
    }

    if(dir == Direction::DOWN){
        if(row == parent->GetRowsize()) return nullptr;
        else return parent->GetCell(row+1, col);
    }
    if(dir == Direction::LEFT){
        if(col == 0) return nullptr;
        else return parent->GetCell(row, col-1);
    }
    if(dir == Direction::RIGHT){
        if(col == parent->GetColsize()) return nullptr;
        else return parent->GetCell(row, col+1);
    }

    return nullptr;

    //////////   TODO END   ////////////////////////////////////
}
