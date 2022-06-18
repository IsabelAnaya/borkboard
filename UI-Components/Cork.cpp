#include "Cork.h"
#include <iostream> //testing
//https://doc.qt.io/qt-5/qtwidgets-draganddrop-draggableicons-example.html

Cork::Cork(QWidget *parent) : QFrame(parent) {
    setMinimumSize(200, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
}

Note* Cork::addTextNote() {
    //std::cout << "new note" << std::endl;
    Note *tempo = new NoteText(this);
    tempo->ID = maxID;

    maxID++;

    tempo->move(10, 10);
    notes.push_back(tempo);

    return tempo;
}

Note* Cork::addImageNote() {
    //std::cout << "new note" << std::endl;
    Note *tempo = new NoteImage(this);
    tempo->ID = maxID;

    maxID++;

    tempo->move(10, 10);
    notes.push_back(tempo);

    return tempo;
}

Note* Cork::addBoardLinkNote() {
    Note *tempo = new NoteBoardLink(this);
    tempo->ID = maxID;

    maxID++;

    tempo->move(20, 20);
    notes.push_back(tempo);

    return tempo;
}

//Note* Cork::addNote(std::string title, std::string content, int xPos, int yPos) {
//    //std::cout << "rebuilding note" << std::endl;
//    Note *tempo = new Note(this);
//    tempo->ID = maxID;

//    maxID++;

////    tempo->title->setText(QString::fromStdString(title));
////    tempo->content->setText(QString::fromStdString(content));
//    tempo->move(xPos, yPos);
//    notes.push_back(tempo);

//    return tempo;
//}

void Cork::moveNote(Note *note, int xPos, int yPos) {
    note->move(xPos, yPos);
}

void Cork::renumberNotes() {
    maxID = notes.size();
    for (int i = 0; i < int(maxID); i++) {
        notes[i]->ID = i;
    }
}

void Cork::mouseReleaseEvent(QMouseEvent *event) {
    selectedNote = NULL;
}

void Cork::mouseMoveEvent(QMouseEvent *event) {
    event->pos();

    if (selectedNote) {
        selectedNote->move(event->pos().x() - offset.x(), event->pos().y() - offset.y());
    }
    //move selected child relative to offset from note's origin

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
        selectedNote = static_cast<Note*>(childAt(event->pos()));
        if(!selectedNote) { return; }

        offset = event->pos() - selectedNote->pos();
        std::cout << selectedNote->mapTo(this, selectedNote->pos()).x() << " " << selectedNote->mapTo(this, selectedNote->pos()).y() << std::endl;
        std::cout << event->pos().x() << " " << event->pos().y() << std::endl;
    }
}

Cork::~Cork() {
    int notesize = notes.size();
    for (int i = 0; i < notesize; i++) {
        delete notes[i];
    }
}
