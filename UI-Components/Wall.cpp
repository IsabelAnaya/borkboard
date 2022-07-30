#include "Wall.h"
#include <iostream>

Wall::Wall() {
    wallName = "New Wall";

    root = new Board();
    root->setName("Root");
    root->ID = 0;
    root->parent = NULL;

    currentBoard = root;
    boardMap = new Board* [MAX_BOARDS];
    boardMap[0] = root;
}

//sets the wall's name and root board
Wall::Wall(QString name, QString bgColor, QString rootName) {
    wallName = name;

    root = new Board(bgColor, rootName);
    root->ID = 0;
    root->parent = NULL;

    currentBoard = root;
    boardMap = new Board* [MAX_BOARDS];
    boardMap[0] = root;
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

void Wall::changeBoard(int board) {
    currentBoard = boardMap[board];
}

std::vector<BoardSwitchButton*>* Wall::updateTree(Board *node) {
    qDebug() << "building tree, " << node->boardName;
    BoardSwitchButton *curr = new BoardSwitchButton(node->ID, node->boardName);
    std::vector<BoardSwitchButton*> *bits = new std::vector<BoardSwitchButton*>;
    bits->push_back(curr);

    for (unsigned int i = 0; i < node->children.size(); i++) {
        std::vector<BoardSwitchButton*> *newEnd = updateTree(node->children[i]);
        bits->insert(bits->end(), newEnd->begin(), newEnd->end());

        //delete newEnd;
    }

    return bits;
}

Wall::~Wall() {
    std::cout << "deletin (Wall)" << std::endl;
    delete root;
}
