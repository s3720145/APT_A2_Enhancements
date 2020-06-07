#include "Node.h"

Node::Node(Tile::Colour tile, Node* nextNode) {
    this->tile = tile;
    this->nextNode = nextNode;
}

Node::~Node() {
    this->nextNode = nullptr;
}

Node* Node::getNextNode() {
    return this->nextNode;
}

void Node::setNextNode(Node* nextNode) {
    this->nextNode = nextNode;
}

Tile::Colour Node::getTileColour() {
    return this->tile;
}