#ifndef NODE
#define NODE

#include "Tile.h"

class Node {
public:
    Node(Tile::Colour tile, Node* nextNode);
    ~Node();

    Node* getNextNode();
    void setNextNode(Node* nextNode);
    Tile::Colour getTileColour();
private:
    Tile::Colour tile;
    Node* nextNode;
};

#endif // NODE