#include "cellobj/CellObjBase.hpp"

#include "CellObjBase.hpp"
#include "Enums.hpp"
#include "Map.hpp"
#include "cellobj/Player.hpp"
#include "cell/Cell.hpp"
#include "item/Number.hpp"
#include "item/Operator.hpp"
#include "item/Equal.hpp"
#include <cstddef>

CellObjBase::CellObjBase(Cell* cell) : parent(cell)
{
}

CellObjBase::~CellObjBase()
{
    //////////     TODO     ////////////////////////////////////
    // Modify destructor if you needed.
    delete this->item;
    this->item = nullptr;
    //////////   TODO END   ////////////////////////////////////
}

bool CellObjBase::TryMove(Direction dir)
{
    //////////     TODO     ////////////////////////////////////
    // Try to move and return if it actually moved.
    // 1. Get a neighbor in that direction
    // 2. If that neighbor exists, then check its cell type
    // 3. If the neighbor is not Wall, then get its object
    // 4. If the neighbor didn’t have any object, then
    //    swap between the neighbor and return true
    // 5. If any one of 2 to 4 is false, then return false

    Cell* neighbor = parent->GetNeighbor(dir);
    
    if(neighbor != nullptr){
        if(neighbor->cellType != CellType::WALL){
            if(neighbor->GetObject() == nullptr){
                parent->SwapObject(neighbor);
                return true;
            }

            // for the case that 'this' is player. it can push, not only just move.
            // !! should check whether it works well !!
            // if(this->GetType() == ObjectType::PLAYER) ((Player*)this)->TryPush(dir);
        }
    }

    return false;

    //////////   TODO END   ////////////////////////////////////
}


void CellObjBase::InitItem(char itemIcon)
{
    //////////     TODO     ////////////////////////////////////
    // Create this->item.
    // itemIcon == ‘+’: Create ADD operator.
    // itemIcon == ‘-’: Create SUB operator.
    // itemIcon == ‘*’: Create MUL operator.
    // itemIcon == ‘=‘: Create equal, then push back into map->equals.
    // ‘0’ <= itemIcon <= ‘9’: Create the corresponding number.
    // ‘@’: Do nothing (this indicates an empty player).
    // else: Don’t care (throwing runtime_error is best).

    if(itemIcon == '+'){
        ItemBase* newItem = new Operator(this, OpType::ADD);
        this->item = newItem;
    }

    else if(itemIcon == '-'){
        ItemBase* newItem = new Operator(this, OpType::SUB);
        this->item = newItem;
    }

    else if(itemIcon == '*'){
        ItemBase* newItem = new Operator(this, OpType::MUL);
        this->item = newItem;
    }
    
    else if(itemIcon == '='){ 
        ItemBase* newItem = new Equal(this); 
        this->item = newItem;
    }
    else if('0' <= itemIcon && itemIcon <= '9'){ 
        ItemBase* newItem = new Number(this, (int(itemIcon) - int('0'))); 
        this->item = newItem;
    }


    //////////   TODO END   ////////////////////////////////////
}
