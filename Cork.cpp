#include "Cork.h"
#include <iostream>
//https://doc.qt.io/qt-5/qtwidgets-draganddrop-draggableicons-example.html

Cork::Cork(QWidget *parent) : QFrame(parent) {
    setMinimumSize(200, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);

//    Note *tempTest = addNote();
//    tempTest->move(10, 10);

//    Note *temp2 = addNote();
//    temp2->move(20, 30);
}

Note* Cork::addNote() {
    std::cout << "new note" << std::endl;
    Note *tempo = new Note(this);

    tempo->ID = maxID;
    maxID++;

    tempo->move(10, 10);
    notes.push_back(tempo);

    return tempo;
}

Note* Cork::addNote(std::string title, std::string content, int xPos, int yPos) {
    std::cout << "rebuilding note" << std::endl;
    Note *tempo = new Note(this);

    tempo->title->setText(QString::fromStdString(title));
    tempo->content->setText(QString::fromStdString(content));
    tempo->ID = maxID;
    maxID++;

    tempo->move(xPos, yPos);
    notes.push_back(tempo);

    return tempo;
}

void Cork::dragEnterEvent(QDragEnterEvent *event) {
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

void Cork::dragMoveEvent(QDragMoveEvent *event) {
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

void Cork::dropEvent(QDropEvent *event) {
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

void Cork::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        //ask to make new note, or delete if its over a note
        Note *child = static_cast<Note*>(childAt(event->pos()));
        if(!child) {
            std::cout << "right click on empty" << std::endl;
        } else {
            std::cout << "right click on note" << std::endl;
            //std::cout << child->pos().x() << ", " << child->pos().y() << std::endl;
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
