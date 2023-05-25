#ifndef CORK_H
#define CORK_H

#include <QWidget>
#include <QLabel>
#include <QMenu>
#include <QMouseEvent>
#include <QFileDialog>
#include <stdlib.h>
#include "Notes/Note.h"
#include "Notes/NoteImage.h"
#include "Notes/NoteText.h"
#include "Notes/NoteBoardLink.h"

//area for notes
class Cork : public QFrame {
    Q_OBJECT

public:
    explicit Cork(QWidget *parent = nullptr);
    ~Cork();

    //could replace addNotes with 1 variant, use default values...
    NoteText* addTextNote();
    NoteText* addTextNote(int x, int y, int height, int width, QString c);

    NoteImage* addImageNote();
    NoteImage* addImageNote(int x, int y, int height, int width, QString c);
    NoteBoardLink* addBoardLinkNote(int board, QString name);
    NoteBoardLink* addBoardLinkNote(int x, int y, int height, int width, int board, QString name);
    void moveNote(Note *note, int xPos, int yPos);
    std::vector<Note*> notes;

private:
    void renumberNotes();
    unsigned int maxID = 0;
    Note* movingNote;
    Note* selectedNote;
    QPoint offset;
    QPoint initialPos;
    QPoint newPos;
    int initialSize[2] = {0, 0};
    int firstGrab[2] = {0, 0};
    int cornerGrabbed = 0;
    bool resizing = false;

private slots:
    void newNoteSlot();
    void removeNoteSlot();
    void changeImageSlot();

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CORK_H
