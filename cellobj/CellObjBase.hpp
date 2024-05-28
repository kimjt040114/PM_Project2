#pragma once
#include <string>
#include <memory>

#include "Enums.hpp"
#include "item/ItemBase.hpp"
#include "utils/Terminal.hpp"
class Cell;

class CellObjBase
{
protected:
    ItemBase* item = nullptr;

public:
    Cell* parent;

    CellObjBase(Cell* cell);
    virtual ~CellObjBase();

    void InitItem(char itemIcon);
    ItemBase* GetItem() const { return this->item; }

    bool TryMove(Direction dir);

    
    //////////     TODO     ////////////////////////////////////
    // Optional: if you wish, you can implement some of these functions
    // in this virtual class, and change them into non-pure virtual functions.

    virtual ObjectType GetType() const = 0;
    virtual AttrType GetAttr() const = 0;
    virtual char GetIcon() const = 0;

    //////////   TODO END   ////////////////////////////////////
};
