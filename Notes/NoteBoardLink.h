#ifndef NOTEBOARDLINK_H
#define NOTEBOARDLINK_H

#include "Note.h"
#include "UI-Components/BoardSwitchButton.h"

class NoteBoardLink: public Note {

public:
    NoteBoardLink(int board, QString name, QWidget *parent);
    ~NoteBoardLink();

    void setName(QString name);
    noteType getType() override;
    int getBoardID();

    BoardSwitchButton* button;

protected:
    void resizeEvent(QResizeEvent* event);

private:
    int boardID;
};

#endif // NOTEIMAGE_H
