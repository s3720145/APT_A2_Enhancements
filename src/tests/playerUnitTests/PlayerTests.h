#ifndef PLAYER_TESTS
#define PLAYER_TESTS

#include <string>

using std::string;

class Player;

class PlayerTests {
public:
    PlayerTests();
    ~PlayerTests();
private:
    void mosaicTest();

    void storageTest();

    void brokenTileTest();
};

#endif // PLAYER_TESTS