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

    bool saveBoard(Board *board, int boardID, int parentID);
    bool saveNote(Note *note, int boardID, int noteID);
    bool removeDoubles(int boardID);
    void retrieveInfo();
    bool addNote(Board* board, noteType type, int x, int y, QString c1, QString c2, QString c3);
    Wall* rebuildWall();

private:
    DBManager *db;
};

#endif // DATAHANDLER_H
