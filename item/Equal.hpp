//////////     TODO     ////////////////////////////////////
// Declare your Equal class

#pragma once
#include <iostream>

#include "item/ItemBase.hpp"

class Equal : public ItemBase
{
public:
    Equal(CellObjBase* obj);

    ItemType GetType() const override;
    char GetIcon() const override;
    
private:

};





















//////////   TODO END   ////////////////////////////////////
