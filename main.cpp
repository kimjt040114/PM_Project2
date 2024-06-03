#include <string>

#include "Game.hpp"

int main(int argc, char* argv[])
{
    std::string level_name = (argc > 1) ? argv[1] : "levels/1-sokoban.txt";
    Game game{ level_name };
    game.Run();
}
