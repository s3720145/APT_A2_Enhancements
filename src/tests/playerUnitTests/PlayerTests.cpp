#include "PlayerTests.h"
#include "../../Player.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>

using std::cout;
using std::endl;

Player* testPlayer = new Player("test", 1);

PlayerTests::PlayerTests() {
    cout << "TESTING PLAYER ..." << endl;
    mosaicTest();
    storageTest();
    brokenTileTest();
}

PlayerTests::~PlayerTests() {

}

void PlayerTests::mosaicTest() {
    cout << "TESTING PLAYER MOSAIC ..." << endl;

    // NOTE: Look at differences between ofstreams and ifstreams
    std::ifstream inputFile("src/tests/input/mosaic-input.txt");
    std::ofstream outputFile("src/tests/output/mosaic-output.txt");
    string mosaicInput;
    string mosaicOutput;


    if (!inputFile) {
        std::cout << "Somthing failed while opening the file\n";
    }

    inputFile.clear();
    while(std::getline(inputFile, mosaicInput)) {
        // the read worked and the line is valid
    }

    testPlayer->setMosaic(mosaicInput);

    for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
        for(int col_num = 0; col_num < ARRAY_DIM; ++col_num) {
            outputFile << *testPlayer->getMosaicTile(row_num,col_num);
        }
    }

    inputFile.close();
    outputFile.close();
}

void PlayerTests::storageTest() {
    cout << "TESTING PLAYER STORAGE ..." << endl;

    std::ifstream inputFile("src/tests/input/storage-input.txt");
    std::ofstream outputFile("src/tests/output/storage-output.txt");
    string textRead;
    string combinedInput;
    string storageOutput;

    if (!inputFile) {
        std::cout << "Something failed while opening the file \n";
    }

    inputFile.clear();
    while(std::getline(inputFile, textRead, '\r')) {
        // the read worked and the line is valid
        combinedInput.append(textRead);
    }

    combinedInput.erase(std::remove(combinedInput.begin(), combinedInput.end(), '\n'), combinedInput.end());

    testPlayer->setStorage(combinedInput);

    for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
        for(int col_num = row_num; col_num >= 0; --col_num) {
            outputFile << getTileColourAsString(*testPlayer->getStorageTile(row_num, col_num));
        }
        outputFile << '\n';
    }

    inputFile.close();
    outputFile.close();
}

void PlayerTests::brokenTileTest() {
    cout << "TESTING PLAYER BROKEN TILES ..." << endl;

    std::ifstream inputFile("src/tests/input/broken-input.txt");
    std::ofstream outputFile("src/tests/output/broken-output.txt");
    string brokenInput;
    string brokenOutput;

    if (!inputFile) {
        std::cout << "Something failed while opening the file \n";
    }

    inputFile.clear();
    while(std::getline(inputFile, brokenInput)) {
        // the read worked and the line is valid
    }

    testPlayer->setBrokenTiles(brokenInput);

    for(int i = 0; i < testPlayer->getNumBrokenTiles(); ++i) {
        outputFile << getTileColourAsString(*testPlayer->getBrokenTile(i));
    }

    inputFile.close();
    outputFile.close();
}