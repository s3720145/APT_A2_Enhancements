#ifndef GAMEBOARD_TESTS
#define GAMEBOARD_TESTS

#include <string>

class GameBoardTests {
public:
    GameBoardTests();
    ~GameBoardTests();
private:
    void centreFactoryTest(std::string outputFileName);

    void factoriesTest(std::string outputFileName);

    void tileBagTest(std::string outputFileName);

    void boxLidTest(std::string outputFileName);
};

#endif // GAMEBOARD_TESTS