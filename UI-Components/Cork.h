#ifndef CORK_H
#define CORK_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
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
    NoteText* addTextNote(int x, int y, QString t, QString c);
    NoteImage* addImageNote();
    NoteBoardLink* addBoardLinkNote(int board, QString name);
    NoteBoardLink* addBoardLinkNote(int x, int y, int board, QString name);
    void moveNote(Note *note, int xPos, int yPos);
    std::vector<Note*> notes;

private:
    void renumberNotes();
    unsigned int maxID = 0;
    Note* selectedNote;
    QPoint offset;
    QPoint initialPos;
    int initialSize[2] = {0, 0};
    int firstGrab[2] = {0, 0};
    int cornerGrabbed = 0;
    bool resizing = false;

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CORK_H
