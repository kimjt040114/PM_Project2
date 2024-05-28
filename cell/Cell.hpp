#pragma once
#include <memory>
#include <string>

#include "Enums.hpp"
#include "cellobj/CellObjBase.hpp"
class Map;

class Cell
{
protected:
    CellObjBase* obj = nullptr;

public:
    Map* parent;
    int row, col;
    CellType cellType = CellType::CELL;

    Cell(Map* map, int row, int col);
    virtual ~Cell();

    void InitObject(const std::string& item);
    CellObjBase* GetObject() const { return this->obj; }
    void SwapObject(Cell* other);

    void Print() const;

    Cell* GetNeighbor(Direction dir) const;

    virtual AttrType GetAttr() const;
    virtual ColorPair GetColorPair() const;
    virtual char GetIcon() const;
};
