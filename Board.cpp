#include "Board.h"

Board::Board() {
    this->bgColor = "background-color:#ffffff";
    this->boardName = "New Board";

    cork = new Cork();
}

Board::Board(QString bgColor, QString boardName) {
    this->bgColor = bgColor.toStdString();
    this->boardName = boardName.toStdString();

    cork = new Cork();
}

void Board::setColor(QString bgColor) {
    this->bgColor = bgColor.toStdString();
}

void Board::setName(QString boardName) {
    this->boardName = boardName.toStdString();
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

void Board::readData(std::ifstream *file) {
    std::getline(*file, boardName);
    std::getline(*file, bgColor);

    std::string temp;
    std::getline(*file, temp);
    int notesize = stoi(temp);

    for (int i = 0; i < notesize; i++) {
        Note *newNote = cork->addNote();
        newNote->readData(file);
    }
}

Board::~Board() {
    delete cork;
}
