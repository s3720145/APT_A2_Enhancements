#include "MainMenu.h"
#include "Player.h"
#include "LinkedList.h"
#include "tests/playerUnitTests/PlayerTests.h"
#include <fstream>

using std::cout;
using std::cin;
using std::exception;
using std::string;
using std::endl;

MainMenu::MainMenu() {
    
}

MainMenu::~MainMenu() {

}

void MainMenu::displayMenu(int seed) {
    cout << "Menu" << '\n' << "----" << '\n'
    << "1. New Game" << '\n'
    << "2. Load Game" << '\n'
    << "3. Credits (Show student information)" << '\n'
    << "4. Quit" << '\n' << "> ";

    int userInput;

    while (!(cin >> userInput) || userInput < 1 || userInput > 4) {
        if(cin.eof()) {
            quit();
        } else {
            cout << "Incorrect input - please try again: ";
            cin.clear();
            cin.ignore(INT_MAX,'\n');
        }
    }

    if(userInput == 1) {
        newGame(seed);
    } else if(userInput == 2) {
        loadGame();
    } else if(userInput == 3) {
        showCredits(seed);
    } else {
        quit();
    }
}

void MainMenu::newGame(int seed) {
    cout << "Starting a New Game" << "\n\n";
    cout << "Enter a name for player 1" << "\n> ";
    string playerOneName;
    cin >> playerOneName;

    cout << endl;

    cout << "Enter a name for player 2" << "\n> ";
    string playerTwoName;
    cin >> playerTwoName;

    cout << "\n\n";
    cout << "Let's Play" << "\n\n";

    GameBoard* gameBoard = new GameBoard(playerOneName, playerTwoName, seed);
    Player* playerOne = gameBoard->getPlayerOne();
    Player* playerTwo = gameBoard->getPlayerTwo();

    // End of game condition for every new round
    while(playerOne->hasFullRow() == false && playerTwo->hasFullRow() == false) {
        newRound(gameBoard);
    }

    cout << "=== Game End ===" << endl;
    cout << "Player: " << playerOne->getPlayerName() <<
    "  " << playerOne->getScore() << "\n\n";
    cout << "Player: " << playerTwo->getPlayerName() <<
    "  " << playerTwo->getScore() << "\n\n";

    // Find out the winner
    if(playerOne->getScore() > playerTwo->getScore()) {
        cout << gameBoard->getPlayerOne()->getPlayerName() << " WINS!!!" << "\n\n";
    } 
    else if(playerTwo->getScore() > playerOne->getScore()) {
        cout << gameBoard->getPlayerTwo()->getPlayerName() << " WINS!!!" << "\n\n";
    } else {
        cout << "WE HAVE A DRAW!!!" << "\n\n";
    }

    delete gameBoard;
}

void MainMenu::newRound(GameBoard* gameBoard) {
    cout << "=== Start Round ===" << "\n";
    
    // Player turns 
    do {
        currentPlayerTurn(gameBoard);
    } while (!(isEndOfRound(gameBoard)));
    
    // End of round

    // Player 1 transfer full row into mosaic 
    Player* playerOne = gameBoard->getPlayerOne();
    playerOne->clearStorageRows(*gameBoard->getBoxLid());
    
    // Player 2 transfer full row into mosaic 
    Player* playerTwo = gameBoard->getPlayerTwo();
    playerTwo->clearStorageRows(*gameBoard->getBoxLid());

    // Print player information
    playerOne->printPlayerBoard();
    playerTwo->printPlayerBoard();

    // Reset centre factory
    gameBoard->getCentreFactory().clear();
    // Refill
    gameBoard->initialiseFactories();
    
    // Set pointers to null
    playerOne = nullptr;
    playerTwo = nullptr;
    cout << endl;
}

