#ifndef WALL_H
#define WALL_H

#include "Board.h"
#include "Sidebar.h"
#include <list>
#include <QPushButton>

//contain all of the save info
struct BoardNode{
    Board *board;
    int id;
    std::vector<BoardNode*> children;
    BoardNode *parent;
};


class Wall {

public:
    Wall();
    ~Wall();
    Sidebar *buildTreeVis();
    void saveData(std::ofstream *file);
    void readData(std::ifstream *file);

    BoardNode *root;
    std::string wallName;

private:
    int maxID = 0;

};

#endif // WALL_H
