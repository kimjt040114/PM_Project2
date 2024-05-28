#pragma once
#include <string>
#include "Enums.hpp"

using AttrType = unsigned int;

class Terminal
{
public:
    class Attr
    {
    public:
        static AttrType NORMAL;
        static AttrType UNDERLINE;
        static AttrType REVERSE;
        static AttrType DIM;
    };

    static void InitConsole();
    static void EndConsole();

    static void PrintIconAt(int row, int col, char icon, AttrType attr, ColorPair color);
    static void PrintAt(int row, int col, std::string str, AttrType attr = Attr::NORMAL, ColorPair color = ColorPair::NORMAL);

    static void PrintMessage(std::string msg);
    static void ClearMessage();

    static char GetCh();
    static Command GetCommand();
};
