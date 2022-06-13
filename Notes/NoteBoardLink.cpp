#include "NoteBoardLink.h"

NoteBoardLink::NoteBoardLink(QWidget *parent) : Note(parent) {
    setMinimumSize(20, 20);

    thing = new QPushButton("New Board", this);

    lay = new QVBoxLayout;
    lay->addWidget(thing);
    setLayout(lay);

    this->setFrameStyle(QFrame::StyledPanel);
    this->setLineWidth(2);

    show();
    setAttribute(Qt::WA_DeleteOnClose);
}

NoteBoardLink::NoteBoardLink(QString t, QWidget *parent) : Note(parent) {
    setMinimumSize(20, 20);

    thing = new QPushButton(t, this);

    lay = new QVBoxLayout;
    lay->addWidget(thing);
    setLayout(lay);

    this->setFrameStyle(QFrame::StyledPanel);
    this->setLineWidth(2);

    show();
    setAttribute(Qt::WA_DeleteOnClose);
}

NoteBoardLink::~NoteBoardLink() {

}
