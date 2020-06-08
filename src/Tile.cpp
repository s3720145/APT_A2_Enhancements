#include "Tile.h"

const char Tile::getTileColourAsString(Colour tileColour) {
    return tileColour;
}

const int Tile::getTileColourAsInt(Colour tileColour) {
    return tileColour;
}

void Tile::getEscapeCodeChar(Colour tileColour) {
    //string returnedString;

    if(tileColour == Tile::FirstPlayer) {
        cout << "\u001b[47;1m " <<  getTileColourAsString(tileColour) << " \u001b[0m";
    } else if(tileColour == Tile::Red) {
        cout << "\u001b[41m " <<  getTileColourAsString(tileColour) << " \u001b[0m";
    } else if(tileColour == Tile::Yellow) {
        cout << "\u001b[43m " <<  getTileColourAsString(tileColour) << " \u001b[0m";
    } else if(tileColour == Tile::DarkBlue) {
        cout << "\u001b[44m " <<  getTileColourAsString(tileColour) << " \u001b[0m";
    } else if(tileColour == Tile::LightBlue) {
        cout << "\u001b[46m " <<  getTileColourAsString(tileColour) << " \u001b[0m";
    } else if(tileColour == Tile::Black){
        cout << "\u001b[40m " <<  getTileColourAsString(tileColour) << " \u001b[0m";
    } else {
        cout << getTileColourAsString(tileColour) << "  ";
    }
}
