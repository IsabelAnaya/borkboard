#ifndef WALL_H
#define WALL_H

#include "Board.h"
#include <list>

//contain all of the save info
struct BoardNode{
    Board *board;
    std::vector<BoardNode> children;
    Board *parent;
};

class Wall {

public:
    Wall();
    QLayout *buildTreeVis();
    BoardNode root;

private:
    int maxID = 0;

};

#endif // WALL_H
