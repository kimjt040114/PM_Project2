#include "utils/Terminal.hpp"

#include <stdexcept>
#include <string>

#include <ncurses.h>

AttrType Terminal::Attr::NORMAL = A_NORMAL;
AttrType Terminal::Attr::UNDERLINE = A_UNDERLINE;
AttrType Terminal::Attr::REVERSE = A_REVERSE;
AttrType Terminal::Attr::DIM = A_DIM;

void Terminal::InitConsole()
{
    initscr();
    int row, col;
    getmaxyx(stdscr, row, col);
    if (row <= 25 || col <= 50) throw std::runtime_error("Row and column of the terminal screen should be greater than 25 and 50.");
    start_color();
    keypad(stdscr, true);
    noecho();
    // nodelay(stdscr, true);
    curs_set(0);

    init_pair((short)ColorPair::NORMAL, COLOR_WHITE, COLOR_BLACK);
    init_pair((short)ColorPair::CORRECT, COLOR_GREEN, COLOR_BLACK);
    init_pair((short)ColorPair::WRONG, COLOR_RED, COLOR_BLACK);
    init_pair((short)ColorPair::PLAYER_NORMAL, COLOR_WHITE, COLOR_BLUE);
    init_pair((short)ColorPair::PLAYER_CORRECT, COLOR_GREEN, COLOR_BLUE);
    init_pair((short)ColorPair::PLAYER_WRONG, COLOR_RED, COLOR_BLUE);

    move(0, 0);
    clear();
}

void Terminal::EndConsole()
{
    resetterm();
    endwin();
}

/// @brief Print icon at given location.
/// @param row 
/// @param col 
/// @param icon 
/// @param attr 
/// @param color 
void Terminal::PrintIconAt(int row, int col, char icon, AttrType attr, ColorPair color)
{
    attrset(attr);
    attron(COLOR_PAIR(color));
    mvaddch(row, col, icon);
    attrset(Attr::NORMAL);
    attron(ColorPair::NORMAL);
}

/// @brief Print string at given location.
/// @attention Don't use this function in the project. This function is designed only for compiling curses_test.cpp.
/// @param row 
/// @param col 
/// @param str 
/// @param attr 
/// @param color 
void Terminal::PrintAt(int row, int col, std::string str, AttrType attr, ColorPair color)
{
    attrset(attr);
    attron(COLOR_PAIR(color));
    mvprintw(row, col, "%s", str.c_str());
    attrset(Attr::NORMAL);
    attron(ColorPair::NORMAL);
}

void Terminal::PrintMessage(std::string msg)
{
    mvprintw(22, 0, "%s", msg.c_str());
}

void Terminal::ClearMessage()
{
    int r, c;
    getyx(stdscr, r, c);
    for (int i = 20; i <= 25; i++)
    {
        move(i, 0);
        clrtoeol();
    }
    move(r, c);
}

char Terminal::GetCh()
{
    return getch();
}

Command Terminal::GetCommand()
{
    char ch = getch();
    switch (ch)
    {
        case 'w':
        case 'W':
        case KEY_UP & 0xFF:
            return Command::UP;
        case 'a':
        case 'A':
        case KEY_LEFT & 0xFF:
            return Command::LEFT;
        case 's':
        case 'S':
        case KEY_DOWN & 0xFF:
            return Command::DOWN;
        case 'd':
        case 'D':
        case KEY_RIGHT & 0xFF:
            return Command::RIGHT;
        case 'z':
        case 'Z':
            return Command::UNDO;
        case 'r':
        case 'R':
            return Command::RESTART;
        case 'h':
        case 'H':
            return Command::SOLVE;
        case 'q':
        case 'Q':
            return Command::EXIT;
        default:
            return Command::NONE;
    }
}
