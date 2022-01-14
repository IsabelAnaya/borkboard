#include "Wall.h"

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
    Board *newBoard = new Board();
    newBoard->readData(file);

    std::string temp;
    std::getline(*file, temp);
    int childrensize = stoi(temp);

    for (int i = 0; i < childrensize; i++) {
        BoardNode* child = new BoardNode;
        child->parent = currNode;
        currNode->children.push_back(loadRecurse(file, child));
    }

    return currNode;
}


Wall::Wall() {
    wallName = "New Wall";

    root = new BoardNode();
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

    saveRecurse(file, root);
}

void Wall::readData(std::ifstream *file) {
    std::string temp;
    std::getline(*file, temp); //file version
    std::getline(*file, wallName);

    root = loadRecurse(file, root);

}

Wall::~Wall() {
    delete root->board;
    //this will need more
}
