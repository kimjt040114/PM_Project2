//////////     TODO     ////////////////////////////////////
// Implement the methods of your Equal class

#include "item/Equal.hpp"
#include "Enums.hpp"
#include "cell/Cell.hpp"

#include <algorithm>

Equal::Equal(CellObjBase* obj) : ItemBase(obj){
}


ItemType Equal::GetType() const{
    return ItemType::EQUALS;
}

char Equal::GetIcon() const{
    return '=';
}

std::string Equal::GetExpression(Direction dir){
    std::string expr;

    Cell *leftCell = this->parent->parent->GetNeighbor(dir);
    
    while(leftCell != nullptr && leftCell->GetObject() != nullptr && leftCell->GetObject()->GetItem() != nullptr &&
          leftCell->GetObject()->GetItem()->GetType() != ItemType::EQUALS)
    {
        expr.push_back(leftCell->GetIcon());
        leftCell = leftCell->GetNeighbor(dir);
    }

    std::reverse(expr.begin(), expr.end());

    return expr;
}

//////////   TODO END   ////////////////////////////////////
