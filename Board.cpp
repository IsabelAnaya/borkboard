#include "Board.h"
#include <cstring>
#include <valarray>

Board::Board() {
    this->bgColor = new char[26];
    this->boardName = new char[26];
    strncpy(this->boardName, "New Board", 25);
    strncpy(this->bgColor, "#ffffff", 25);

    cork = new NoteBoard();
}

Board::Board(QString bgColor, QString boardName) {
    this->bgColor = new char[26];
    strncpy(this->bgColor, bgColor.toLocal8Bit().data(), 25);

    this->boardName = new char[26];
    strncpy(this->boardName, boardName.toLocal8Bit().data(), 25);

    this->ID = 0;
}

void Board::setColor(QString bgColor) {
    strncpy(this->bgColor, bgColor.toLocal8Bit().data(), 25);
}

void Board::setName(QString boardName) {
    strncpy(this->boardName, boardName.toLocal8Bit().data(), 25);
}
