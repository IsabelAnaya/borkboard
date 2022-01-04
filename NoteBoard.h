#ifndef NOTEBOARD_H
#define NOTEBOARD_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include "Note.h"

//area for notes
class NoteBoard : public QFrame {
    Q_OBJECT

public:
    explicit NoteBoard(QWidget *parent = nullptr);

    void addNote();
    std::vector<Note*> notes;

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
};

#endif // NOTEBOARD_H
