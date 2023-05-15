#include "Cork.h"
#include <iostream> //testing
//https://doc.qt.io/qt-5/qtwidgets-draganddrop-draggableicons-example.html

Cork::Cork(QWidget *parent) : QFrame(parent) {
    setMinimumSize(200, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
    setContextMenuPolicy(Qt::DefaultContextMenu);
    QAction *addAction = new QAction(tr("&Add new note"), this);
    connect(addAction, &QAction::triggered, this, &Cork::newNoteSlot);
}

void Cork::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    QAction *addAction = new QAction(tr("&Add new note"), this);
    connect(addAction, &QAction::triggered, this, &Cork::newNoteSlot);
    menu.addAction(addAction);

    if (selectedNote) {
        QAction *removeAction = new QAction(tr("&Delete note"), this);
        connect(removeAction, &QAction::triggered, this, &Cork::removeNoteSlot);
        menu.addAction(removeAction);
    }

    newPos = event->pos();
    menu.exec(event->globalPos());
}

void Cork::newNoteSlot() {
    Note* note = addTextNote();
    note->move(newPos);
}

void Cork::removeNoteSlot() {
    if (selectedNote) {
        int id = selectedNote->getID();
        auto it = std::find_if(notes.begin(), notes.end(), [&id](Note* note){ return note->getID() == id; });

        if (it != notes.end()) {
            delete *it;
            notes.erase(it);
        }
    }
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

NoteText* Cork::addTextNote(int x, int y, int height, int width, QString c) {
    //std::cout << "new note" << std::endl;
    NoteText *tempo = new NoteText(c, this);
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
    movingNote = NULL;
    cornerGrabbed = 0;
    initialSize[0] = 0;
    initialSize[1] = 0;
}

void Cork::mouseMoveEvent(QMouseEvent *event) {
    event->pos();

    if (movingNote) {
        switch (cornerGrabbed) {
        case(0): //moving
            movingNote->move(event->pos().x() - offset.x(), event->pos().y() - offset.y());
            break;
        case(1): //top left
            movingNote->move(event->pos().x() - offset.x(), event->pos().y() - offset.y());
            movingNote->resize(initialSize[0] - event->pos().x() + firstGrab[0], initialSize[1] - event->pos().y() + firstGrab[1]);
            break;
        case(2): //bottom left
            movingNote->move(event->pos().x() - offset.x(), movingNote->pos().y());
            movingNote->resize(initialSize[0] - event->pos().x() + firstGrab[0], initialSize[1] - initialPos.y() + event->pos().y() - offset.y());
            break;
        case(3): //bottom right
            movingNote->resize(initialSize[0] - initialPos.x() + event->pos().x() - offset.x(), initialSize[1] - initialPos.y() + event->pos().y() - offset.y());
            break;
        case(4): //top right
            movingNote->move(movingNote->pos().x(), event->pos().y() - offset.y());
            movingNote->resize(initialSize[0] - initialPos.x() + event->pos().x() - offset.x(), initialSize[1] - event->pos().y() + firstGrab[1]);
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
            selectedNote = NULL;
        } else {
            std::cout << "right click on note" << std::endl;
            selectedNote = child;
        }

    } else if (event->button() == Qt::LeftButton) {
        movingNote = static_cast<Note*>(childAt(event->pos()));
        if(!movingNote) { return; }

        offset = event->pos() - movingNote->pos();
        initialSize[0] = movingNote->width(); //correctly offset for resizing
        initialSize[1] = movingNote->height();
        initialPos = movingNote->pos();
        firstGrab[0] = event->pos().x();
        firstGrab[1] = event->pos().y();

        movingNote->raise();
        //check if its in a grabby area. if yes, resize, else get ready to move
        if (((event->pos() - movingNote->pos()).x() < 10) && ((event->pos() - movingNote->pos()).y() < 10)) {
            std::cout << "top left" << std::endl;
            cornerGrabbed = 1;

        } else if (((event->pos() - movingNote->pos()).x() < 10) && ((event->pos() - movingNote->pos()).y() > movingNote->height() - 10)) {
            std::cout << "bottom left" << std::endl;
            cornerGrabbed = 2;

        } else if (((event->pos() - movingNote->pos()).x() > movingNote->width() - 10) && ((event->pos() - movingNote->pos()).y() > movingNote->height() - 10)) {
            std::cout << "bottom right" << std::endl;
            cornerGrabbed = 3;

        } else if (((event->pos() - movingNote->pos()).x() > movingNote->width() - 10) && ((event->pos() - movingNote->pos()).y() < 10)) {
            std::cout << "top right" << std::endl;
            cornerGrabbed = 4;

        //movement moment
        } else {
            std::cout << event->pos().x() << " " << event->pos().y() << std::endl;

        }
    }
}

Cork::~Cork() {
    selectedNote = NULL;
    movingNote = NULL; //just in case

    int notesize = notes.size();
    for (int i = 0; i < notesize; i++) {
        delete notes[i];
    }

    delete addAction;
}
