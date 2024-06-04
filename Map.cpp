#include "Map.hpp"

#include <cmath>
#include <istream>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include "Enums.hpp"
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
        for(unsigned int j=0; j < line.length(); j++){
            char c = line[j];
            switch (c){
                case '#':
                    this->cells[i].push_back(new Wall(this, i, j));
                    break;
                case ' ':
                    this->cells[i].push_back(new Cell(this, i, j));
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
                    this->cells[i].push_back(new Home(this, i, j, c));
                    this->homes.push_back(this->cells[i][j]);
                    break;
            }
        }
        for(int j=line.length(); j < colsize; j++) { this->cells[i][j]; }
    }
    
    std::getline(ist, line);
    int numObj = std::stoi(line);

    for(int i=0; i < numObj; i++){
        std::string objType;
        std::string itemIcon;
        std::string row_s, col_s;

        std::getline(ist, objType, ' ');

        std::getline(ist, itemIcon, ' ');

        std::getline(ist, row_s, ' ');
        std::getline(ist, col_s, '\n');
        int row = std::stoi(row_s);
        int col = std::stoi(col_s);

        this->cells[row][col]->InitObject(objType);
        if(this->cells[row][col]->GetObject() == nullptr){
            this->objects[this->cells[row][col]->GetObject()->GetType()].push_back(this->cells[row][col]->GetObject());
        }

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
    for(auto h : this->homes){
        if(!((Home*)h)->Check()) return false;
    }

    return true;
    //////////   TODO END   ////////////////////////////////////
}

std::string evaluateExpr(std::string expr){
    if(expr.empty()) return "";

    // check the validity of expr
    if(expr[0] == '*') return "";

    int cnt = 0;
    for(cnt=0; cnt < (int)expr.size(); cnt++){
        if(expr[cnt] == '+' || expr[cnt] == '-' || expr[cnt] == '*'){
            if(cnt == (int)expr.size() - 1) return "";
            else if(expr[cnt+1] == '+' || expr[cnt+1] == '-' || expr[cnt+1] == '*') return "";
        }
    }

    // trim
    bool negFirstNum = false;
    if(expr[0] == '-') {
        expr.erase(0, 1); 
        negFirstNum = true;
    }
    else if(expr[0] == '+') {
        expr.erase(0, 1);
    }

    // evaluate
    cnt=0;
    int n1=0, n2=0;
    std::string n1_s(""), n2_s("");
    
    char op;
    while(expr[cnt] != '+' && expr[cnt] != '-' && expr[cnt] != '*'){
        n1_s.push_back(expr[cnt]);
        cnt++;
        if(cnt == (int)expr.size()) break;
    }
    n1 = std::stoi(n1_s);

    expr.erase(0, cnt);
    if(negFirstNum) n1 *= -1;

    while(!expr.empty()){
        op = expr[0];
        expr.erase(0, 1);
        cnt=0, n2=0;
        n2_s.clear();
        while(expr[cnt] != '+' && expr[cnt] != '-' && expr[cnt] != '*'){
            n2_s.push_back(expr[cnt]);
            cnt++;
            if(cnt == (int)expr.size()) break;
        }
        n2 = std::stoi(n2_s);

        expr.erase(0, cnt);

        switch (op){
            case '+':
                n1 += n2;
                break;
            case '-':
                n1 -= n2;
                break;
            case '*':
                n1 *= n2;
                break;
        }
    }
    std::string result = std::to_string(n1);
    return result;
}

