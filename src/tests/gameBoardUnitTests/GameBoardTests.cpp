#include "GameBoardTests.h"
#include "../../GameBoard.h"
#include <fstream>
#include <iostream>

GameBoard* gameBoard = new GameBoard("Test Man 1", "Test Man 2", 10);

GameBoardTests::GameBoardTests() {
    std::cout << "Testing Gameboard" << std::endl;
    
}

void GameBoardTests::centreFactoryTest(std::string outputFileName) {
    std::fstream outputFile(outputFileName);

    std::vector<Tile::Colour> centreFactory = gameBoard->getCentreFactory();

    for (Tile::Colour tile: centreFactory) {
        outputFile << Tile::getTileColourAsString(tile);
    }
    
    outputFile.close();
}

void GameBoardTests::factoriesTest(std::string outputFileName) {
    std::fstream outputFile(outputFileName);

    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < FACTORY_WIDTH; j++) {
            outputFile << Tile::getTileColourAsString(gameBoard->getFactoryTile(i, j));
        }
        outputFile << std::endl;
    }
    
    outputFile.close();
}

void GameBoardTests::tileBagTest(std::string outputFileName) {
    std::fstream outputFile(outputFileName);
    LinkedList* tileBag = gameBoard->getTileBag();
    Node* currentTile = tileBag->getHeader();

    while (currentTile != nullptr) {
        outputFile << Tile::getTileColourAsString(currentTile->getTileColour());
        currentTile = currentTile->getNextNode();
    }
    
    outputFile.close();
}

void GameBoardTests::boxLidTest(std::string outputFileName) {
    std::fstream outputFile(outputFileName);
    LinkedList* boxLid = gameBoard->getBoxLid();
    Node* currentTile = boxLid->getHeader();

    while (currentTile != nullptr) {
        Tile::getTileColourAsString(currentTile->getTileColour());
        currentTile = currentTile->getNextNode();
    }
    
    outputFile.close();
}