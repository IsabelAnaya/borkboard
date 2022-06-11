#ifndef BOARD_H
#define BOARD_H

#include <QString>
#include <list>
#include "Notes/Note.h"
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
    void readData(std::ifstream *file);

    std::string bgColor;
    std::string boardName;
    unsigned int ID;

    Cork* cork;

};

#endif // BOARD_H
