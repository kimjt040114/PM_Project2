#pragma once
#include <string>

#include "item/ItemBase.hpp"

class Number : public ItemBase
{
private:
    int value = 0;

public:
    Number(CellObjBase* obj, int value);

    //////////     TODO     ////////////////////////////////////
    // Override virtual functions from ItemBase.
    // You don't have to override them if you want to keep using the ItemBase functions.

    // Implement Number::GetType that returns NUMBER.
    ItemType GetType() const override;

    // Implement Number::GetIcon.
    // Return the value in printable form.
    char GetIcon() const override;

    //////////   TODO END   ////////////////////////////////////
};
