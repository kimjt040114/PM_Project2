#pragma once
#include <memory>
#include <deque>
#include <stack>

#include "Map.hpp"
#include "Enums.hpp"
#include "cellobj/Player.hpp"

class Game
{
private:
    std::stack<std::vector<std::string>> undoStack;

    Map* map = nullptr;

    std::string levelName;
    std::string solutionName;

    void Start();
    void Update();
    void End();

    void Load(std::string filename);
    void StartSolve(std::string filename);
    void AskExit();

    void Move(Direction dir);
    void Undo();

public:
    GameState gameState = GameState::GAMEOVER;
    
    Game(std::string levelName);
    ~Game();

    void Run();
};
