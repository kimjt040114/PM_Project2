//////////     TODO     ////////////////////////////////////
// Implement the methods of your Equal class

#include "item/Equal.hpp"


Equal::Equal(CellObjBase* obj) : ItemBase(obj){
}


ItemType Equal::GetType() const{
    return ItemType::EQUALS;
}

char Equal::GetIcon() const{
    return '=';
}




















//////////   TODO END   ////////////////////////////////////
