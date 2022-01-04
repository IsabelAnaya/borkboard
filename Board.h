#ifndef BOARD_H
#define BOARD_H

#include <QString>
#include <list>
#include "Note.h"
#include "NoteBoard.h"

//contain info for individual board
class Board  {
public:
    Board();
    Board(QString bgColor, QString boardName);

    void setName(QString boardName);
    void setColor(QString bgColor);

    char* bgColor;
    char* boardName;
    unsigned int ID;

    NoteBoard* cork;

};

#endif // BOARD_H
