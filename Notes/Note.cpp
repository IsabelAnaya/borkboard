#include "Note.h"

Note::Note(QWidget *parent) : QFrame(parent) {

}

Note::Note(QString t, QString c, QWidget *parent) : QFrame(parent) {

}

void Note::saveData(std::ofstream *file) {

}

void Note::readData(std::ifstream *file) {

}

std::string Note::toText() {
    return "hello";
}

noteType Note::getType() {
    return noteText;
}

Note::~Note() {

}
