#include "BoardSwitchButton.h"
#include <iostream>

BoardSwitchButton::BoardSwitchButton(int board, QString name) {
    setText(name);
    boardID = board;
    connect(this, &QAbstractButton::released, this, &BoardSwitchButton::emitSignal);
}

void BoardSwitchButton::setName(QString name) {
    setText(name);
}

void BoardSwitchButton::emitSignal() {
    std::cout << "trying to emit " << boardID << std::endl;
    emit boardSwitch(boardID);
}

BoardSwitchButton::~BoardSwitchButton() {

}
