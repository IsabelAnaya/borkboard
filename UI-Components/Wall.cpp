#include "Wall.h"
#include <iostream>

std::vector<BoardSwitchButton*> traverse(Board *node) {
    qDebug() << "building tree, " << node->boardName;
    BoardSwitchButton *curr = new BoardSwitchButton(node->ID, node->boardName);
    std::vector<BoardSwitchButton*> bits;
    bits.push_back(curr);

    for (unsigned int i = 0; i < node->children.size(); i++) {
        std::vector<BoardSwitchButton*> newEnd = traverse(node->children[i]);
        bits.insert(bits.end(), newEnd.begin(), newEnd.end());
    }

    return bits;
}

Wall::Wall() {
    wallName = "New Wall";

    wallNameLabel = new QLabel;
    wallNameLabel->setText(wallName);

    root = new Board();
    root->setName("Root");
    root->ID = 0;
    root->parent = NULL;

    currentBoard = root;
    boardMap = new Board* [MAX_BOARDS];
    boardMap[0] = root;

    mainbox = new QGridLayout;
    mainbox->addWidget(root->cork,0, 0, 10, 3);
    mainbox->addWidget(wallNameLabel, 0, 4, 1, 1);
    treeVis = buildTreeVis();
    mainbox->addLayout(treeVis, 1, 4, 9, 1);
}

//sets the wall's name and root board
Wall::Wall(QString name, QString bgColor, QString rootName) {
    wallName = name;

    wallNameLabel = new QLabel;
    wallNameLabel->setText(wallName);

    root = new Board(bgColor, rootName);
    root->ID = 0;
    root->parent = NULL;

    currentBoard = root;
    boardMap = new Board* [MAX_BOARDS];
    boardMap[0] = root;

    mainbox = new QGridLayout;
    mainbox->addWidget(root->cork,0, 0, 10, 3);
    mainbox->addWidget(wallNameLabel, 0, 4, 1, 1);
    treeVis = buildTreeVis();
    mainbox->addLayout(treeVis, 1, 4, 9, 1);
}

Board* Wall::addBoard(Board* parent, QString name) {
    if (boardsStored < MAX_BOARDS) {
        Board* child = parent->makeNewChild(name);
        child->ID = maxID % MAX_BOARDS;
        boardMap[maxID] =  child;

        maxID++;
        return child;

    } else {
        return NULL;
    }
}

Sidebar* Wall::buildTreeVis() {
    std::vector<BoardSwitchButton*> bits = traverse(root);

    return new Sidebar(bits);
}

void Wall::changeBoard(int board) {
    currentBoard = boardMap[board];
}

void Wall::update() {

    qDebug() << wallName;
    this->wallNameLabel->setText(wallName);

    delete mainbox;

    mainbox = new QGridLayout;
    Sidebar* treeVis = buildTreeVis();
    mainbox->addWidget(currentBoard->cork,0, 0, 10, 3);
    mainbox->addWidget(wallNameLabel, 0, 4, 1, 1);
    mainbox->addLayout(treeVis, 1, 4, 9, 1);
}

Wall::~Wall() {
    std::cout << "deletin (Wall)" << std::endl;
    delete root;
    delete wallNameLabel;
    delete mainbox;
    //delete treeVis;
    //currentBoard should hopefully get deleted in the board deletion
}
