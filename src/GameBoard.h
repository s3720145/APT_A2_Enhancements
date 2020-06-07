#ifndef GAMEBOARD
#define GAMEBOARD

#include "LinkedList.h"
#include "Player.h"
#include <vector>

class GameBoard {

public:
    GameBoard(std::string playerOneName, std::string playerTwoName, int seed);
    GameBoard(std::vector<Tile::Colour> centreFactory);
    ~GameBoard();

    void switchCurrentPlayer();

    // Getter
    std::vector<Tile::Colour>& getCentreFactory();
    LinkedList* getTileBag();
    LinkedList* getBoxLid();
    Player* getCurrentPlayer();
    Player* getPlayerOne();
    Player* getPlayerTwo();
    // row 0 = factory 1 ensure correct row usage
    Tile::Colour getFactoryTile(int row, int column);


    bool isFirstTurn();

    // Setter
    void setFactoryTile(Tile::Colour tile, int row, int column);
    void setFactories(string inputFactory);
    void setTileBagElement(Tile::Colour tile);
    void setBoxLidElement(Tile::Colour tile);
    void initialiseFactories();
    void setPlayerOne(Player* playerOne);
    void setPlayerTwo(Player* playerTwo);
    void setCurrentPlayer(Player* currentPlayer);
    
private:
    /* data */
    std::vector<Tile::Colour> centreFactory;
    Tile::Colour factories[DIM][FACTORY_WIDTH];

    LinkedList* tileBag;
    LinkedList* boxLid;

    // Players
    Player* playerOne;
    Player* playerTwo;
    Player* currentPlayer;

    // Initialise tile bag with a randomize set of tiles
    void initialiseTileBag(int seed);
};

#endif // GAMEBOARD