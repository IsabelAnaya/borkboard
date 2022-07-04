#include "Tools/DBManager.h"

DBManager::DBManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
}

bool DBManager::addWall(QString name) {
    db.setDatabaseName(name + ".bork");

    if(!db.open()) {
        qDebug() << "database connection failure";
    } else {
        qDebug() << "database connection success";
    }

    bool success = false;

    QSqlQuery query;
    query.prepare("PRAGMA schema.user_version = 0");
    query.exec();

    query.prepare("CREATE TABLE boards (board_id int, name text, color text, parent int, PRIMARY KEY (board_id))");
    query.exec();

    query.prepare("CREATE TABLE notes (count_id int, board_id int, type int, x int, y int, content_1 text, content_2 text, content_3 text)");
    query.exec();

    //query.prepare("SELECT * FROM TestTable");
    //query.exec();

    //query.next();
    //qDebug() << query.value(0).toString() << ", " << query.value(1).toString();

    return true;
}

bool DBManager::completeQuery(QSqlQuery q) {
    return q.exec();
}


//PRAGMA schema.user_version = #;
