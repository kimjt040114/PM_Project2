#include "Map.hpp"

#include <cmath>
#include <istream>
#include <string>
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
                    this->homes.push_back((Home*)this->cells[i][j]);
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
        std::getline(ist, col_s, '\n');
        int row = (int)row_s[0] - (int)'0';
        int col = (int)col_s[0] - (int)'0';

        this->cells[row][col]->InitObject(objType);
        if(this->cells[row][col]->GetObject() == nullptr){
            this->objects[this->cells[row][col]->GetObject()->GetType()].push_back(this->cells[row][col]->GetObject());
        }

        this->cells[row][col]->GetObject()->InitItem(itemIcon[0]);
        if(itemIcon == "="){
            (this->equals).push_back((Equal*)(this->cells[row][col]->GetObject()->GetItem()));
        }
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
        if(!h->Check()) return false;
    }

    return true;
    //////////   TODO END   ////////////////////////////////////
}

std::string evaluateExpr(std::string expr){
    if(expr.empty()) return "";

    // check the validity of expr
    if(expr[0] == '*') return "";

    int cnt = 0;
    for(cnt=0; cnt < expr.size(); cnt++){
        if(expr[cnt] == '+' || expr[cnt] == '-' || expr[cnt] == '*'){
            if(cnt == expr.size() - 1) return "";
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
    char op;
    while(expr[cnt] != '+' || expr[cnt] != '-' || expr[cnt] != '*'){
        n1 += std::pow(10, cnt) * ((int)expr[cnt] - (int)'0');
        cnt++;
        if(cnt == expr.size()) break;
    }
    expr.erase(0, cnt);
    if(negFirstNum) n1 *= -1;

    while(!expr.empty()){
        op = expr[cnt];
        expr.erase(0, 1);
        cnt=0;
        while(expr[cnt] != '+' || expr[cnt] != '-' || expr[cnt] != '*'){
            n2 += std::pow(10, cnt) * ((int)expr[cnt] - (int)'0');
            cnt++;
        }
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
    for(int i=0; i < this->equals.size(); i++){
        for(int j=i; j < this->equals.size() - 1; j++){
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
        if(result.empty()) return;

        // initialize obj, item
        Cell *cellptr = eq->parent->parent;
        for(int i=0; i < result.size(); i++){
            char ghostNum = result[i];
            cellptr = cellptr->GetNeighbor(Direction::RIGHT);
            if(cellptr != nullptr){
                if(cellptr->GetObject() == nullptr || cellptr->GetObject()->GetType() != ObjectType::GHOST){
                    cellptr->InitObject("Ghost");
                    cellptr->GetObject()->InitItem(ghostNum);
                }
                else{
                    if(ghostNum > cellptr->GetObject()->GetItem()->GetIcon()){
                        for(auto iter = this->objects[ObjectType::GHOST].begin(); 
                            iter != this->objects[ObjectType::GHOST].end(); iter++){
                            if( (*iter)->parent == cellptr ) this->objects[ObjectType::GHOST].erase(iter);
                        }
                        cellptr->InitObject("Ghost");
                        cellptr->GetObject()->InitItem(ghostNum);
                    }
                }
            }
        }

        // evaluate the up expression
        result.clear();
        result = evaluateExpr(eq->GetExpression(Direction::UP));

        // initialize obj, item
        cellptr = eq->parent->parent;
        for(int i=0; i < result.size(); i++){
            char ghostNum = result[i];
            cellptr = cellptr->GetNeighbor(Direction::DOWN);
            if(cellptr != nullptr){
                if(cellptr->GetObject() == nullptr || cellptr->GetObject()->GetType() != ObjectType::GHOST){
                    cellptr->InitObject("Ghost");
                    cellptr->GetObject()->InitItem(ghostNum);
                }
                else{
                    if(ghostNum > cellptr->GetObject()->GetItem()->GetIcon()){
                        for(auto iter = this->objects[ObjectType::GHOST].begin(); 
                            iter != this->objects[ObjectType::GHOST].end(); iter++){
                            if( (*iter)->parent == cellptr ) this->objects[ObjectType::GHOST].erase(iter);
                        }
                        cellptr->InitObject("Ghost");
                        cellptr->GetObject()->InitItem(ghostNum);
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
    

    PrintAll();
    //////////   TODO END   ////////////////////////////////////    
}
