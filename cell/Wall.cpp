//////////     TODO     ////////////////////////////////////
// Define overrided functions from Wall.hpp.

#include "cell/Wall.hpp"

Wall::Wall(Map* map, int row, int col) : Cell(map, row, col)
{
    this->cellType = CellType::WALL;
}




//////////   TODO END   ////////////////////////////////////
