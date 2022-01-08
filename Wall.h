#ifndef WALL_H
#define WALL_H

#include "Board.h"
#include "Sidebar.h"
#include <list>

//contain all of the save info
struct BoardNode{
    Board *board;
    int id;
    std::vector<BoardNode> children;
    Board *parent;
};


class Wall {

public:
    Wall();
    ~Wall();
    Sidebar *buildTreeVis();

    BoardNode root;
    std::string wallName;

private:
    int maxID = 0;

};

#endif // WALL_H
