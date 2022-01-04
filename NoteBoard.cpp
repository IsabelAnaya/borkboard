#include "NoteBoard.h"
#include <iostream>
//https://doc.qt.io/qt-5/qtwidgets-draganddrop-draggableicons-example.html

NoteBoard::NoteBoard(QWidget *parent) : QFrame(parent) {
    setMinimumSize(200, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);

    Note *tempTest = new Note(this);
    notes.push_back(tempTest);

    tempTest->move(10, 10);

    Note *temp2 = new Note(this);
    temp2->move(20, 30);
    notes.push_back(temp2);
}

void NoteBoard::addNote() {
    std::cout << "new note" << std::endl;
    Note *tempo = new Note(this);

    tempo->move(10, 10);
    notes.push_back(tempo);
}

void NoteBoard::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        //std::cout << "dragenter" << std::endl;

        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void NoteBoard::dragMoveEvent(QDragMoveEvent *event) {
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        //std::cout << "dragmove" << std::endl;

        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void NoteBoard::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        //std::cout << "dropevent" << std::endl;

        const QMimeData *mime = event->mimeData();

        QByteArray itemData = mime->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString t;
        QString c;
        QPoint offset;
        dataStream >> t >> c >> offset;

        Note *newnote = new Note(t, c, this);
        newnote->move(event->pos() - offset);
        newnote->show();
        newnote->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void NoteBoard::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        //ask to make new note, or delete if its over a note
        Note *child = static_cast<Note*>(childAt(event->pos()));
        if(!child) {
            std::cout << "right click on empty" << std::endl;
        } else {
            std::cout << "right click on note" << std::endl;
        }

    } else if (event->button() == Qt::LeftButton) {

        Note *child = static_cast<Note*>(childAt(event->pos()));
        if(!child) { return; }

        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << child->title->toPlainText() << child->content->toPlainText() << QPoint(event->pos() - child->pos());

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata", itemData);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        //drag->setPixmap(child->pixmap(Qt::ReturnByValue));
        drag->setHotSpot(event->pos() - child->pos());

        child->hide();
        if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction) {
            child->close();
        } else {
            child->show();
        }
    }
}
