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
    q.bindValue(":name", board->boardName);
    q.bindValue(":color", board->bgColor);
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

void DataHandler::retrieveInfo() {
    QString query1 = "SELECT * FROM boards";
    QSqlQuery q1;
    q1.prepare(query1);
    q1 = db->returnQuery(q1);

    q1.first();

    //boards
    while (q1.isValid()) {
        qDebug() << q1.value(0) << q1.value(1) << q1.value(2) << q1.value(3);

        q1.next();
    }


    //notes
    QString query2 = "SELECT * FROM notes WHERE board_id = :board"; //FIX
    QSqlQuery q2;
    q2.prepare(query2);
    q2 = db->returnQuery(q2);

    q2.first();

    while (q2.isValid()) {
        qDebug() << q2.value(0) << q2.value(1) << q2.value(2) << q2.value(3) << q2.value(4) << q2.value(5) << q2.value(6) << q2.value(7);

        q2.next();
    }
}

bool DataHandler::addNote(Board* board, noteType type, int x, int y, QString c1, QString c2, QString c3) {
    switch (type) {
        case noteText:
            qDebug() << "text";
            board->cork->addTextNote(x, y, c1, c2);
            qDebug() << "done";
            return true;
        case noteBoard:
            return false;
        case noteImage:
            return false;
        default:
            return false;
    }
}

Wall* DataHandler::rebuildWall() {
    //retrieveInfo();

    QString boardString = "SELECT * FROM boards WHERE board_id = 0";
    QSqlQuery q1;
    q1.prepare(boardString);
    q1 = db->returnQuery(q1);

    q1.first();

    if (q1.isValid()) {
                    //id           //name         //color        //parent
        qDebug() << q1.value(0) << q1.value(1) << q1.value(2) << q1.value(3);
        Wall* wall = new Wall(db->getName(), q1.value(2).toString(), q1.value(1).toString());

        QString noteString = "SELECT type, x, y, content_1, content_2, content_3 FROM notes WHERE board_id = 0";
        QSqlQuery q2;
        q2.prepare(noteString);
        q2 = db->returnQuery(q2);

        q2.first();
        while (q2.isValid()) {
            addNote(wall->root, static_cast<noteType>(q2.value(0).toInt()), q2.value(1).toInt(), q2.value(2).toInt(), q2.value(3).toString(), q2.value(4).toString(), q2.value(5).toString());
            q2.next();
        }

        return wall;
    } else {
        return NULL;
    }
}
