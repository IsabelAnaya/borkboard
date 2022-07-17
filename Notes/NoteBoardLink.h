#ifndef NOTEBOARDLINK_H
#define NOTEBOARDLINK_H

#include "Note.h"
//#include "UI-Components/Board.h"
#include <QPushButton>

class NoteBoardLink: public Note {
    Q_OBJECT

public:
    explicit NoteBoardLink(QWidget *parent = nullptr);
    NoteBoardLink(int board, QString name, QWidget *parent);
    ~NoteBoardLink();

    std::string toText() override;
    noteType getType() override;
    void emitSignal();

    QPushButton* thing;
    int boardID;

signals:
    void boardSwitch(int board);
};

#endif // NOTEIMAGE_H
