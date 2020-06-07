#include <iostream>

#include "MainMenu.h"
#include "GameBoard.h"

#define EXIT_SUCCESS 0

int main(int argc, char** argv) {
    MainMenu menu;
    std::string arg(argv[2]);
    int seed = std::stoi(arg);

    try {
        menu.displayMenu(seed);
    }
    catch(...) {
        menu.~MainMenu();
    }
    
    return EXIT_SUCCESS;
}