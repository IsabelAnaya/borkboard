#ifndef CORK_H
#define CORK_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
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
    Note* addImageNote();
    Note* addBoardLinkNote();
    void moveNote(Note *note, int xPos, int yPos);
    std::vector<Note*> notes;

private:
    void renumberNotes();
    unsigned int maxID = 0;

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CORK_H
