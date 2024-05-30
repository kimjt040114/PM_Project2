#pragma once
#include "cellobj/CellObjBase.hpp"

class Box : public CellObjBase
{
public:
    Box(Cell* cell);

    //////////     TODO     ////////////////////////////////////
    // Override virtual functions from CellObjBase.
    // You don't have to override them if you want to keep using the CellObjBase functions.

    // Implement Box::GetType that returns BOX.
    ObjectType GetType() const;

    // Implement Box::GetAttr that returns NORMAL.
    AttrType GetAttr() const;

    // Implement Box::GetIcon.
    // No default icon - return the item's icon.

    //////////   TODO END   ////////////////////////////////////
};
