#include "cellobj/Player.hpp"

#include "Enums.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "cell/Cell.hpp"

Player::Player(Cell* cell) : CellObjBase(cell)
{
}

bool Player::TryPush(Direction dir)
{
    //////////     TODO     ////////////////////////////////////
    // Try to push other object and return if it actually pushed.
    // 1. Get a neighbor in that direction.
    // 2. If that neighbor exists, then check its cell type.
    // 3. If the neighbor is not Wall, then get its object.
    // 4. If the neighbor had an object, then try to move that object in that direction and return the result.
    // 5. If any one of 2 to 4 is false, then return false.

    Cell* neighbor = parent->GetNeighbor(dir);

    if(neighbor->cellType != CellType::WALL){
        if(neighbor->GetObject() != nullptr){
            if(neighbor->GetObject()->TryMove(dir)){
                this->TryMove(dir);
                return true;
            }
            else if(neighbor->GetObject()->GetType() == ObjectType::PLAYER){
                if(((Player*)neighbor->GetObject())->TryPush(dir)){
                    this->TryMove(dir);
                    return true;
                }
            }
        }
    }

    return false;

    //////////   TODO END   ////////////////////////////////////
}

//////////     TODO     ////////////////////////////////////
// Define overrided functions from Player.hpp.

ObjectType Player::GetType() const{ 
    return ObjectType::PLAYER; 
}

AttrType Player::GetAttr() const{ 
    return Terminal::Attr::NORMAL; 
}

char Player::GetIcon() const{
    if(this->item != nullptr){
        return this->item->GetIcon();
    }
    else{
        return ' ';
    }
}

//////////   TODO END   ////////////////////////////////////
