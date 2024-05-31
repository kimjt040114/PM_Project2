#pragma once
#include <iostream>

#include "item/ItemBase.hpp"

class Operator : public ItemBase
{
private:
    OpType op;

public:
    Operator(CellObjBase* obj, OpType op);
    ~Operator();
    //////////     TODO     ////////////////////////////////////
    // Override virtual functions from ItemBase.
    // You don't have to override them if you want to keep using the ItemBase functions.

    // Implement Operator::GetType that returns OPERATOR.
    ItemType GetType() const override;
     
    // Implement Operator::GetIcon.
    // Return one of the character '+', '-', '*' that matches this->op.
    char GetIcon() const override;

    //////////   TODO END   ////////////////////////////////////
};
