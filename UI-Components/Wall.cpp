#include "Wall.h"
#include <iostream>

void zeroBoolArray(bool* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = false;
    }
}

Wall::Wall() {
    wallName = "New Wall";
    themePath = "";

    root = new Board();
    root->setName("Root");
    root->ID = 0;
    root->parent = NULL;

    currentBoard = root;
    boardMap = new Board* [MAX_BOARDS];
    slotFull = new bool [MAX_BOARDS];
    zeroBoolArray(slotFull, MAX_BOARDS);
    boardMap[0] = root;
    slotFull[0] = true;
}

//sets the wall's name and root board
Wall::Wall(QString name, QString theme, QString rootName) {
    wallName = name;
    themePath = theme;

    root = new Board(rootName);
    root->ID = 0;
    root->parent = NULL;

    currentBoard = root;
    boardMap = new Board* [MAX_BOARDS];
    slotFull = new bool [MAX_BOARDS];
    zeroBoolArray(slotFull, MAX_BOARDS);
    boardMap[0] = root;
    slotFull[0] = true;
}

Board* Wall::addBoard(Board* parent, QString name) {
    if (boardsStored < MAX_BOARDS) {
        while (slotFull[nextID]) {
            nextID = (nextID + 1) % MAX_BOARDS;
        }

        Board* child = parent->makeNewChild(name);
        child->ID = nextID;
        boardMap[nextID] = child;
        slotFull[nextID] = true;

        nextID = (nextID + 1) % MAX_BOARDS;

        boardsStored++;
        return child;

    } else {
        //qDebug() << "failed to create board!";
        return NULL;
    }
}

Board* Wall::addSpecificBoard(Board* parent, QString name, int ID) {
    if (parent && boardsStored < MAX_BOARDS && !slotFull[ID]) {
        Board* child = parent->makeNewChild(name);
        child->ID = ID;
        boardMap[ID] = child;
        slotFull[ID] = true;

        if (nextID == ID) {
            nextID = (nextID + 1) % MAX_BOARDS;
        }

        boardsStored++;
        return child;

    } else {
        return NULL;
    }
}

Board* Wall::getBoard(int ID) {
    if (ID > -1 && ID < MAX_BOARDS && slotFull[ID]) {
        return boardMap[ID];
    }

    return NULL;
}

std::pair<Board**, bool*> Wall::getAllBoards() {
    return std::make_pair(boardMap, slotFull);
}

void Wall::changeBoard(int board) {
    currentBoard = boardMap[board];
}

std::vector<Note*> Wall::findAllNotesOfType(noteType type) {
    std::vector<Note*> matching;
    QQueue<Board*> unsearched;
    unsearched.enqueue(root);

    while(!unsearched.isEmpty()) {
        Board *searching = unsearched.dequeue();
        std::vector<Note*> found = searching->findAllNotesOfType(type);
        matching.insert(matching.end(), found.begin(), found.end());

        for (unsigned int i = 0; i < searching->children.size(); i++) {
            unsearched.enqueue(searching->children[i]);
        }
    }

    return matching;
}

SidebarItem* Wall::updateTree(Board *node) {
    qDebug() << "building tree, " << node->boardName;
    BoardSwitchButton* currButton = new BoardSwitchButton(node->ID, node->boardName);
    SidebarItem* curr = new SidebarItem(nullptr, currButton);

    for (unsigned int i = 0; i < node->children.size(); i++) {
        SidebarItem* newEnd = updateTree(node->children[i]);
        curr->addItem(newEnd);
    }

    //qDebug() << "returning from updateTree..." << curr;
    return curr;
}

//assumes children have been reparented manually
void Wall::deleteBoard(int ID) {
    slotFull[ID] = false;
    Board* toDelete = boardMap[ID];
    delete toDelete;
    boardMap[ID] = NULL;
    boardsStored--;
}

Wall::~Wall() {
    std::cout << "deletin (Wall)" << std::endl;
    delete root;
}
