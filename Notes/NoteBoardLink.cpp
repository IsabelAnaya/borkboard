#include "NoteBoardLink.h"

NoteBoardLink::NoteBoardLink(QWidget *parent) : Note(parent) {
    setMinimumSize(20, 20);

    thing = new QPushButton("New Board", this);

    lay = new QVBoxLayout;
    lay->addWidget(thing);
    setLayout(lay);
    //board = NULL;

    this->setFrameStyle(QFrame::StyledPanel);
    this->setLineWidth(2);

    show();
    setAttribute(Qt::WA_DeleteOnClose);
}

//NoteBoardLink::NoteBoardLink(Board* b, QWidget *parent) : Note(parent) {
//    setMinimumSize(20, 20);

//    thing = new QPushButton(QString::fromStdString(b->boardName), this);
//    //board = b;

//    lay = new QVBoxLayout;
//    lay->addWidget(thing);
//    setLayout(lay);

//    this->setFrameStyle(QFrame::StyledPanel);
//    this->setLineWidth(2);

//    show();
//    setAttribute(Qt::WA_DeleteOnClose);
//}

void NoteBoardLink::saveData(std::ofstream *file) {

}

void NoteBoardLink::readData(std::ifstream *file) {

}

std::string NoteBoardLink::toText() {
    return thing->text().toStdString();
}

noteType NoteBoardLink::getType() {
    return noteBoard;
}



NoteBoardLink::~NoteBoardLink() {

}
