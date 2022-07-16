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
    Board(QString color, QString name);
    ~Board();

    void setName(QString name);
    void setColor(QString color);

    Board* makeNewChild(QString boardName);

    QString bgColor;
    QString boardName;
    unsigned int ID;

    Cork* cork;

    std::vector<Board*> children;
    unsigned int parent;
};

#endif // BOARD_H
