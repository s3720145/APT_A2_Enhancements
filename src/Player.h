#ifndef PLAYER
#define PLAYER

#include <string>
#include <array>
#include "Tile.h"

#define ARRAY_DIM           5
#define MAX_BROKEN_TILES    7

using std::string;

class LinkedList;

class Player {
public:
    // DEFAULT costructor for a new game
    Player(string playerName, int score);
    // COPY constructor
    Player(const Player& other);
    // MOVE constructor
    Player(Player&& other);
    ~Player();

    /**
     * Initialises the mosaic and storage ADTs. Only initialised
     * once which is when the constructor is called.
     */
    void initialiseStructures();

    // Returns playerName.
    string getPlayerName() const;

    void setScore(const int totalScore);

    int getScore() const;

    void setStorage(string inputStorage);

    /**
     * Returns a pointer to storage[row_num][col_num]. Returns null if the 
     * contract is violated.
     * 
     * row_num MUST be >= 0 and < ARRAY_DIM
     * col_num MUST be >= 0 and <= row_num
     */
    Tile::Colour* getStorageTile(const int row_num, const int col_num);

    void setMosaic(string inputMosaic);

    /**
     * Returns a pointer to mosaic[row_num][col_num]. Returns null if the 
     * contract is violated.
     * 
     * row_num and col_num MUST be >= 0 and < ARRAY_DIM
     */
    char* getMosaicTile(const int row_num, const int col_num);

    void setBrokenTiles(string inputBroken);

    Tile::Colour* getBrokenTile(const int col_num);

    int getPointPenalty();

    int getNumBrokenTiles();

    // Prints the player's mosaic and storage rows.
    void printPlayerBoard() const;

    // Inserts a tile into the mosaic.
    void insertIntoMosaic(const int row_num, const Tile::Colour tile);

    bool isInMosaicRow(const int row_num, Tile::Colour tile);

    /**
     * Inserts a tile into a storage row. user specifies the storage row the 
     * tile is inserted in. 
     * return false if insertion fails. This can happen when:
     *  -attempting to insert the tile into a row with non-matching coloured tiles
     *  -the row is full and no more tiles can be inserted
     * 
     * Must discuss which class is responsible for:
     *  -IF insertion fail you must place tile in the broken section
     *  -Cannot place tile into storage if that row already has a same colour 
     *   tile in the mosaic
     * 
     * row_num MUST be >= 1 and <= 5
     */
    bool insertIntoStorage(const int row_num, const Tile::Colour tile);

    /**
     * Call at the end of each round for each player. 
     * Checks all storage rows if they are full.
     * If a storage row is full, add the last tile in the row to the mosaic
     * place the rest in the box lid. 
     */
    void clearStorageRows(LinkedList& boxLid);

    void insertIntoBrokenTiles(Tile::Colour tile);

    bool hasFullRow();

private:
    string playerName;

    int totalScore;

    int roundScore;

    // Keeps track of the number of broken tiles
    int numBrokenTiles;

    // Storage rows on the left-hand side of the player's mosaic
    Tile::Colour storage[ARRAY_DIM][ARRAY_DIM];

    // Player mosaic 
    char mosaic[ARRAY_DIM][ARRAY_DIM];

    // Player broken tiles
    Tile::Colour brokenTiles[MAX_BROKEN_TILES];
};

#endif // PLAYER