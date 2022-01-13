#ifndef BOARD_H
#define BOARD_H

#include <QString>
#include <list>
#include "Note.h"
#include "Cork.h"

//contain info for individual board
class Board  {
public:
    Board();
    Board(QString bgColor, QString boardName);
    ~Board();

    void setName(QString boardName);
    void setColor(QString bgColor);

    void saveData(std::ofstream *file);

    char* bgColor;
    char* boardName;
    unsigned int ID;

    Cork* cork;

};

#endif // BOARD_H
