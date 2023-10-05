#ifndef WALL_H
#define WALL_H

#define MAX_BOARDS 20

#include "Board.h"
#include <list>
#include <QPushButton>
#include <QGridLayout>
#include <QQueue>
#include "SidebarItem.h"

class Wall {

public:
    Wall();
    Wall(QString name, QString bgColor, QString rootName);
    ~Wall();
    Board* addBoard(Board *parent, QString name);
    Board* addSpecificBoard(Board *parent, QString name, int ID);
    Board* getBoard(int ID);
    std::pair<Board**, bool*> getAllBoards();
    void changeBoard(int board);
    SidebarItem* updateTree(Board *node);
    std::vector<Note*> findAllNotesOfType(noteType type);
    void deleteBoard(int ID);

    Board *root;
    Board *currentBoard;
    QString wallName;
    QString themePath;

private:
    int nextID = 1;
    int boardsStored = 1;
    Board** boardMap;
    bool* slotFull;
};

#endif // WALL_H
