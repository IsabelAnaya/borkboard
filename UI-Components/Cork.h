#ifndef CORK_H
#define CORK_H

#include <QWidget>
#include <QLabel>
#include <QMenu>
#include <QMouseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <stdlib.h>
#include "Notes/Note.h"
#include "Notes/NoteImage.h"
#include "Notes/NoteText.h"
#include "Notes/NoteBoardLink.h"
#include "Notes/NoteSticker.h"

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
    NoteSticker* addStickerNote(int type);
    NoteSticker* addStickerNote(int x, int y, int height, int width, int type);
    void moveNote(Note *note, int xPos, int yPos);

    QMessageBox* confirmDelete;
    std::vector<Note*> notes;
    std::vector<int> order;

private:
    void renumberNotes();
    void changeNoteColor(int c);
    unsigned int maxID = 0;
    Note* movingNote = NULL;
    Note* selectedNote = NULL;
    NoteText* activeNote = NULL;
    QPoint offset;
    QPoint initialPos;
    QPoint newPos;
    int initialSize[2] = {0, 0};
    int firstGrab[2] = {0, 0};
    int cornerGrabbed = 0;
    bool resizing = false;
    bool image = false;
    bool text = false;
    QMenu* menu;
    QMenu* addNoteMenu;
    QMenu* changeColorMenu;
    QAction* removeAction; //needs to be here so it can be switched on
    QAction* changeImageAction;
    QAction* toFrontAction;
    QAction* toBackAction;
    QAction* backOneAction;
    QAction* forwardOneAction;

private slots:
    void newTextSlot();
    void newImageSlot();
    void newBoardNoteSlot();
    void newStickerSlot();
    void removeNoteSlot();
    void changeImageSlot();
    void toFrontSlot();
    void toBackSlot();
    void forwardOneSlot();
    void backOneSlot();

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CORK_H
