#include "Board.h"
#include <iostream>

Board::Board() {
    this->bgColor = "background-color:#ffffff";
    this->boardName = "New Board";

    cork = new Cork();
}

Board::Board(std::string bgColor, std::string boardName) {
    this->bgColor = bgColor;
    this->boardName = boardName;

    cork = new Cork();
}

void Board::setColor(std::string bgColor) {
    this->bgColor = bgColor;
}

void Board::setName(std::string boardName) {
    this->boardName = boardName;
}

Board* Board::makeChild(std::string boardName) {
    Board *newB = new Board("background-color:#ffffff", boardName);
    children.push_back(newB);
    newB->parent = this;

    return newB;
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

//    std::getline(*file, boardName);
//    std::cout << "benchmark 5x: getting boardname (Board); " << boardName << std::endl;
//    std::getline(*file, bgColor);
//    std::cout << "benchmark 6x: getting bgcolor (Board); " << bgColor << std::endl;

//    std::string temp;
//    std::getline(*file, temp);
//    std::cout << "benchmark 7x: getting number of notes (Board); " << temp << std::endl;
//    int notesize = stoi(temp);

//    for (int i = 0; i < notesize; i++) {
//        std::cout << "benchmark 8x: starting notes (Board); " << temp << std::endl;
//        Note *newNote = cork->addNote();
//        newNote->readData(file);

//        std::getline(*file, temp);
//        int x = stoi(temp);
//        std::cout << "benchmark 11x: getting x (Board); " << temp << std::endl;

//        std::getline(*file, temp);
//        int y = stoi(temp);
//        std::cout << "benchmark 12x: getting y (Board); " << temp << std::endl;

//        cork->moveNote(newNote, x, y);
//        std::cout << "benchmark 13x: moved notes (Board)" << std::endl;
//    }
}

Board::~Board() {
    delete cork;
}
