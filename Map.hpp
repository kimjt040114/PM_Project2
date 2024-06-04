#pragma once
#include <vector>
#include <map>

#include "cell/Cell.hpp"
#include "cellobj/Ghost.hpp"
#include "item/Equal.hpp"
#include "cell/Home.hpp"
class Game;

class Map
{
public:
    Game* parent;
private:
    bool initialized;
    std::vector<std::vector<Cell*>> cells;
public:
    std::map<ObjectType, std::vector<CellObjBase*>> objects;
    std::vector<Cell*> homes;
    std::vector<Equal*> equals;

    Map(Game* game);
    ~Map();
    void Initialize(int rowsize, int colsize, std::istream& ist);

    Cell* GetCell(int row, int col) const { return cells[row][col]; }
    int GetRowsize() const { return cells.size(); }
    int GetColsize() const { return cells[0].size(); }
    bool IsInitialized() const { return initialized; }

    void PrintAll() const;
    void PrintCell(int row, int col) const;

    bool IsCleared() const;

    void SpawnGhosts();
    void RemoveGhosts();

    void ClearObjects();

    std::vector<std::string> GetObjInfo();
};
