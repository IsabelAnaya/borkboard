#ifndef WALL_H
#define WALL_H

#define MAX_BOARDS 20

#include "Board.h"
#include "Sidebar.h"
#include <list>
#include <QPushButton>
#include <QGridLayout>

class Wall {

public:
    Wall();
    Wall(QString name, QString bgColor, QString rootName);
    ~Wall();
    Sidebar *buildTreeVis();
    Board* addBoard(Board* parent, QString name);
    void changeBoard(int board);
    void update();

    Board *root;
    Board *currentBoard;
    QString wallName;
    Sidebar *treeVis;
    QGridLayout *mainbox;
    QLabel* wallNameLabel;
private:
    int maxID = 1;
    int boardsStored = 1;
    Board** boardMap;
};

#endif // WALL_H
