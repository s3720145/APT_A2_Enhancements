#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <iostream>
#include <climits>
#include <string>
#include "GameBoard.h"

class MainMenu {
public:
    MainMenu();
    ~MainMenu();

    void displayMenu(int seed);

private:

    // Starts a new game
    void newGame(int seed);

    // Starts a new round
    void newRound(GameBoard* gameBoard);
    bool isEndOfRound(GameBoard* gameBoard);

    // Saves a game
    void saveGame(string fileName, GameBoard* gameBoard);

    // Resumes a game from a save file
    void loadGame();

    // Show student information
    void showCredits(int seed);

    // Quit the game
    void quit();

    // Printing functions
    void printFactories(GameBoard* gameBoard);
    void printCurrentPlayerMozaic(GameBoard* gameBoard);
    void currentPlayerTurn(GameBoard* gameBoard);

    // Player input
    string playerInput();

    // Argument Error check
    bool userTurnErrorCheck(string userTurn, std::vector<string>& userTurnArray, GameBoard* gameBoard);
};

#endif // MAIN_MENU_H
