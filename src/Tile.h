#ifndef TILE
#define TILE

#include <iostream>
#include <string>

#define DIM  5
#define FACTORY_WIDTH 4
#define BAG_SIZE 100

using std::string;
using std::cout;

namespace Tile {
    enum Colour {
        FirstPlayer = 'F',
        Red = 'R',
        Yellow = 'Y',
        DarkBlue = 'B',
        LightBlue = 'L',
        Black = 'U',
        NoTile = '.'
    };

    const char getTileColourAsString(Colour colour);

    const int getTileColourAsInt(Colour colour);

    void getEscapeCodeChar(Colour colour);
}

#endif // TILE