void MainMenu::currentPlayerTurn(GameBoard* gameBoard) {
    Player* currentPlayer = gameBoard->getCurrentPlayer();
    cout << "TURN FOR PLAYER: " << currentPlayer->getPlayerName();
    cout << endl;

    printFactories(gameBoard);

    printCurrentPlayerMozaic(gameBoard);

    string userTurn;
    std::vector<string> userTurnArray;
    std::vector<Tile::Colour> chosenTiles;
    int storageRow = 0;

    // Valid Rule check
    bool turnIsValid = false;
    do {
        // Complete argument error check
        do {
            userTurn = playerInput();
        } while (!(userTurnErrorCheck(userTurn, userTurnArray, gameBoard)));
        
        storageRow = 0;
        // Get commands
        int factory = std::stoi(userTurnArray.at(1))-1;
        string tileColour = userTurnArray.at(2);
        if (userTurnArray.at(3) != "b") {
            storageRow = std::stoi(userTurnArray.at(3));
        }

        // Get tile/s from centre factory
        if (factory == -1) {
            for (Tile::Colour currentTile: gameBoard->getCentreFactory()) {
                if (Tile::getTileColourAsString(currentTile) == tileColour[0]) {
                    // Add correct tiles to temp vector
                    chosenTiles.push_back(currentTile);
                }
            }

        } // Otherwise get tiles from other factories
        else {
            for (int j = 0; j < FACTORY_WIDTH; j++) {
                Tile::Colour currentTile = gameBoard->getFactoryTile(factory, j);
                
                if (Tile::getTileColourAsString(currentTile) == tileColour[0]) {
                    // Add correct tiles to temp vector
                    chosenTiles.push_back(currentTile);
                }
            }
        }
        
        // First turn check
        if (gameBoard->isFirstTurn() && factory == -1) {
            cout << "Can't choose the centre factory on the first turn" << endl;
            userTurnArray.clear();
            chosenTiles.clear();
        }   // Null check
        else if (chosenTiles.empty()) {
            cout << "No Tiles match your option. Try Again" << endl;
            userTurnArray.clear();
        }   // Check if need to insert into broken tiles
        else if (storageRow == 0) {
            size_t numberOfSpaces = 7-currentPlayer->getNumBrokenTiles();
            if (chosenTiles.size() < numberOfSpaces) {
                // Adjust the factories to reflect the valid move
                if (factory == -1) {
                    // Check if first element is first player
                    if (gameBoard->getCentreFactory().front() == Tile::FirstPlayer) {
                        // Insert into broken tiles
                        currentPlayer->insertIntoBrokenTiles(Tile::FirstPlayer);
                        gameBoard->getCentreFactory().erase(gameBoard->getCentreFactory().begin());
                    }
                    for (int i = 0; i < (int) gameBoard->getCentreFactory().size(); i++) {
                        Tile::Colour currentTile = gameBoard->getCentreFactory()[i];
                        if (Tile::getTileColourAsString(currentTile) == tileColour[0]) {
                            gameBoard->getCentreFactory()[i] = Tile::NoTile;
                        }
                        
                    }
                    
                    cout << endl;
                }
                else {
                    for (int j = 0; j < FACTORY_WIDTH; j++) {
                        Tile::Colour currentTile = gameBoard->getFactoryTile(factory, j);
                        
                        if (Tile::getTileColourAsString(currentTile) == tileColour[0]) {
                            // set to no tile in factory 
                            gameBoard->setFactoryTile(Tile::NoTile, factory, j);
                        }
                        else {
                            // Add to centre factory
                            gameBoard->getCentreFactory().push_back(currentTile);
                            // set to no tile in factory 
                            gameBoard->setFactoryTile(Tile::NoTile, factory, j);
                        }
                    }
                }
                // No game rules violated
                turnIsValid = true;
                cout << "Turn successful" << endl;
            }
            else {
                cout << "Broken tiles are full. Try again" << endl;
                userTurnArray.clear();
                chosenTiles.clear();
            }
        }   // Check first element for rule check
        else if (currentPlayer->insertIntoStorage(storageRow, chosenTiles.front())) {
            // Removed from temporary vector
            chosenTiles.pop_back();
            // Adjust the factories to reflect the valid move
            if (factory == -1) {
                // Check if first element is first player
                if (gameBoard->getCentreFactory().front() == Tile::FirstPlayer) {
                    // Insert into broken tiles
                    currentPlayer->insertIntoBrokenTiles(Tile::FirstPlayer);
                    gameBoard->getCentreFactory().erase(gameBoard->getCentreFactory().begin());
                }
                for (int i = 0; i < (int) gameBoard->getCentreFactory().size(); i++) {
                    Tile::Colour currentTile = gameBoard->getCentreFactory()[i];
                    if (Tile::getTileColourAsString(currentTile) == tileColour[0]) {
                        gameBoard->getCentreFactory()[i] = Tile::NoTile;
                    }
                    
                }
                
                cout << endl;
            }
            else {
                for (int j = 0; j < FACTORY_WIDTH; j++) {
                    Tile::Colour currentTile = gameBoard->getFactoryTile(factory, j);
                    
                    if (Tile::getTileColourAsString(currentTile) == tileColour[0]) {
                        // set to no tile in factory 
                        gameBoard->setFactoryTile(Tile::NoTile, factory, j);
                    }
                    else {
                        // Add to centre factory
                        gameBoard->getCentreFactory().push_back(currentTile);
                        // set to no tile in factory 
                        gameBoard->setFactoryTile(Tile::NoTile, factory, j);
                    }
                }
            }
            
            // No game rules violated
            turnIsValid = true;
            cout << "Turn successful" << endl;
        }
        else {
            cout << "Storage row has a different tile or mozaic already contains tile.";
            cout << " Try Again" << endl;
            // Reset chosen tiles
            chosenTiles.clear();
            userTurnArray.clear();
        }
    } while (!(turnIsValid));
    
    // Add to players mozaic with storage row
    for (Tile::Colour tile: chosenTiles) {
        // If true tile will be added to the correct storage row
        if (currentPlayer->insertIntoStorage(storageRow, tile)) {
            // Removed from temporary vector
            chosenTiles.pop_back();
        } 
        else { // Otherwise add to broken tiles
            currentPlayer->insertIntoBrokenTiles(tile);
            // Removed from temporary vector
            chosenTiles.pop_back();
        }
    }

    cout << endl;

    // Change current player
    gameBoard->switchCurrentPlayer();
    // Set current player pointer to null
    currentPlayer = nullptr;
}

