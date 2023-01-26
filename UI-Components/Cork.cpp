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

NoteText* Cork::addTextNote(int x, int y, int height, int width, QString t, QString c) {
    //std::cout << "new note" << std::endl;
    NoteText *tempo = new NoteText(t, c, this);
    tempo->ID = maxID;

    maxID++;

    tempo->move(x, y);
    notes.push_back(tempo);
    tempo->resize(width, height);

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

NoteBoardLink* Cork::addBoardLinkNote(int x, int y, int height, int width, int board, QString name) {
    NoteBoardLink *tempo = new NoteBoardLink(board, name, this);
    tempo->ID = maxID;

    maxID++;

    tempo->move(x, y);
    notes.push_back(tempo);
    tempo->resize(width, height);

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
    cornerGrabbed = 0;
    initialSize[0] = 0;
    initialSize[1] = 0;
}

void Cork::mouseMoveEvent(QMouseEvent *event) {
    event->pos();

    if (selectedNote) {
        switch (cornerGrabbed) {
        case(0): //moving
            selectedNote->move(event->pos().x() - offset.x(), event->pos().y() - offset.y());
            break;
        case(1): //top left
            selectedNote->move(event->pos().x() - offset.x(), event->pos().y() - offset.y());
            selectedNote->resize(initialSize[0] - event->pos().x() + firstGrab[0], initialSize[1] - event->pos().y() + firstGrab[1]);
            break;
        case(2): //bottom left
            selectedNote->move(event->pos().x() - offset.x(), selectedNote->pos().y());
            selectedNote->resize(initialSize[0] - event->pos().x() + firstGrab[0], initialSize[1] - initialPos.y() + event->pos().y() - offset.y());
            break;
        case(3): //bottom right
            selectedNote->resize(initialSize[0] - initialPos.x() + event->pos().x() - offset.x(), initialSize[1] - initialPos.y() + event->pos().y() - offset.y());
            break;
        case(4): //top right
            selectedNote->move(selectedNote->pos().x(), event->pos().y() - offset.y());
            selectedNote->resize(initialSize[0] - initialPos.x() + event->pos().x() - offset.x(), initialSize[1] - event->pos().y() + firstGrab[1]);
            break;

        }
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

        }

    } else if (event->button() == Qt::LeftButton) {
        selectedNote = static_cast<Note*>(childAt(event->pos()));
        if(!selectedNote) { return; }

        offset = event->pos() - selectedNote->pos();
        initialSize[0] = selectedNote->width(); //correctly offset for resizing
        initialSize[1] = selectedNote->height();
        initialPos = selectedNote->pos();
        firstGrab[0] = event->pos().x();
        firstGrab[1] = event->pos().y();

        selectedNote->raise();
        //check if its in a grabby area. if yes, resize, else get ready to move
        if (((event->pos() - selectedNote->pos()).x() < 10) && ((event->pos() - selectedNote->pos()).y() < 10)) {
            std::cout << "top left" << std::endl;
            cornerGrabbed = 1;

        } else if (((event->pos() - selectedNote->pos()).x() < 10) && ((event->pos() - selectedNote->pos()).y() > selectedNote->height() - 10)) {
            std::cout << "bottom left" << std::endl;
            cornerGrabbed = 2;

        } else if (((event->pos() - selectedNote->pos()).x() > selectedNote->width() - 10) && ((event->pos() - selectedNote->pos()).y() > selectedNote->height() - 10)) {
            std::cout << "bottom right" << std::endl;
            cornerGrabbed = 3;

        } else if (((event->pos() - selectedNote->pos()).x() > selectedNote->width() - 10) && ((event->pos() - selectedNote->pos()).y() < 10)) {
            std::cout << "top right" << std::endl;
            cornerGrabbed = 4;

        //movement moment
        } else {
            std::cout << event->pos().x() << " " << event->pos().y() << std::endl;

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
