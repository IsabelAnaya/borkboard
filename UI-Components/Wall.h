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
    ~Wall();
    Sidebar *buildTreeVis();
    void saveData(std::ofstream *file);
    void readData(std::ifstream *file);
    void update();

    Board *root;
    Board *currentBoard;
    std::string wallName;
    Sidebar *treeVis;
    QGridLayout *mainbox;
    QLabel* wallNameLabel;
private:
    int maxID = 0;

};

#endif // WALL_H