string MainMenu::playerInput() {
    string userTurn;
    // current player turn
    cout << "> ";
    
    getline(cin >> std::ws, userTurn);
    return userTurn;
}

bool MainMenu::userTurnErrorCheck(string userTurn, 
                                std::vector<string>& userTurnArray, GameBoard* gameBoard) {
    
    bool noErrors = true;
    
    size_t pos = 0;
    string token;

    // Split the string into a vector
    string delimiter = " ";

    while ((pos = userTurn.find(delimiter)) != string::npos) {
        token = userTurn.substr(0, pos);
        userTurnArray.push_back(token);
        userTurn.erase(0, pos + delimiter.length());
    }
    userTurnArray.push_back(userTurn);

    // Check for argument number error
    if (userTurnArray.size() != 4) {
        if (userTurnArray.size() == 2) {
            // save file
            string command = userTurnArray.at(0);
            string fileName = userTurnArray.at(1);

            if (command == "save") {
                noErrors = false;
                saveGame(fileName, gameBoard);
                userTurnArray.clear();
                cin.clear();
            }
            else {
                noErrors = false;
                userTurnArray.clear();
                cout << "You must enter the 'turn' or 'save' command" << endl;
                cin.clear();
            }
        }
        else {
            if (userTurnArray.size() == 1) {
                if (cin.eof()) {
                    //escape
                    cout << "^D" << endl;
                }
                else {
                    noErrors = false;
                    userTurnArray.clear();
                    cout << "Incorrect number of arguments" << endl;
                    cin.clear();
                }
            }
            else {
                noErrors = false;
                userTurnArray.clear();
                cout << "Incorrect number of arguments" << endl;
                cin.clear();    
            }
            
        }
        
    }  // Check for argument type error
    else {
        // Get commands
        string command = userTurnArray.at(0);
        string factory = userTurnArray.at(1);
        string tileColour = userTurnArray.at(2);
        string storageRow = userTurnArray.at(3);
        
        // Check conversion to an int
        bool factoryInt = (factory.find_first_not_of("0123456789") == string::npos);
        bool storageInt = (storageRow.find_first_not_of("0123456789") == string::npos);

        // Check Tile::Colour match
        Tile::Colour colourArray[] = {Tile::Red, Tile::Yellow, Tile::DarkBlue, 
        Tile::LightBlue, Tile::Black};

        bool tileMatch = false;
        for (Tile::Colour tile: colourArray) {
            if (Tile::getTileColourAsString(tile) == tileColour[0]) {
                tileMatch = true;
            }
        }

        if (command != "turn") {
            noErrors = false;
            userTurnArray.clear();
            cout << "You must enter the 'turn' or 'save' command" << endl;
            cin.clear();
        }
        else if (factoryInt == true && storageInt == false) {
            if (storageRow != "b") {
                noErrors = false;
                userTurnArray.clear();
                cout << "You must enter an integer between 1 and 5" << endl;
                cin.clear();
            }
        }
        else if (factoryInt == false || storageInt == false) {
            noErrors = false;
            userTurnArray.clear();
            cout << "You must enter an integer between 1 and 5" << endl;
            cin.clear();
        }
        else if (tileMatch == false) {
            noErrors = false;
            userTurnArray.clear();
            cout << "You must provide the correct tile colour" << endl;
            cin.clear();
        }
        else { // Check if numbers are between 1 and 5
            int factoryAsInt = std::stoi(factory);
            int storageAsInt = std::stoi(storageRow);
            if (!(factoryAsInt >= 0 && factoryAsInt <= 5) || 
                !(storageAsInt >= 1 && storageAsInt <= 5)) {
                noErrors = false;
                userTurnArray.clear();
                cout << "You must enter an integer between 0 and 5 for factories" << endl;
                cout << "You must enter an integer between 1 and 5 for storage" << endl;
                cin.clear();
            }
        }
    }
    
    return noErrors;
}

