#include "NoteBoardLink.h"


NoteBoardLink::NoteBoardLink(int board, QString name, QWidget *parent) : Note(parent) {
    setMinimumSize(20, 20);

    button = new BoardSwitchButton(board, name);
    button->resize(100, 100);
    boardID = board;

    lay = new QVBoxLayout;
    lay->addWidget(button);
    setLayout(lay);

    this->setFrameStyle(QFrame::StyledPanel);
    this->setLineWidth(2);

    show();
    setAttribute(Qt::WA_DeleteOnClose);
}

void NoteBoardLink::setName(QString name) {
    button->setName(name);
}

int NoteBoardLink::getBoardID() {
    return boardID;
}

noteType NoteBoardLink::getType() {
    return noteBoard;
}

void NoteBoardLink::resizeEvent(QResizeEvent *event) {
    button->setFixedSize(this->size().width() - 20, this->size().height() - 20);
}

NoteBoardLink::~NoteBoardLink() {
    delete button;
    delete lay;
}
