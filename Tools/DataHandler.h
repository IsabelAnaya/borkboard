#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "Notes/Note.h"
#include "UI-Components/Board.h"
#include "DBManager.h"

class DataHandler {
public:
    DataHandler(DBManager *d);

    bool saveBoard(Board *board, int boardID, int parentID);
    bool saveNote(Note *note, int boardID, int noteID);
    bool removeDoubles(int boardID);

private:
    DBManager *db;
};

#endif // DATAHANDLER_H