void MainMenu::printFactories(GameBoard* gameBoard) {
    // Print centre Factory
    cout << "Factories:" << endl;
    cout << "0: ";
    for (Tile::Colour tile: gameBoard->getCentreFactory()) {
        if (Tile::getTileColourAsString(tile) != '.') {
            cout << Tile::getTileColourAsString(tile);
        }
    }
    cout << endl;
    
    // Print other factories
    for (int i = 0; i < DIM; i++) {
        cout << (i+1) << ": ";
        for (int j = 0; j < FACTORY_WIDTH; j++) {
            Tile::Colour tile = gameBoard->getFactoryTile(i, j);
            if (Tile::getTileColourAsString(tile) != '.') {
                cout << Tile::getTileColourAsString(gameBoard->getFactoryTile(i, j));
            }
        }
        cout << endl;
    }
}

bool MainMenu::isEndOfRound(GameBoard* gameBoard) {
    bool isEmpty = false;

    // Check centre factory
    bool isCentreFactoryEmpty = true;
    for (int i = 0; i < (int) gameBoard->getCentreFactory().size() 
        && isCentreFactoryEmpty == true; i++) {

        Tile::Colour currentTile = gameBoard->getCentreFactory()[i];
        if (Tile::getTileColourAsString(currentTile) != '.') {
            isCentreFactoryEmpty = false;
        }
        
    }

    bool areFactoriesEmpty = true;
    // Loop through 2d factories array 
    // breakLoop stops the for loop from continuing if it contains a tile colour
    bool breakLoop = false;
    for (int i = 0; i < DIM && breakLoop == false; i++) {
        for (int j = 0; j < FACTORY_WIDTH && breakLoop == false; j++) {

            Tile::Colour currentTile = gameBoard->getFactoryTile(i, j);
            if (Tile::getTileColourAsString(currentTile) != '.') {
                areFactoriesEmpty = false;
                breakLoop = true;
            }

        }
    }
    
    if (isCentreFactoryEmpty && areFactoriesEmpty) {
        cout << "=== END OF ROUND ===" << endl;
        isEmpty = true;
    }
    
    return isEmpty;
}

