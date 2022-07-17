#include "NoteBoardLink.h"

NoteBoardLink::NoteBoardLink(QWidget *parent) : Note(parent) {
    setMinimumSize(20, 20);

    thing = new QPushButton("New Board", this);
    connect(thing, &QAbstractButton::released, this, &NoteBoardLink::emitSignal);

    lay = new QVBoxLayout;
    lay->addWidget(thing);
    setLayout(lay);
    //board = NULL;

    this->setFrameStyle(QFrame::StyledPanel);
    this->setLineWidth(2);

    show();
    setAttribute(Qt::WA_DeleteOnClose);
}

NoteBoardLink::NoteBoardLink(int board, QString name, QWidget *parent) : Note(parent) {
    setMinimumSize(20, 20);

    thing = new QPushButton(name, this);
    connect(thing, &QAbstractButton::released, this, &NoteBoardLink::emitSignal);
    boardID = board;

    lay = new QVBoxLayout;
    lay->addWidget(thing);
    setLayout(lay);

    this->setFrameStyle(QFrame::StyledPanel);
    this->setLineWidth(2);

    show();
    setAttribute(Qt::WA_DeleteOnClose);
}

void NoteBoardLink::emitSignal() {
    emit boardSwitch(boardID);
}

std::string NoteBoardLink::toText() {
    return thing->text().toStdString();
}

noteType NoteBoardLink::getType() {
    return noteBoard;
}

NoteBoardLink::~NoteBoardLink() {
    delete thing;
    delete lay;
}
