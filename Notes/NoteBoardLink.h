#ifndef NOTEBOARDLINK_H
#define NOTEBOARDLINK_H

#include "Note.h"
#include "UI-Components/BoardSwitchButton.h"

class NoteBoardLink: public Note {

public:
    NoteBoardLink(int board, QString name, QWidget *parent);
    ~NoteBoardLink();

    noteType getType() override;

    BoardSwitchButton* button;
};

#endif // NOTEIMAGE_H
