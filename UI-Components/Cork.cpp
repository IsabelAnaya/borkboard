#include "Cork.h"
#include <iostream> //testing
//https://doc.qt.io/qt-5/qtwidgets-draganddrop-draggableicons-example.html

Cork::Cork(QWidget *parent) : QFrame(parent) {
    setMinimumSize(200, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
    setContextMenuPolicy(Qt::DefaultContextMenu);
}

void Cork::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    QAction *addAction = new QAction(tr("&Add new note"), this);
    connect(addAction, &QAction::triggered, this, &Cork::newNoteSlot);
    QAction *addStickerAction = new QAction(tr("&Add sticker"), this);
    connect(addStickerAction, &QAction::triggered, this, &Cork::newStickerSlot);
    menu.addAction(addAction);
    menu.addAction(addStickerAction);

    if (selectedNote) {
        QAction *removeAction = new QAction(tr("&Delete note"), this);
        connect(removeAction, &QAction::triggered, this, &Cork::removeNoteSlot);
        menu.addAction(removeAction);

        if (selectedNote->getType() == noteImage) {
            QAction *changeImageAction = new QAction(tr("&Change Picture"), this);
            connect(changeImageAction, &QAction::triggered, this, &Cork::changeImageSlot);
            menu.addAction(changeImageAction);
        }

        if (selectedNote->getType() != noteSticker) {
            QAction *color1Action = new QAction(tr("&Color 1"), this);
            connect(color1Action, &QAction::triggered, this, [this](){changeNoteColor(1);});
            menu.addAction(color1Action);

            QAction *color2Action = new QAction(tr("&Color 2"), this);
            connect(color2Action, &QAction::triggered, this, [this](){changeNoteColor(2);});
            menu.addAction(color2Action);

            QAction *color3Action = new QAction(tr("&Color 3"), this);
            connect(color3Action, &QAction::triggered, this, [this](){changeNoteColor(3);});
            menu.addAction(color3Action);

            QAction *color4Action = new QAction(tr("&Color 4"), this);
            connect(color4Action, &QAction::triggered, this, [this](){changeNoteColor(4);});
            menu.addAction(color4Action);

            QAction *color5Action = new QAction(tr("&Color 5"), this);
            connect(color5Action, &QAction::triggered, this, [this](){changeNoteColor(5);});
            menu.addAction(color5Action);
        }
    }

    newPos = event->pos();
    menu.exec(event->globalPos());
}

void Cork::changeNoteColor(int c) {
    selectedNote->setColor(c);
    setStyleSheet(styleSheet()); // head in my hands. this is stupid but it works
}

void Cork::newNoteSlot() {
    Note* note = addTextNote();
    note->move(newPos);
}

void Cork::newStickerSlot() {
    NoteSticker* note = addStickerNote(0);
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

void Cork::changeImageSlot() {
    if (selectedNote && selectedNote->getType() == noteImage) {
        //ask for new pic
        QFileDialog dialog;
        QString newPath = dialog.getOpenFileName(this, tr("Choose Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

        if (newPath != "") {
            static_cast<NoteImage*>(selectedNote)->changeImage(newPath);
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

NoteImage* Cork::addImageNote(int x, int y, int height, int width, QString c) {
    //std::cout << "new note" << std::endl;
    NoteImage *tempo = new NoteImage(c, this);
    tempo->ID = maxID;

    maxID++;

    tempo->move(x, y);
    notes.push_back(tempo);
    tempo->resize(width, height);

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

NoteSticker* Cork::addStickerNote(int type) {
    NoteSticker *tempo = new NoteSticker(this);
    tempo->ID = maxID;

    maxID++;

    tempo->move(20, 20);
    notes.push_back(tempo);

    tempo->setStyleSheet("* { border: 0 } *:hover { border: 10px } ");

    return tempo;
}

NoteSticker* Cork::addStickerNote(int x, int y, int height, int width, int type) {
    NoteSticker *tempo = new NoteSticker(type, this);
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
    image = false;
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
            if (!image) {
                movingNote->move(event->pos().x() - offset.x(), event->pos().y() - offset.y());
                movingNote->resize(initialSize[0] - event->pos().x() + firstGrab[0], initialSize[1] - event->pos().y() + firstGrab[1]);
            } else {
                int initialW = movingNote->width();
                movingNote->resize(initialSize[0] - event->pos().x() + firstGrab[0], initialSize[1] - event->pos().y() + firstGrab[1]);
                movingNote->move(movingNote->pos().x() + (initialW - movingNote->width()), event->pos().y() - offset.y());
            }
            break;
        case(2): //bottom left
            if (!image) {
                movingNote->move(event->pos().x() - offset.x(), movingNote->pos().y());
                movingNote->resize(initialSize[0] - event->pos().x() + firstGrab[0], initialSize[1] - initialPos.y() + event->pos().y() - offset.y());
            } else  {
                int initialW = movingNote->width();
                movingNote->resize(initialSize[0] - event->pos().x() + firstGrab[0], initialSize[1] - initialPos.y() + event->pos().y() - offset.y());
                movingNote->move(movingNote->pos().x() + (initialW - movingNote->width()), movingNote->pos().y());
            }
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
            if (activeNote){
                activeNote->toMarkdown();
                activeNote = NULL;
            }
            std::cout << "right click on empty" << std::endl;
            selectedNote = NULL;
            qDebug() << "right click test";
        } else {
            std::cout << "right click on note" << std::endl;
            selectedNote = child;
            qDebug() << selectedNote->color;
        }

    } else if (event->button() == Qt::LeftButton) {
        movingNote = static_cast<Note*>(childAt(event->pos()));
        if(!movingNote) {
            if (activeNote){
                activeNote->toMarkdown();
                activeNote = NULL;
            }

            return;
        }

        offset = event->pos() - movingNote->pos();
        initialSize[0] = movingNote->width(); //correctly offset for resizing
        initialSize[1] = movingNote->height();
        initialPos = movingNote->pos();
        firstGrab[0] = event->pos().x();
        firstGrab[1] = event->pos().y();

        movingNote->raise();
        if (movingNote->getType() == noteImage) {
            image = true;
        }

        if (movingNote->getType() == noteText) {
            if (activeNote && activeNote != movingNote) {
                activeNote->toMarkdown();
            }
            activeNote = static_cast<NoteText*>(movingNote);
            activeNote->toPlaintext();
        } else if (activeNote){
            activeNote->toMarkdown();
            activeNote = NULL;
        }

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

    //delete addAction;
}
