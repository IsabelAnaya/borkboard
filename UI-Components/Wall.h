#ifndef WALL_H
#define WALL_H

#define MAX_BOARDS 20

#include "Board.h"
#include <list>
#include <QPushButton>
#include <QGridLayout>
#include <QQueue>

class Wall {

public:
    Wall();
    Wall(QString name, QString bgColor, QString rootName);
    ~Wall();
    Board* addBoard(Board *parent, QString name);
    Board* addSpecificBoard(Board *parent, QString name, QString color, int ID);
    Board* getBoard(int ID);
    void changeBoard(int board);
    std::vector<BoardSwitchButton*>* updateTree(Board *node);
    std::vector<Note*> findAllNotesOfType(noteType type);

    Board *root;
    Board *currentBoard;
    QString wallName;

private:
    int nextID = 1;
    int boardsStored = 1;
    Board** boardMap;
    bool* slotFull;
};

#endif // WALL_H
