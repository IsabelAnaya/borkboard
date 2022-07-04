#include "DataHandler.h"
#include <iostream>

DataHandler::DataHandler(DBManager *d) {
    db = d;
}

bool DataHandler::removeDoubles(int boardID) {
    QString bstring = "DELETE FROM boards WHERE board_id = :board";
    QSqlQuery b;
    b.prepare(bstring);
    b.bindValue(":board", boardID);

    QString nstring = "DELETE FROM notes WHERE board_id = :board";
    QSqlQuery n;
    n.prepare(nstring);
    n.bindValue(":board", boardID);

    return (db->completeQuery(b) && db->completeQuery(n));
}

bool DataHandler::saveBoard(Board *board, int boardID, int parentID) {

    if (!removeDoubles(boardID)) {
        std::cout << "couldn't remove preexisting board info" << std::endl;
    }

    for (int i = 0; i < board->cork->notes.size(); i++) {
        if (!saveNote(board->cork->notes[i], boardID, i)) {
            return false;
        }
    }

    QString queryString = "INSERT INTO boards (board_id, name, color, parent) VALUES (:board, :name, :color, :parent)";
    QSqlQuery q;
    q.prepare(queryString);
    q.bindValue(":board", boardID);
    q.bindValue(":name", QString::fromStdString(board->boardName));
    q.bindValue(":color", QString::fromStdString(board->bgColor));
    q.bindValue(":parent", parentID);

    return db->completeQuery(q);
}

bool DataHandler::saveNote(Note *note, int boardID, int noteID) {
    noteType type = note->getType();
    int x = note->pos().x();
    int y = note->pos().y();
    QString content1 = NULL;
    QString content2 = NULL;
    QString content3 = NULL;
    NoteText *text;

    switch (type) {
//        case noteImage:

//            break;

        case noteText:
            text = static_cast<NoteText*>(note);
            content1 = text->title->toPlainText();
            content2 = text->content->toPlainText();
            break;

        case noteBoard:
            content1 = QString::number(static_cast<NoteBoardLink*>(note)->boardID);
            break;

//        case noteFile:

//            break;

        default:
            //TYPE NOT IMPLEMENTED
            return false;
    }

    QString queryString = "INSERT INTO notes (count_id, board_id, type, x, y, content_1, content_2, content_3) VALUES (:count, :board, :type, :x, :y, :con1, :con2, :con3)";
    QSqlQuery q;
    q.prepare(queryString);
    q.bindValue(":count", noteID);
    q.bindValue(":board", boardID);
    q.bindValue(":type", type);
    q.bindValue(":x", x);
    q.bindValue(":y", y);
    q.bindValue(":con1", content1);
    q.bindValue(":con2", content2);
    q.bindValue(":con3", content3);

    return db->completeQuery(q);
}
