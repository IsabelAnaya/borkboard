#include "Board.h"
#include <cstring>

Board::Board() {
    this->bgColor = new char[26];
    strncpy(this->bgColor, "background-color:#ffffff", 25);

    this->boardName = new char[26];
    strncpy(this->boardName, "New Board", 25);

    cork = new Cork();
}

Board::Board(QString bgColor, QString boardName) {
    this->bgColor = new char[26];
    strncpy(this->bgColor, bgColor.toLocal8Bit().data(), 25);

    this->boardName = new char[26];
    strncpy(this->boardName, boardName.toLocal8Bit().data(), 25);

    cork = new Cork();
}

void Board::setColor(QString bgColor) {
    strncpy(this->bgColor, bgColor.toLocal8Bit().data(), 25);
}

void Board::setName(QString boardName) {
    strncpy(this->boardName, boardName.toLocal8Bit().data(), 25);
}

void Board::saveData(std::ofstream *file) {
    *file << boardName << std::endl;
    *file << bgColor << std::endl;

    int notesize = cork->notes.size();
    *file << notesize << std::endl;

    for (int i = 0; i < notesize; i++) {
        cork->notes[i]->saveData(file);
    }
}

Board::~Board() {
    delete[] bgColor;
    delete[] boardName;
    delete cork;
}
