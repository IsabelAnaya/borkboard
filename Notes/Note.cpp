#include "Note.h"

Note::Note(QWidget *parent) : QFrame(parent) {

}

std::string Note::toText() {
    return "hello";
}

noteType Note::getType() {
    return noteText;
}

Note::~Note() {

}
