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

NoteBoardLink* Cork::addBoardLinkNote(int x, int y, int board, QString name) {
    NoteBoardLink *tempo = new NoteBoardLink(board, name, this);
    tempo->ID = maxID;

    maxID++;

    tempo->move(x, y);
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
    resizing = false;
}

void Cork::mouseMoveEvent(QMouseEvent *event) {
    event->pos();

    if (selectedNote) {
        if (resizing) {
            selectedNote->resize(initialSize[0] + event->pos().x() - offset.x(), initialSize[1] + event->pos().y() - offset.y());
        } else {
            selectedNote->move(event->pos().x() - offset.x(), event->pos().y() - offset.y());
        }
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

        //check if its in a grabby area. if yes, resize, else get ready to move
        if ((((event->pos() - selectedNote->pos()).x() < 10) && ((event->pos() - selectedNote->pos()).y() < 10)) ||
          (((event->pos() - selectedNote->pos()).x() < 10) && ((event->pos() - selectedNote->pos()).y() > selectedNote->height() - 10)) ||
          (((event->pos() - selectedNote->pos()).x() > selectedNote->width() - 10) && ((event->pos() - selectedNote->pos()).y() < 10)) ||
          (((event->pos() - selectedNote->pos()).x() > selectedNote->width() - 10) && ((event->pos() - selectedNote->pos()).y() > selectedNote->height() - 10))) {

            resizing = true;
            initialSize[0] = selectedNote->width() - selectedNote->pos().x();
            initialSize[1] = selectedNote->height() - selectedNote->pos().y();
            std::cout << "checking the note dimensions; " << selectedNote->pos().x() + selectedNote->width() << ", " << selectedNote->pos().y() + selectedNote->height() << std::endl;

        //movement moment
        } else {
            std::cout << event->pos().x() << " " << event->pos().y() << std::endl;
            selectedNote->raise();
        }
    }
}

Cork::~Cork() {
    selectedNote = NULL; //just in case

    int notesize = notes.size();
    for (int i = 0; i < notesize; i++) {
        delete notes[i];
    }
}
