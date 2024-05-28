#include "item/Number.hpp"

#include <stdexcept>

Number::Number(CellObjBase* obj, int value) : ItemBase(obj), value(value)
{
    if (value < 0 || value > 9) throw std::runtime_error("Number construct error");
}

//////////     TODO     ////////////////////////////////////
// Define overrided functions from Number.hpp.



//////////   TODO END   ////////////////////////////////////
