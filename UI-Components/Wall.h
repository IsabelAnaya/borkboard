#ifndef WALL_H
#define WALL_H

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
    void update();

    Board *root;
    Board *currentBoard;
    QString wallName;
    Sidebar *treeVis;
    QGridLayout *mainbox;
    QLabel* wallNameLabel;
private:
    int maxID = 0;

};

#endif // WALL_H
