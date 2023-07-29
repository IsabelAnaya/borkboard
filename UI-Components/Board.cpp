#include "Board.h"
#include <iostream>

Board::Board() {
    this->bgColor = "background-color:#ffffff";
    this->boardName = "New Board";

    cork = new Cork();
}

Board::Board(QString name) {
    boardName = name;

    cork = new Cork();
}

void Board::setColor(QString color) {
    bgColor = color;
}

void Board::setName(QString boardName) {
    this->boardName = boardName;
}

Board* Board::makeNewChild(QString boardName) {
    Board *newB = new Board(boardName);
    children.push_back(newB);
    newB->parent = ID;

    return newB;
}

std::vector<Note*> Board::findAllNotesOfType(noteType type) {
    std::vector<Note*> matching;

    for (unsigned int i = 0; i < cork->notes.size(); i++) {
        if (cork->notes[i]->getType() == type) {
            matching.push_back(cork->notes[i]);
        }
    }

    return matching;
}

Board::~Board() {
    for (unsigned int i = 0; i < children.size(); i++) {
        delete children[i];
    }
    delete cork;
}
