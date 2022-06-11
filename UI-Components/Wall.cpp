#include "Wall.h"
#include <iostream>

std::vector<QPushButton*> traverse(BoardNode *node) {
    QPushButton *curr = new QPushButton(QString::fromStdString(node->board->boardName));
    std::vector<QPushButton*> bits;
    bits.push_back(curr);

    for (unsigned int i = 0; i < node->children.size(); i++) {
        std::vector<QPushButton*> newEnd = traverse(node->children[i]);
        bits.insert(bits.end(), newEnd.begin(), newEnd.end());
    }

    return bits;
}

void saveRecurse(std::ofstream *file, BoardNode *currNode) {
    currNode->board->saveData(file);
    *file << currNode->children.size() << std::endl;

    for (int i = 0; i < int(currNode->children.size()); i++) {
        saveRecurse(file, currNode->children[i]);
    }
}

BoardNode* loadRecurse(std::ifstream *file, BoardNode* currNode) {
    std::cout << "benchmark 4x: calling board(Wall)" << std::endl;
    Board *newBoard = new Board();
    newBoard->readData(file);

    currNode->board = newBoard;
    std::cout << "benchmark 4.3: board set" << std::endl;

    std::string temp;
    std::getline(*file, temp);
    temp = "0";
    std::cout << "benchmark 4.4: about to stoi" << std::endl;
    int childrensize = stoi(temp);
    std::cout << "benchmark 4.5: child size " << temp << std::endl;

    for (int i = 0; i < childrensize; i++) {
        BoardNode* child = new BoardNode;
        child->parent = currNode;
        currNode->children.push_back(loadRecurse(file, child));
    }


    return currNode;
}


Wall::Wall() {
    wallName = "New Wall";

    root = new BoardNode;
    root->board = new Board();
    root->board->setName("Root");
    root->board->ID = 0;
    root->parent = NULL;
}

Sidebar* Wall::buildTreeVis() {
    std::vector<QPushButton*> bits = traverse(root);

    return new Sidebar(bits);
}

void Wall::saveData(std::ofstream *file) {
    *file << "v0.1" << std::endl;
    *file << wallName << std::endl;
    *file << 0 << std::endl;

    saveRecurse(file, root);
}

void Wall::readData(std::ifstream *file) {
    delete root;
    root = new BoardNode;
    root->parent = NULL;

    std::string temp;
    std::getline(*file, temp); //file version
    std::cout << "benchmark 2: file version (Wall); " << temp << std::endl;
    std::getline(*file, wallName);
    std::cout << "benchmark 3: wall name (Wall); " << wallName << std::endl;

    root = loadRecurse(file, root);

}

Wall::~Wall() {
    std::cout << "deletin (Wall)" << std::endl;
    delete root->board;
    //this will need more
}
