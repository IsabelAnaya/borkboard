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
            qDebug() << "critical cringe moment";
            return false;
        }

        //qDebug() << "children " << currBoard->children.size();
        for (unsigned int i = 0; i < currBoard->children.size(); i++) {
            boards.enqueue(currBoard->children[i]);
        }
    }

    if (wall->themePath != "") {
        QString themeString = "UPDATE config SET value = :theme WHERE key = 'theme'";
        QSqlQuery updateTheme;
        updateTheme.prepare(themeString);
        updateTheme.bindValue(":theme", wall->themePath);
        //qDebug() << wall->themePath;
        if (!db->completeQuery(updateTheme)) {
            return false;
        }
    }

    qDebug() << "save successful";
    return true;
}

bool DataHandler::saveBoard(Board *board) {

    if (!removeDoubles(board->ID)) {
        std::cout << "couldn't remove preexisting board info" << std::endl;
    }

    for (unsigned int i = 0; i < board->cork->notes.size(); i++) {
        if (!saveNote(board->cork->notes[i], board->cork->order, board->ID, i)) {
            qDebug() << "break on saving note " << i;
            return false;
        }
    }

    QString queryString = "INSERT INTO boards (board_id, name, parent) VALUES (:board, :name, :parent)";
    QSqlQuery q;
    q.prepare(queryString);
    q.bindValue(":board", board->ID);
    q.bindValue(":name", board->boardName);
    q.bindValue(":parent", board->parent);

    return db->completeQuery(q);
}

bool DataHandler::saveNote(Note *note, std::vector<int> order, int boardID, int noteID) {
    noteType type = note->getType();
    int x = note->pos().x();
    int y = note->pos().y();
    int height = note->height();
    int width = note->width();
    QString content1 = NULL;
    QString content2 = NULL;
    QString content3 = NULL;
    NoteText *text;
    int id = note->ID;
    int noteOrder = -1;
    auto it = std::find(order.begin(), order.end(), id);
    if (it != order.end()) {
        noteOrder = it - order.begin();
    }
    qDebug() << noteOrder;


    switch (type) {
        case noteImage:
            content1 = note->toText();
            break;

        case noteText:
            text = static_cast<NoteText*>(note);
            if (text->editable) {
                text->toMarkdown(); //update text if needed
            }
            content1 = text->toText();
            break;

        case noteBoard:
            content1 = QString::number(static_cast<NoteBoardLink*>(note)->button->boardID);
            break;

        case noteSticker:
            content1 = "1"; //change this later
            break;

//        case noteFile:

//            break;

        default:
            //TYPE NOT IMPLEMENTED
            return false;
    }

    qDebug() << db->getName();
    QString queryString = "INSERT INTO notes (count_id, board_id, ordered, type, x, y, height, width, color, content_1, content_2, content_3) VALUES (:count, :board, :ord, :type, :x, :y, :height, :width, :color, :con1, :con2, :con3)";
    QSqlQuery q;
    q.prepare(queryString);
    q.bindValue(":count", noteID);
    q.bindValue(":board", boardID);
    q.bindValue(":ord", noteOrder);
    q.bindValue(":type", type);
    q.bindValue(":x", x);
    q.bindValue(":y", y);
    q.bindValue(":height", height);
    q.bindValue(":width", width);
    q.bindValue(":con1", content1);
    q.bindValue(":con2", content2);
    q.bindValue(":con3", content3);
    q.bindValue(":color", note->color);

    //qDebug() << "got this far";
    return db->completeQuery(q);
}

bool DataHandler::addNote(Board* board, noteType type, int x, int y, int height, int width, QString c1, QString c2, QString c3, int color) {
    QString boardString = "SELECT name FROM boards WHERE board_id = :board";
    QSqlQuery q;
    Note* note;

    switch (type) {
        case noteText:
            qDebug() << "text";
            note = board->cork->addTextNote(x, y, height, width, c1);
            note->setColor(color);
            return true;
        case noteBoard:
            qDebug() << "boardlink";
            q.prepare(boardString);
            q.bindValue(":board", c1);
            q = db->returnQuery(q);
            q.first();
            if (q.isValid()) {
                note = board->cork->addBoardLinkNote(x, y, height, width, c1.toInt(), q.value(0).toString());
                note->setColor(color);
                return true;
            }

            return false;
        case noteImage:
            qDebug() << "image" << c1;
            note = board->cork->addImageNote(x, y, height, width, c1);
            note->setColor(color);
            return true;
        case noteSticker:
            qDebug() << "sticker";
            note = board->cork->addStickerNote(x, y, height, width, c1.toInt());
            return true;
        default:
            return false;
    }

    c2 = NULL;
    c3 = NULL; //just to get rid of the warning
}

Wall* DataHandler::rebuildWall() {
    QSqlQuery q1 = findBoard(0);
    q1.first();

    if (q1.isValid()) {
                    //id           //name        //parent
        qDebug() << q1.value(0) << q1.value(1) << q1.value(2);
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
                Board *newest = wall->addSpecificBoard(wall->getBoard(q2.value(2).toInt()), q2.value(1).toString(), q2.value(0).toInt());

                if (newest) {
                    //make notes
                    rebuildNotes(newest);
                    findChildBoards(currentID, &parents);
                }
            }
        }

        QString findTheme = "SELECT value FROM config WHERE key = 'theme'";
        QSqlQuery q3;
        q3.prepare(findTheme);
        db->returnQuery(q3);
        q3.first();
        if (!q3.isValid()) {
            qDebug() << "failed to get theme";
        } else {
            wall->themePath = q3.value(0).toString();
        }

        return wall;
    } else {
        qDebug() << "about to die";
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
    QString noteString = "SELECT type, x, y, height, width, content_1, content_2, content_3, color, ordered FROM notes WHERE board_id = :id ORDER BY ordered DESC";
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
                q.value(7).toString(),
                q.value(8).toInt()
        );
        q.next();
    }
}
