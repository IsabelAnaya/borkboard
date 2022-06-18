#include "Wall.h"
#include <iostream>

std::vector<QPushButton*> traverse(Board *node) {
    QPushButton *curr = new QPushButton(QString::fromStdString(node->boardName));
    std::vector<QPushButton*> bits;
    bits.push_back(curr);

    for (unsigned int i = 0; i < node->children.size(); i++) {
        std::vector<QPushButton*> newEnd = traverse(node->children[i]);
        bits.insert(bits.end(), newEnd.begin(), newEnd.end());
    }

    return bits;
}

void saveRecurse(std::ofstream *file, Board *currNode) {
    currNode->saveData(file);
    *file << currNode->children.size() << std::endl;

    for (int i = 0; i < int(currNode->children.size()); i++) {
        saveRecurse(file, currNode->children[i]);
    }
}

Board* loadRecurse(std::ifstream *file, Board* currNode) {
    std::cout << "benchmark 4x: calling board(Wall)" << std::endl;
    Board *newBoard = new Board();
    newBoard->readData(file);

    currNode = newBoard;
    std::cout << "benchmark 4.3: board set" << std::endl;

    std::string temp;
    std::getline(*file, temp);
    temp = "0";
    std::cout << "benchmark 4.4: about to stoi" << std::endl;
    int childrensize = stoi(temp);
    std::cout << "benchmark 4.5: child size " << temp << std::endl;

    for (int i = 0; i < childrensize; i++) {
        Board* child = new Board;
        child->parent = currNode;
        currNode->children.push_back(loadRecurse(file, child));
    }


    return currNode;
}


Wall::Wall() {
    wallName = "New Wall";

    wallNameLabel = new QLabel;
    wallNameLabel->setText(QString::fromStdString(wallName));

    root = new Board();
    root->setName("Root");
    root->ID = 0;
    root->parent = NULL;

    currentBoard = root;

    mainbox = new QGridLayout;
    mainbox->addWidget(root->cork,0, 0, 10, 3);
    mainbox->addWidget(wallNameLabel, 0, 4, 1, 1);
    treeVis = buildTreeVis();
    mainbox->addLayout(treeVis, 1, 4, 9, 1);
}

Sidebar* Wall::buildTreeVis() {
    std::vector<QPushButton*> bits = traverse(root);

    return new Sidebar(bits);
}

void Wall::update() {

    this->wallNameLabel->setText(QString::fromStdString(wallName));

    delete mainbox;

    mainbox = new QGridLayout;
    Sidebar* treeVis = buildTreeVis();
    mainbox->addWidget(currentBoard->cork,0, 0, 10, 3);
    mainbox->addWidget(wallNameLabel, 0, 4, 1, 1);
    mainbox->addLayout(treeVis, 1, 4, 9, 1);
}

void Wall::saveData(std::ofstream *file) {
    *file << "v0.2" << std::endl;
    *file << wallName << std::endl;
    *file << 0 << std::endl;

    saveRecurse(file, root);
}

void Wall::readData(std::ifstream *file) {
    delete root;
    root = new Board;
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
    delete root;
    //this will need more
}
