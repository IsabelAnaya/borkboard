#ifndef CORK_H
#define CORK_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include "Note.h"

//area for notes
class Cork : public QFrame {
    Q_OBJECT

public:
    explicit Cork(QWidget *parent = nullptr);

    void addNote();
    std::vector<Note*> notes;

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CORK_H
