#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "Notes/Note.h"
#include "UI-Components/Board.h"
#include "UI-Components/Wall.h"
#include "DBManager.h"

//builds and reacts to queries
class DataHandler {
public:
    DataHandler(DBManager *d);

    bool saveWall(Wall *wall);
    bool saveBoard(Board *board);
    bool saveNote(Note *note, int boardID, int noteID);
    bool removeDoubles(int boardID);
    bool addNote(Board* board, noteType type, int x, int y, int height, int width, QString c1, QString c2, QString c3, int color);
    Wall* rebuildWall();
    void rebuildNotes(Board *board);
    QSqlQuery findBoard(int ID);
    void findChildBoards(int ID, QQueue<int> *parents);

private:
    DBManager *db;
};

#endif // DATAHANDLER_H
