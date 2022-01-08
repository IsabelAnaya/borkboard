#include "Wall.h"
#include <QPushButton>

std::vector<QPushButton*> traverse(BoardNode node) {
    QPushButton *curr = new QPushButton(node.board->boardName);
    std::vector<QPushButton*> bits;
    bits.push_back(curr);

    for (unsigned int i = 0; i < node.children.size(); i++) {
        std::vector<QPushButton*> newEnd = traverse(node.children[i]);
        bits.insert(bits.end(), newEnd.begin(), newEnd.end());
    }

    return bits;
}



Wall::Wall() {
    wallName = "New Wall";

    root = BoardNode();
    root.board = new Board();
    root.board->setName("Root");
    root.board->ID = 0;
    root.parent = NULL;
}

Sidebar* Wall::buildTreeVis() {
    std::vector<QPushButton*> bits = traverse(root);

    return new Sidebar(bits);
}

Wall::~Wall() {
    delete root.board;
}
