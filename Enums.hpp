#pragma once

enum class GameState
{
    PLAYING,
    CLEARED,
    GAMEOVER,
};

enum class CellType
{
    CELL,
    HOME,
    WALL,
};

enum class Direction
{
    UP,
    LEFT,
    DOWN,
    RIGHT,
};

enum class Command
{
    NONE,
    UP,
    LEFT,
    DOWN,
    RIGHT,
    UNDO,
    RESTART,
    SOLVE,
    EXIT,
};

enum class ObjectType
{
    BOX,
    PLAYER,
    GHOST,
};

enum class ItemType
{
    NUMBER,
    OPERATOR,
    EQUALS,
};

enum class OpType
{
    ADD,
    SUB,
    MUL,
};

enum class ColorPair
{
    NORMAL,
    CORRECT,
    WRONG,
    PLAYER_NORMAL,
    PLAYER_CORRECT,
    PLAYER_WRONG,
};

enum class HomeCheckResult
{
    EMPTY,
    CORRECT,
    WRONG,
};
