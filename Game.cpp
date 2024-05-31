#include "Game.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <ostream>
#include "cellobj/Player.hpp"
#include "utils/Terminal.hpp"

#include "Enums.hpp"
#include "cell/Home.hpp"


Game::Game(std::string levelName)
{
    const std::string sol_ext = ".sol";
    this->levelName = levelName;  // "levels/1-sokoban.txt"
    this->solutionName = levelName + sol_ext;  // "levels/1-sokoban.txt.sol"
}


Game::~Game()
{
    //////////     TODO     ////////////////////////////////////
    // Modify destructor if you needed.

    //////////   TODO END   ////////////////////////////////////
}


/// @brief Run the game and start the event loop.
void Game::Run()
{
    Start();
    do
    {
        Update();
    } while (this->gameState != GameState::GAMEOVER);
    End();
}


/// @brief Initialize ncurses environment and load the map.
void Game::Start()
{
    Terminal::InitConsole();
    Load(this->levelName);
    gameState = GameState::PLAYING;
}


/// @brief End the ncurses environment.
void Game::End()
{
    Terminal::EndConsole();
}


/// @brief Run the event loop.
void Game::Update()
{
    Command cmd = Terminal::GetCommand();
    if (this->gameState == GameState::PLAYING)
    {
        switch (cmd)
        {
            case Command::UP:
            case Command::LEFT:
            case Command::DOWN:
            case Command::RIGHT:
                Move((Direction)((int)cmd - (int)Command::UP));
                break;
            case Command::UNDO:
                Undo();
                break;
            case Command::RESTART:
                Load(this->levelName);
                break;
            case Command::SOLVE:
                Load(this->levelName);
                StartSolve(this->solutionName);
                break;
            case Command::EXIT:
                AskExit();
                break;
            default:
                return;
        }
    }
    if (this->gameState == GameState::CLEARED)
    {
        Terminal::PrintMessage(
            "Victory!\n"
            "  q: exit\n"
            "  z: undo\n"
            "  r: restart\n"
        );
        switch (cmd)
        {
            case Command::UNDO:
                Undo();
                this->gameState = GameState::PLAYING;
                Terminal::ClearMessage();
                break;
            case Command::RESTART:
                Load(this->levelName);
                this->gameState = GameState::PLAYING;
                Terminal::ClearMessage();
                break;
            case Command::EXIT:
                this->gameState = GameState::GAMEOVER;
                return;
            default:
                return;
        }
    }
}


/// @brief Load the map from txt file. Also used for resetting the game.
/// @param filename filename of the level file
void Game::Load(std::string filename)
{
    std::ifstream ifs { filename };
    if (!ifs.is_open())
        throw std::runtime_error("Could not open the level file.");

    delete this->map;
    this->map = new Map{ this };

    int rowsize, colsize;
    ifs >> rowsize >> colsize;
    ifs.ignore();  // ignore next '\n' for getline

    this->map->Initialize(rowsize, colsize, ifs);

    // make ghosts
    this->map->SpawnGhosts();
    if (this->map->IsCleared())
        this->gameState = GameState::CLEARED;
    this->map->PrintAll();

    //////////     TODO     ////////////////////////////////////
    // Add undo-related logic if you needed.

    //////////   TODO END   ////////////////////////////////////
}


/// @brief Simulate inputs written in the solution file.
/// @param filename filename of the solution file
void Game::StartSolve(std::string filename)
{
    Terminal::PrintMessage(
        "Solving state:\n"
        "  Press any key to continue...\n"
        "  Press Q to stop.\n"
    );
    std::ifstream ifs { filename };
    if (!ifs.is_open())
        throw std::runtime_error("Could not open level file.");
    std::string line;
    std::getline(ifs, line);

    //////////     TODO     ////////////////////////////////////
    // Implement 'solving state'.
    // If every input in the line has been simulated, then the solving state ends.
    // Any keystroke except ‘Q’ will simulate the given input and will progress to next move.
    // If you press ‘Q’, then the solving state ends.
    // When the solving state ends, clear the terminal message.




    //////////   TODO END   ////////////////////////////////////
}


void Game::AskExit()
{
    Terminal::PrintMessage(
        "Wanna quit?\n"
        "  q: quit\n"
        "  z: resume\n"
    );
    //////////     TODO     ////////////////////////////////////
    // Implement 'exiting state'.
    // Press ‘Q’ again to quit the game.
    // Press ‘Z’ to resume the game and clear the terminal message.




    //////////   TODO END   ////////////////////////////////////
}


void Game::Move(Direction dir)
{
    //////////     TODO     ////////////////////////////////////
    // Implement move.
    // 1. Remove every ghost.
    // 2. Try push and move every player in the given direction.
    // 3. Spawn ghosts.
    // 4. Check if the game’s clear condition is met, and change the game state.
    // 5. Print the map.
    // 6. Push current map state to undo stack.

    this->map->RemoveGhosts();

    for(auto p : this->map->objects[ObjectType::PLAYER]){
        if(!p->TryMove(dir)) p->TryPush(dir);
    }

    this->map->SpawnGhosts();




    //////////   TODO END   ////////////////////////////////////
}


void Game::Undo()
{
    //////////     TODO     ////////////////////////////////////
    // Implement undo feature.
    // 1. Remove every ghost.
    // 2. Pop the undo stack and retrieve previous move information.
    // 3. Change each box position manually.
    // 4. Spawn ghosts.
    // 5. Check if the game’s clear condition is met, and change the game state.
    // 6. Print the map.

    //////////   TODO END   ////////////////////////////////////
}
