#include "LinkedList.h"

LinkedList::LinkedList() {
    head = nullptr;
}

LinkedList::~LinkedList() {
    Node* n = head;
    Node* currentNode = nullptr;

    while (n != nullptr) {
        currentNode = n;
        n = n->getNextNode();
        delete(currentNode);
    }
    
    head = nullptr;
}

int LinkedList::size() {
    int count = 0;
    Node* currentNode = head;

    while (currentNode != nullptr) {
        ++count;
        currentNode = currentNode->getNextNode();
    }
    
    return count;
}

void LinkedList::addBack(Tile::Colour colour) {
    Node* newNode = new Node(colour, nullptr);

    // Check if head is null
    if (head == nullptr) {
        head = newNode;
    }
    else {
        Node* currentNode = head;

        // Loop until next node is null
        while (currentNode->getNextNode() != nullptr) {
            currentNode = currentNode->getNextNode();
        }

        // Set next node to parameter node
        currentNode->setNextNode(newNode);
    }

}

Node* LinkedList::dequeue() {
    Node* removeNode = nullptr;
    // Check head
    if (head != nullptr) {
        
        removeNode = head;
        
        // Head will take up next pointer
        head = removeNode->getNextNode();

        // Set next pointer to null
        removeNode->setNextNode(nullptr);
    }
    
    return removeNode;
}

Node* LinkedList::getHeader() {
    return this->head;
}

string LinkedList::getAllTilesAsString() {
    string tiles;
    Node* currentNode = head;

    while (currentNode != nullptr) {
        tiles += Tile::getTileColourAsString(currentNode->getTileColour());
        currentNode = currentNode->getNextNode();
    }

    return tiles;
}