void MainMenu::printCurrentPlayerMozaic(GameBoard* gameBoard) {
    Player* currentPlayer = gameBoard->getCurrentPlayer();
    // Print current player mozaic
    cout << "Mozaic for " << currentPlayer->getPlayerName() << ":" << endl;
    for (int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
        cout << row_num + 1 << ": ";
        // Prints the storage rows
        for(int col_num = 1; col_num < ARRAY_DIM - row_num ; ++col_num) {
            cout << ' ';
        }
        for(int col_num = row_num; col_num >= 0; --col_num) {
            Tile::Colour tile = *currentPlayer->getStorageTile(row_num, col_num);
            cout << Tile::getTileColourAsString(tile);
        }

        // Prints the mosaic
        cout << "||";
        
        for(int col_num = 0; col_num < ARRAY_DIM; ++col_num) {
            cout << *currentPlayer->getMosaicTile(row_num, col_num);
        }
        
        cout << std::endl;
    }
    
    // Print broken tiles
    cout << "broken: ";
    for (int i = 0; i <= currentPlayer->getNumBrokenTiles() - 1; ++i) {
        cout << Tile::getTileColourAsString(*currentPlayer->getBrokenTile(i));
    }

    // Set current player pointer to null
    currentPlayer = nullptr;
    cout << endl;
}

void MainMenu::saveGame(string fileName, GameBoard* gameBoard) {
    std::ofstream saveFile("src/saveFiles/" + fileName);
    
    if(saveFile.fail()) {
        cout << "File not found";
    } else {
        if(gameBoard->getCurrentPlayer() == gameBoard->getPlayerOne()) {
        saveFile << "true" << '\n';
        } else {
            saveFile << "false" << '\n';
        }

        // player 1 name and score
        saveFile << gameBoard->getPlayerOne()->getPlayerName() << '\n';
        saveFile << gameBoard->getPlayerOne()->getScore() << '\n';

        // player 2 name and score
        saveFile << gameBoard->getPlayerTwo()->getPlayerName() << '\n';
        saveFile << gameBoard->getPlayerTwo()->getScore() << '\n';

        // Centre factory
        std::vector<Tile::Colour>& centreFactory = gameBoard->getCentreFactory();
        for(int i = 0; i < (int) centreFactory.size(); ++i) {
            if (centreFactory[i] != Tile::NoTile) {
                saveFile << Tile::getTileColourAsString(centreFactory[i]);
            }
        }
        saveFile << '\n';

        // Factories
        for(int row_num = 0; row_num < DIM; ++row_num) {
            for(int col_num = 0; col_num < FACTORY_WIDTH; ++col_num) {
                if(gameBoard->getFactoryTile(row_num, col_num) != Tile::NoTile) {
                    Tile::Colour tile = gameBoard->getFactoryTile(row_num, col_num);
                    saveFile << Tile::getTileColourAsString(tile);
                } 
            }
            saveFile << '\n';
        }

        // Player 1
        // storage
        for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
            for(int col_num = row_num; col_num >= 0; --col_num) {
                Tile::Colour tile = *gameBoard->getPlayerOne()->getStorageTile(row_num,col_num);
                saveFile << Tile::getTileColourAsString(tile);
            }
            saveFile << '\n';
        }

        // broken tiles
        for(int i = 0; i < gameBoard->getPlayerOne()->getNumBrokenTiles(); ++i) {
            Tile::Colour tile = *gameBoard->getPlayerOne()->getBrokenTile(i);
            saveFile << Tile::getTileColourAsString(tile);
        }
        saveFile << '\n';

        // mosaic
        for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
            for(int col_num = 0; col_num < ARRAY_DIM; ++col_num) {
                saveFile << *gameBoard->getPlayerOne()->getMosaicTile(row_num, col_num);
            }
        }
        saveFile << '\n';

        // Player 2
        // storage
        for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
            for(int col_num = row_num; col_num >= 0; --col_num) {
                Tile::Colour tile = *gameBoard->getPlayerTwo()->getStorageTile(row_num,col_num);
                saveFile << Tile::getTileColourAsString(tile);
            }
            saveFile << '\n';
        }

        // broken tiles
        for(int i = 0; i < gameBoard->getPlayerTwo()->getNumBrokenTiles(); ++i) {
            Tile::Colour tile = *gameBoard->getPlayerTwo()->getBrokenTile(i);
            saveFile << Tile::getTileColourAsString(tile);
        }
        saveFile << '\n';

        // mosaic
        for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
            for(int col_num = 0; col_num < ARRAY_DIM; ++col_num) {
                saveFile << *gameBoard->getPlayerTwo()->getMosaicTile(row_num, col_num);
            }
        }
        saveFile << '\n';

        // Box lid and tile bag
        saveFile << gameBoard->getBoxLid()->getAllTilesAsString() << '\n';
        saveFile << gameBoard->getTileBag()->getAllTilesAsString() << '\n';

        cout << "Game successfully saved to '" << fileName << "'" << endl;
    }

    saveFile.close();
}

