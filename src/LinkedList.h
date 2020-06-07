#ifndef LINKEDLIST
#define LINKEDLIST

#include "Node.h"
#include <string>

using std::string;

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    int size();
    void addBack(Tile::Colour colour);
    Node* dequeue();
    Node* getHeader();
    string getAllTilesAsString();
private:
    Node* head;
};

#endif // LINKEDLIST
