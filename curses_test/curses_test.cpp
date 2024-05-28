#include <string>

#include "utils/Terminal.hpp"
#include "Enums.hpp"

int main()
{
    Terminal::InitConsole();

    for (int i = 0; i < 6; i++)
    {
        ColorPair colorpair = (ColorPair)i;

        Terminal::PrintAt(3*i+1, 1, "Normal", Terminal::Attr::NORMAL, colorpair);

        Terminal::PrintAt(3*i+1, 13, "Underlined", Terminal::Attr::UNDERLINE, colorpair);

        Terminal::PrintAt(3*i+1, 36, "Reversed", Terminal::Attr::REVERSE, colorpair);

        Terminal::PrintAt(3*i+2, 1, "Dimmed", Terminal::Attr::DIM, colorpair);

        Terminal::PrintAt(3*i+2, 13, "Underline | Dim", Terminal::Attr::UNDERLINE | Terminal::Attr::DIM, colorpair);

        Terminal::PrintAt(3*i+2, 36, "Reverse | Dim", Terminal::Attr::REVERSE | Terminal::Attr::DIM, colorpair);
    }

    Terminal::PrintMessage("Press any key to exit...");
    Terminal::GetCh();
    Terminal::EndConsole();
    return 0;
}
