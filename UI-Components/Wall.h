#ifndef WALL_H
#define WALL_H

#define MAX_BOARDS 20

#include "Board.h"
#include <list>
#include <QPushButton>
#include <QGridLayout>

class Wall {

public:
    Wall();
    Wall(QString name, QString bgColor, QString rootName);
    ~Wall();
    Board* addBoard(Board *parent, QString name);
    void changeBoard(int board);
    std::vector<BoardSwitchButton*>* updateTree(Board *node);

    Board *root;
    Board *currentBoard;
    QString wallName;

private:
    int maxID = 1;
    int boardsStored = 1;
    Board** boardMap;
};

#endif // WALL_H
