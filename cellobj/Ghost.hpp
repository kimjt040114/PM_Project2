#pragma once
#include "cellobj/CellObjBase.hpp"

class Ghost : public CellObjBase
{
public:
    Ghost(Cell* cell);

    //////////     TODO     ////////////////////////////////////
    // Override virtual functions from CellObjBase.
    // You don't have to override them if you want to keep using the CellObjBase functions.

    // Implement Ghost::GetType that returns GHOST.
    ObjectType GetType() const override;

    // Implement Ghost::GetAttr that returns DIM.
    AttrType GetAttr() const override;

    // Implement Ghost::GetIcon.
    // No default icon - return the item's icon.
    char GetIcon() const override;
    //////////   TODO END   ////////////////////////////////////
};
