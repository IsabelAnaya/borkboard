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
    Board(std::string bgColor, std::string boardName);
    ~Board();

    void setName(std::string boardName);
    void setColor(std::string bgColor);

    Board* makeChild(std::string boardName);

    void saveData(std::ofstream *file);
    void readData(std::ifstream *file);

    std::string bgColor;
    std::string boardName;
    unsigned int ID;

    Cork* cork;

    std::vector<Board*> children;
    Board* parent;
};

#endif // BOARD_H
