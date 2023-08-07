#include "Note.h"

Note::Note(QWidget *parent) : QFrame(parent) {
    this->setProperty("class", "color-1");
}

std::string Note::toText() {
    return "hello";
}

noteType Note::getType() {
    return noteText;
}

int Note::getID() {
    return ID;
}

void Note::setColor(int c) {
    QString colortag = "color-" + QString::number(c);
    this->setProperty("class", colortag);
    this->color = c;
}

Note::~Note() {

}
