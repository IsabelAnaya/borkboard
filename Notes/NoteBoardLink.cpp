#include "NoteBoardLink.h"


NoteBoardLink::NoteBoardLink(int board, QString name, QWidget *parent) : Note(parent) {
    setMinimumSize(20, 20);

    button = new BoardSwitchButton(board, name);

    lay = new QVBoxLayout;
    lay->addWidget(button);
    setLayout(lay);

    this->setFrameStyle(QFrame::StyledPanel);
    this->setLineWidth(2);

    show();
    setAttribute(Qt::WA_DeleteOnClose);
}

noteType NoteBoardLink::getType() {
    return noteBoard;
}

NoteBoardLink::~NoteBoardLink() {
    delete button;
    delete lay;
}
