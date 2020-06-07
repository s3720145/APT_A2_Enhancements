#include "GameBoard.h"
#include <random>
#include <iostream>

GameBoard::GameBoard(std::string playerOneName, std::string playerTwoName, int seed) {
    // Initialise data structure
    tileBag = new LinkedList();
    boxLid = new LinkedList();

    // Initialise player mosaics
    playerOne = new Player(playerOneName, 0);
    playerTwo = new Player(playerTwoName, 0);

    // Set player one to current player
    currentPlayer = playerOne;
    // Fill the tile bag
    initialiseTileBag(seed);

    // Put tiles into the factories and set up centre factory
    initialiseFactories();
}

GameBoard::GameBoard(std::vector<Tile::Colour> centreFactory) {
    
    // Initialise data structure
    tileBag = new LinkedList();
    boxLid = new LinkedList();
    
    // Centre factory
    this->centreFactory = centreFactory;

}

GameBoard::~GameBoard() {
    delete playerOne;
    delete playerTwo;
    delete tileBag;
    delete boxLid;
}

void GameBoard::initialiseTileBag(int seed) {
    Tile::Colour colourArray[] = {Tile::Red, Tile::Yellow, Tile::DarkBlue, 
        Tile::LightBlue, Tile::Black};
    // Check for number of tiles for the entire stack
    int redCounter = 0;
    int yellowCounter = 0;
    int darkBlueCounter = 0;
    int lightBlueCounter = 0;
    int blackCounter = 0;

    for (int i = 0; i < BAG_SIZE; i++) {
        // seed the engine
        std::mt19937 engine(++seed);
        //establish the range of values that the enum can be
        std::uniform_int_distribution<int> range(0, 4);
        
        Tile::Colour randomTile = Tile::NoTile;
        // Generate numbers and cast them into an enum type
        do {
            randomTile = colourArray[range(engine)];
        } while (randomTile == Tile::NoTile);
        
        if (randomTile == Tile::Red && redCounter < 20) {
            if (redCounter == 19) {
                colourArray[0] = Tile::NoTile;
            }
            redCounter++;
        }
        else if (randomTile == Tile::Yellow && yellowCounter < 20) {
            if (yellowCounter == 19) {
                colourArray[1] = Tile::NoTile;
            }
            yellowCounter++;
        }
        else if (randomTile == Tile::DarkBlue && darkBlueCounter < 20) {
            if (darkBlueCounter == 19) {
                colourArray[2] = Tile::NoTile;
            }
            darkBlueCounter++;
        }
        else if (randomTile == Tile::LightBlue && lightBlueCounter < 20) {
            if (lightBlueCounter == 19) {
                colourArray[3] = Tile::NoTile;
            }
            lightBlueCounter++;
        }
        else if (randomTile == Tile::Black && blackCounter < 20) {
            if (blackCounter == 19) {
                colourArray[4] = Tile::NoTile;
            }
            blackCounter++;
        }
        
        tileBag->addBack(randomTile);
    }
}

void GameBoard::initialiseFactories() {
    // Add first player tile to the centre factory
    centreFactory.push_back(Tile::FirstPlayer);

    // Check if tilebag has any tiles and if it doesn't transfer from boxlid
    if (tileBag->getHeader() != nullptr) {
        for(int i = 0; i < boxLid->size(); ++i) {
            tileBag->addBack(boxLid->dequeue()->getTileColour());
        }
    }

    // Add tiles from the tile bag to the factories
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < FACTORY_WIDTH; j++) {
            Tile::Colour tile = tileBag->dequeue()->getTileColour();
            factories[i][j] = tile;
        }

    }
}

Player* GameBoard::getCurrentPlayer() {
    return this->currentPlayer;
}

void GameBoard::setFactories(string inputFactory) {
    int stringCounter = 0;
    for(int row_num = 0; row_num < DIM; ++row_num) {
        for(int col_num = 0; col_num < FACTORY_WIDTH; ++col_num) {
            
            if (inputFactory[stringCounter] == ' ') {
                factories[row_num][col_num] = Tile::NoTile;
            }
            else {
                factories[row_num][col_num] = (Tile::Colour) inputFactory[stringCounter];
            }
            ++stringCounter;
        }
    }
}

bool GameBoard::isFirstTurn() {
    bool isFirstTurn = false;
    if (centreFactory.size() == 1) {
        if (Tile::getTileColourAsString(centreFactory.front()) == 'F') {
            isFirstTurn = true;
        }
    }
    return isFirstTurn;
}

void GameBoard::switchCurrentPlayer() {
    // Check if pointing to the same object and then change it's pointer
    if (currentPlayer == playerOne) {
        currentPlayer = playerTwo;
    }
    else if (currentPlayer == playerTwo) {
        currentPlayer = playerOne;
    }
}

std::vector<Tile::Colour>& GameBoard::getCentreFactory() {
    return this->centreFactory;
}

Tile::Colour GameBoard::getFactoryTile(int row, int column) {
    return this->factories[row][column];
}

void GameBoard::setFactoryTile(Tile::Colour tile, int row, int column) {
    this->factories[row][column] = tile;
}

LinkedList* GameBoard::getTileBag() {
    return this->tileBag;
}

void GameBoard::setTileBagElement(Tile::Colour tile) {
    this->tileBag->addBack(tile);
}

LinkedList* GameBoard::getBoxLid() {
    return this->boxLid;
}

void GameBoard::setBoxLidElement(Tile::Colour tile) {
    this->boxLid->addBack(tile);
}

Player* GameBoard::getPlayerOne() {
    return this->playerOne;
}

Player* GameBoard::getPlayerTwo() {
    return this->playerTwo;
}

void GameBoard::setPlayerOne(Player* playerOne) {
    this->playerOne = playerOne;
}

void GameBoard::setPlayerTwo(Player* playerTwo) {
    this->playerTwo = playerTwo;
}
void GameBoard::setCurrentPlayer(Player* currentPlayer){
    this->currentPlayer = currentPlayer;
}
