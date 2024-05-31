#include "Map.hpp"

#include <istream>
#include "utils/Terminal.hpp"

#include "cell/Cell.hpp"
#include "cell/Home.hpp"
#include "cell/Wall.hpp"
#include "cellobj/CellObjBase.hpp"


Map::Map(Game* game) : parent(game), initialized(false)
{
    this->objects[ObjectType::BOX] = std::vector<CellObjBase*>();
    this->objects[ObjectType::PLAYER] = std::vector<CellObjBase*>();
    this->objects[ObjectType::GHOST] = std::vector<CellObjBase*>();
}


Map::~Map()
{
    //////////     TODO     ////////////////////////////////////
    // Modify destructor if you needed.

    //////////   TODO END   ////////////////////////////////////
}


/// @brief Initialize this map (only if this has not been initialized yet).
/// @param rowsize number of rows of the level
/// @param colsize number of columns of the level
/// @param ist istream that contains the level information string
/// @note The usage of 'ist' is similar to that of std::cin, since they both inherit std::istream.
void Map::Initialize(int rowsize, int colsize, std::istream& ist)
{
    if (this->initialized) return;
    this->cells.resize(rowsize);

    std::string line;
    //////////     TODO     ////////////////////////////////////
    // 1. Read cell map and construct each cell.
    // 2. Initialize each object and its item.

    for(int i=0; i < rowsize; i++){
        std::getline(ist, line);
        for(int j=0; j < line.length(); j++){
            char c = line[j];
            switch (c){
                case '#':
                    this->cells[i].push_back(new Wall(this, i, j));
                    break;
                case ' ':
                    this->cells[i][j] = new Cell(this, i, j);
                    break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    this->cells[i][j] = new Home(this, i, j);
                    this->homes.push_back(this->cells[i][j]);
                    break;
            }
        }
        for(int j=line.length(); j < colsize; j++) { this->cells[i][j]; }
    }
    
    std::getline(ist, line);
    int numObj = (int)line[0] - (int)'0';

    for(int i=0; i < numObj; i++){
        std::string objType;
        std::string itemIcon;
        std::string row_s, col_s;

        std::getline(ist, objType, ' ');

        std::getline(ist, itemIcon, ' ');

        std::getline(ist, row_s, ' ');
        std::getline(ist, col_s, ' ');
        int row = (int)row_s[0] - (int)'0';
        int col = (int)col_s[0] - (int)'0';

        this->cells[row][col]->InitObject(objType);

        this->cells[row][col]->GetObject()->InitItem(itemIcon[0]);
    }
    


    




    //////////   TODO END   ////////////////////////////////////
    this->initialized = true;
}


void Map::PrintAll() const
{
    int rowsize = this->GetRowsize();
    int colsize = this->GetColsize();
    for (int r = 0; r < rowsize; r++)
    {
        for (int c = 0; c < colsize; c++)
        {
            this->PrintCell(r, c);
        }
    }
}


void Map::PrintCell(int row, int col) const
{
    this->cells[row][col]->Print();
}


bool Map::IsCleared() const
{
    //////////     TODO     ////////////////////////////////////
    // Check if every home has the correct number.



    //////////   TODO END   ////////////////////////////////////
}


/// @brief Spawn every ghosts with the correct order.
void Map::SpawnGhosts()
{
    //////////     TODO     ////////////////////////////////////
    // Sort this->equals to match spawning order.
    // For every equal, evaluate left/upper expression, get result string, and spawn ghosts.





    //////////   TODO END   ////////////////////////////////////
}


/// @brief Remove every ghosts.
void Map::RemoveGhosts()
{
    //////////     TODO     ////////////////////////////////////
    // Remove every ghosts and clear this->objects[GHOST].



    //////////   TODO END   ////////////////////////////////////    
}
