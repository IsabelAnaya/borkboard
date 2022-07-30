#include "Cork.h"
#include <iostream> //testing
//https://doc.qt.io/qt-5/qtwidgets-draganddrop-draggableicons-example.html

Cork::Cork(QWidget *parent) : QFrame(parent) {
    setMinimumSize(200, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
}

NoteText* Cork::addTextNote() {
    //std::cout << "new note" << std::endl;
    NoteText *tempo = new NoteText(this);
    tempo->ID = maxID;

    maxID++;

    tempo->move(10, 10);
    notes.push_back(tempo);

    return tempo;
}

NoteText* Cork::addTextNote(int x, int y, QString t, QString c) {
    //std::cout << "new note" << std::endl;
    NoteText *tempo = new NoteText(t, c, this);
    tempo->ID = maxID;

    maxID++;

    tempo->move(x, y);
    notes.push_back(tempo);

    return tempo;
}

NoteImage* Cork::addImageNote() {
    //std::cout << "new note" << std::endl;
    NoteImage *tempo = new NoteImage(this);
    tempo->ID = maxID;

    maxID++;

    tempo->move(10, 10);
    notes.push_back(tempo);

    return tempo;
}

NoteBoardLink* Cork::addBoardLinkNote(int board, QString name) {
    NoteBoardLink *tempo = new NoteBoardLink(board, name, this);
    tempo->ID = maxID;

    maxID++;

    tempo->move(20, 20);
    notes.push_back(tempo);

    return tempo;
}

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
        }

    } else if (event->button() == Qt::LeftButton) {
        selectedNote = static_cast<Note*>(childAt(event->pos()));
        if(!selectedNote) { return; }

        offset = event->pos() - selectedNote->pos();
        std::cout << selectedNote->mapTo(this, selectedNote->pos()).x() << " " << selectedNote->mapTo(this, selectedNote->pos()).y() << std::endl;
        std::cout << event->pos().x() << " " << event->pos().y() << std::endl;
        selectedNote->raise();
    }
}

Cork::~Cork() {
    selectedNote = NULL; //just in case

    int notesize = notes.size();
    for (int i = 0; i < notesize; i++) {
        delete notes[i];
    }
}
