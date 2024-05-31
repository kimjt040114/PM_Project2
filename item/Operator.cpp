#include "item/Operator.hpp"

Operator::Operator(CellObjBase* obj, OpType op) : ItemBase(obj), op(op){
}

//////////     TODO     ////////////////////////////////////
// Define overrided functions from Number.hpp.

ItemType Operator::GetType() const{
    return ItemType::OPERATOR;
}


char Operator::GetIcon() const{
    if(op == OpType::ADD) { return '+'; }
    else if(op == OpType::SUB) { return '-'; }
    else if(op == OpType::MUL) { return '*'; }
    else { return ' '; }
}

//////////   TODO END   ////////////////////////////////////