void MainMenu::loadGame() {
    string fileName;
    cout << "Enter a filename to load a game: " << endl;
    cout << "> ";
    cin >> std::ws >> fileName;
 
    std::ifstream fileload("src/saveFiles/" + fileName);
 
    // If file does not exist
    if(!fileload.is_open()) {
        cout << "File does not Exist " << "’" << fileName << "’"  << endl;
        quit();
    }
    GameBoard* gameBoard;
    Player* playerOne;
    Player* playerTwo;
    try {
        string currentPlayerTurn;
        getline(fileload, currentPlayerTurn);

        // Get player one name and points to create new player
        string playerOneName;
        getline(fileload, playerOneName);
    
        string playerOnePoints;
        getline(fileload, playerOnePoints);
        std::stoi(playerOnePoints);

        playerOne = new Player(playerOneName, std::stoi(playerOnePoints));

        // Get player two name and points to create new player 
        string playerTwoName;
        getline(fileload, playerTwoName);
        
        string playerTwoPoints;
        getline(fileload, playerTwoPoints);
        
        playerTwo = new Player(playerTwoName, std::stoi(playerTwoPoints));

        
        std::vector<Tile::Colour> centreFactory;
        string centreFactoryString;
        getline(fileload, centreFactoryString);
        
        // split the string and push it into the centre factory
        int stringCounter = 0;
        for(int row_num = 0; row_num < (int) centreFactoryString.length(); ++row_num) {
            
            int tileInt = (int) centreFactoryString[stringCounter];
            centreFactory.push_back((Tile::Colour) tileInt);
            ++stringCounter;
            
        }
        gameBoard = new GameBoard(centreFactory);

        // Factoryline
        string combinedFactoryStr;
        for(int i = 0; i < ARRAY_DIM; ++i) {
            string factoryString;
            getline(fileload, factoryString);
            if (factoryString.empty()) {
                combinedFactoryStr.append("    ");
            }
            else {
                combinedFactoryStr.append(factoryString);
            }
        }
        gameBoard->setFactories(combinedFactoryStr);

        // set player one storage
        string playerOneStrInput;
        for(int i = 0; i < ARRAY_DIM; ++i) {
            string storageRowInput;
            getline(fileload, storageRowInput);
            playerOneStrInput.append(storageRowInput);
        }
        playerOne->setStorage(playerOneStrInput);
        
        // set player one broken tiles
        string playerOneBrokenTiles;
        getline(fileload, playerOneBrokenTiles);
        playerOne->setBrokenTiles(playerOneBrokenTiles);
        
        // set player one mosaic
        string playerOneMosaicStr;
        getline(fileload, playerOneMosaicStr);
        playerOne->setMosaic(playerOneMosaicStr);

        // set player two storage
        string playerTwoStrInput;
        for(int i = 0; i < ARRAY_DIM; ++i) {
            string storageRowInput;
            getline(fileload, storageRowInput);
            playerTwoStrInput.append(storageRowInput);
        }
        playerTwo->setStorage(playerTwoStrInput);
        
        // set player two broken tiles
        string playerTwoBrokenTiles;
        getline(fileload, playerTwoBrokenTiles);
        playerTwo->setBrokenTiles(playerTwoBrokenTiles);
    
        // set player two mosaic
        string mosaicStr1;
        getline(fileload, mosaicStr1);
        playerTwo->setMosaic(mosaicStr1);

        // Set recently created players to gameboard
        gameBoard->setPlayerOne(playerOne);
        gameBoard->setPlayerTwo(playerTwo);

        // Set current player turn in gameboard
        if(currentPlayerTurn == "true") {
            gameBoard->setCurrentPlayer(gameBoard->getPlayerOne());

        } else if(currentPlayerTurn == "false"){
            gameBoard->setCurrentPlayer(gameBoard->getPlayerTwo());
        }
        // set gameboard box lid 
        string boxLidStr;
        getline(fileload, boxLidStr);

        stringCounter = 0;
        for(int row_num = 0; row_num < (int) boxLidStr.length(); ++row_num) {
            int tileInt = (int) boxLidStr[stringCounter];
            gameBoard->setBoxLidElement((Tile::Colour) tileInt);
            ++stringCounter;
        }

        // set gameboard tilebag
        string tileBagStr;
        getline(fileload, tileBagStr);

        stringCounter = 0;
        for(int row_num = 0; row_num < (int) tileBagStr.length(); ++row_num) { 
            int tileInt = (int) tileBagStr[stringCounter];
            gameBoard->setTileBagElement((Tile::Colour) tileInt);
            ++stringCounter; 
        }
    }
    catch(...) {
        std::cerr << "File load corrupted" << '\n';
        quit();
    }
    
    fileload.close();

    while(playerOne->hasFullRow() == false && playerTwo->hasFullRow() == false) {
        newRound(gameBoard);
    }

    cout << "=== Game End ===" << endl;
    cout << "Player: " << playerOne->getPlayerName() <<
    "  " << playerOne->getScore() << "\n\n";
    cout << "Player: " << playerTwo->getPlayerName() <<
    "  " << playerTwo->getScore() << "\n\n";

    if(playerOne->getScore() > playerTwo->getScore()) {
        cout << playerOne->getPlayerName() << " WINS!!!" << "\n\n";
    } 
    else if(playerTwo->getScore() > playerTwo->getScore()) {
        cout << playerTwo->getPlayerName() << " WINS!!!" << "\n\n";
    } 
    else {
        cout << "WE HAVE A DRAW!!!" << "\n\n";
    }

    // set current pointers to null
    playerOne = nullptr;
    playerTwo = nullptr;

    // Delete GameBoard
    delete gameBoard;
}

void MainMenu::showCredits(int seed) {
    struct student {
        string name;
        string studentId;
        string eMail;
    };

    student students[] = {
        {"Marco Pereira Barros", "s3379774", "s3379774@student.rmit.edu.au"},
        {"Ivan Cedric Tomas Bulosan", "s3720145", "s3720145@student.rmit.edu.au"},
        {"Adama Fofana", "s3640426", "s3640426@student.rmit.edu.au"}
    };

    for (student student : students) {
        cout << student.name << '\n'
        << student.studentId << '\n'
        << student.eMail << '\n'
        << "----------------- \n";
    }

    displayMenu(seed);
}

void MainMenu::quit() {
    throw exception();
}