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

bool DataHandler::saveWall(Wall *wall) {
    QQueue<Board*> boards;
    boards.enqueue(wall->root);

    while (!boards.isEmpty()) {
        Board* currBoard = boards.dequeue();
        if (!saveBoard(currBoard)) {
            return false;
        }

        qDebug() << "children " << currBoard->children.size();
        for (unsigned int i = 0; i < currBoard->children.size(); i++) {
            boards.enqueue(currBoard->children[i]);
        }
    }

    return true;
}

bool DataHandler::saveBoard(Board *board) {

    if (!removeDoubles(board->ID)) {
        std::cout << "couldn't remove preexisting board info" << std::endl;
    }

    for (unsigned int i = 0; i < board->cork->notes.size(); i++) {
        if (!saveNote(board->cork->notes[i], board->ID, i)) {
            return false;
        }
    }

    QString queryString = "INSERT INTO boards (board_id, name, color, parent) VALUES (:board, :name, :color, :parent)";
    QSqlQuery q;
    q.prepare(queryString);
    q.bindValue(":board", board->ID);
    q.bindValue(":name", board->boardName);
    q.bindValue(":color", board->bgColor);
    q.bindValue(":parent", board->parent);

    return db->completeQuery(q);
}

bool DataHandler::saveNote(Note *note, int boardID, int noteID) {
    noteType type = note->getType();
    int x = note->pos().x();
    int y = note->pos().y();
    int height = note->height();
    int width = note->width();
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
            content1 = QString::number(static_cast<NoteBoardLink*>(note)->button->boardID);
            break;

//        case noteFile:

//            break;

        default:
            //TYPE NOT IMPLEMENTED
            return false;
    }

    QString queryString = "INSERT INTO notes (count_id, board_id, type, x, y, height, width, content_1, content_2, content_3) VALUES (:count, :board, :type, :x, :y, :height, :width, :con1, :con2, :con3)";
    QSqlQuery q;
    q.prepare(queryString);
    q.bindValue(":count", noteID);
    q.bindValue(":board", boardID);
    q.bindValue(":type", type);
    q.bindValue(":x", x);
    q.bindValue(":y", y);
    q.bindValue(":height", height);
    q.bindValue(":width", width);
    q.bindValue(":con1", content1);
    q.bindValue(":con2", content2);
    q.bindValue(":con3", content3);

    return db->completeQuery(q);
}

bool DataHandler::addNote(Board* board, noteType type, int x, int y, int height, int width, QString c1, QString c2, QString c3) {
    QString boardString = "SELECT name FROM boards WHERE board_id = :board";
    QSqlQuery q;

    switch (type) {
        case noteText:
            qDebug() << "text";
            board->cork->addTextNote(x, y, height, width, c1, c2);
            qDebug() << "done";
            return true;
        case noteBoard:
            qDebug() << "boardlink";
            q.prepare(boardString);
            q.bindValue(":board", c1);
            q = db->returnQuery(q);
            q.first();
            if (q.isValid()) {
                board->cork->addBoardLinkNote(x, y, height, width, c1.toInt(), q.value(0).toString());
                return true;
            }

            return false;
        case noteImage:
            return false;
        default:
            return false;
    }

    c3 = NULL; //just to get rid of the warning
}

Wall* DataHandler::rebuildWall() {
    QSqlQuery q1 = findBoard(0);
    q1.first();

    if (q1.isValid()) {
                    //id           //name         //color        //parent
        qDebug() << q1.value(0) << q1.value(1) << q1.value(2) << q1.value(3);
        Wall* wall = new Wall(db->getName(), q1.value(2).toString(), q1.value(1).toString());

        rebuildNotes(wall->root);

        int currentID;
        QQueue<int> parents;

        findChildBoards(0, &parents);

        while (!parents.isEmpty()) {
            //make board
            currentID = parents.dequeue();
            QSqlQuery q2 = findBoard(currentID);
            q2.first();
            if (q2.isValid()) {
                Board *newest = wall->addSpecificBoard(wall->getBoard(q2.value(3).toInt()), q2.value(1).toString(), q2.value(2).toString(), q2.value(0).toInt());

                if (newest) {
                    //make notes
                    rebuildNotes(newest);
                    findChildBoards(currentID, &parents);
                }
            }
        }

        return wall;
    } else {
        return NULL;
    }
}

QSqlQuery DataHandler::findBoard(int ID) {
    QString idString = "SELECT * FROM boards WHERE board_id = :board";
    QSqlQuery q;
    q.prepare(idString);
    q.bindValue(":board", ID);
    return db->returnQuery(q);
}

void DataHandler::findChildBoards(int ID, QQueue<int> *parents) {
    QString childString = "SELECT * FROM boards WHERE parent = :parent";
    QSqlQuery q;
    q.prepare(childString);
    q.bindValue(":parent", ID);
    q = db->returnQuery(q);

    q.first();
    while (q.isValid()) {
        parents->enqueue(q.value(0).toInt());
        q.next();
    }
}

void DataHandler::rebuildNotes(Board *board) {
    QString noteString = "SELECT type, x, y, height, width, content_1, content_2, content_3 FROM notes WHERE board_id = :id";
    QSqlQuery q;
    q.prepare(noteString);
    q.bindValue(":id", board->ID);
    q = db->returnQuery(q);

    q.first();
    while (q.isValid()) {
        addNote(board,
                static_cast<noteType>(q.value(0).toInt()),
                q.value(1).toInt(),
                q.value(2).toInt(),
                q.value(3).toInt(),
                q.value(4).toInt(),
                q.value(5).toString(),
                q.value(6).toString(),
                q.value(7).toString()
        );
        q.next();
    }
}