/// @brief Spawn every ghosts with the correct order.
void Map::SpawnGhosts()
{
    //////////     TODO     ////////////////////////////////////
    // Sort this->equals to match spawning order.
    // For every equal, evaluate left/upper expression, get result string, and spawn ghosts.

    // Sorting equals.
    for(int i=0; i < (int)this->equals.size(); i++){
        for(int j=i; j < (int)this->equals.size() - 1; j++){
            if(this->equals[j]->parent->parent->row > this->equals[j+1]->parent->parent->row ||
                (this->equals[j]->parent->parent->row == this->equals[j+1]->parent->parent->row &&
                this->equals[j]->parent->parent->col > this->equals[j+1]->parent->parent->col))
            {
                Equal* temp = this->equals[j+1];
                this->equals[j+1] = this->equals[j];
                this->equals[j] = temp;
            }
        }
    }
    
    for(auto eq : this->equals){
        // evaluate the left expression
        std::string result = evaluateExpr(eq->GetExpression(Direction::LEFT));
        if(!result.empty()){
            // initialize obj, item
            Cell *cellptr = eq->parent->parent;
            for(int i=0; i < (int)result.size(); i++){
                char ghostNum = result[i];
                cellptr = cellptr->GetNeighbor(Direction::RIGHT);
                if(cellptr != nullptr){
                    if(cellptr->GetObject() == nullptr){
                        cellptr->InitObject("Ghost");
                        cellptr->GetObject()->InitItem(ghostNum);
                    }
                    else if(cellptr->GetObject()->GetType() == ObjectType::GHOST){
                        if(ghostNum > cellptr->GetObject()->GetItem()->GetIcon()){
                            auto i = std::find(this->objects[ObjectType::GHOST].begin(), this->objects[ObjectType::GHOST].end(), cellptr->GetObject());
                            this->objects[ObjectType::GHOST].erase(i);
                            cellptr->InitObject("Ghost");
                            cellptr->GetObject()->InitItem(ghostNum);
                        }
                    }
                }
            }
        }

        // evaluate the up expression
        result.clear();
        result = evaluateExpr(eq->GetExpression(Direction::UP));


        if(!result.empty()){    
            // initialize obj, item
            Cell *cellptr = eq->parent->parent;
            for(int i=0; i < (int)result.size(); i++){
                char ghostNum = result[i];
                cellptr = cellptr->GetNeighbor(Direction::DOWN);
                if(cellptr != nullptr){
                    if(cellptr->GetObject() == nullptr){
                        cellptr->InitObject("Ghost");
                        cellptr->GetObject()->InitItem(ghostNum);
                    }
                    else if(cellptr->GetObject()->GetType() == ObjectType::GHOST){
                        if(ghostNum > cellptr->GetObject()->GetItem()->GetIcon()){
                            std::vector<CellObjBase*> ghosts = this->objects[ObjectType::GHOST];
                            auto i = std::find(this->objects[ObjectType::GHOST].begin(), this->objects[ObjectType::GHOST].end(), cellptr->GetObject());
                            this->objects[ObjectType::GHOST].erase(i);
                            cellptr->InitObject("Ghost");
                            cellptr->GetObject()->InitItem(ghostNum);
                        }
                    }
                }
            }
        }

        
    }

    PrintAll();

    //////////   TODO END   ////////////////////////////////////
}


/// @brief Remove every ghosts.
void Map::RemoveGhosts()
{
    //////////     TODO     ////////////////////////////////////
    // Remove every ghosts and clear this->objects[GHOST].
    std::vector<CellObjBase*> ghosts = this->objects[ObjectType::GHOST];
    for(auto& g: ghosts){
        g->parent->InitObject("");
    }

    this->objects[ObjectType::GHOST].clear();

    //////////   TODO END   ////////////////////////////////////    
}

void Map::ClearObjects(){
    for(int i=0; i < GetRowsize(); i++){
        for(int j=0; j < GetColsize(); j++){
            this->cells[i][j]->InitObject("");
        }
    }

    this->objects[ObjectType::BOX].clear();
    this->objects[ObjectType::PLAYER].clear();
    this->objects[ObjectType::GHOST].clear();
    this->equals.clear();
}

std::vector<std::string> Map::GetObjInfo(){
    std::vector<std::string> objInfo;
    std::string objInfo_s;
    
    for(int i=0; i < GetRowsize(); i++){
        for(int j=0; j < GetColsize(); j++){
            if(cells[i][j]->GetObject() != nullptr){
                if(cells[i][j]->GetObject()->GetType() == ObjectType::BOX){
                    objInfo_s.append("Box ");
                    objInfo_s.push_back(cells[i][j]->GetObject()->GetIcon());
                    objInfo_s.append(" "+std::to_string(i)+" "+std::to_string(j));
                }
                else if(cells[i][j]->GetObject()->GetType() == ObjectType::PLAYER){
                    objInfo_s.append("Player ");
                    objInfo_s.push_back(cells[i][j]->GetObject()->GetIcon());
                    objInfo_s.append(" "+std::to_string(i)+" "+std::to_string(j));
                }
                objInfo.push_back(objInfo_s);
                objInfo_s.clear();
            }
        }
    }

    return objInfo;
}

