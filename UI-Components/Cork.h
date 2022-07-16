#ifndef CORK_H
#define CORK_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QMimeData>
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

    //Note* addNote();
    //Note* addNote(std::string title, std::string content, int xPos, int yPos);
    Note* addTextNote();
    Note* addTextNote(int x, int y, QString t, QString c);
    Note* addImageNote();
    Note* addBoardLinkNote();
    void moveNote(Note *note, int xPos, int yPos);
    std::vector<Note*> notes;

private:
    void renumberNotes();
    unsigned int maxID = 0;
    Note* selectedNote;
    QPoint offset;

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CORK_H
