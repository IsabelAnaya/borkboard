#include "Tools/DBManager.h"

DBManager::DBManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
}

bool DBManager::addWall(QString name) {
    db.setDatabaseName(name + ".bork");

    if (QFile::exists(name + ".bork")) {
        qDebug() << "file exists";
    }


    if(!db.open()) {
        qDebug() << "database connection failure";
    } else {
        qDebug() << "database connection success";
    }

    QSqlQuery query;
    query.prepare("PRAGMA schema.user_version = 0");
    query.exec();

    query.prepare("CREATE TABLE boards (board_id int, name text, color text, parent int, PRIMARY KEY (board_id))");
    query.exec();

    query.prepare("CREATE TABLE notes (count_id int, board_id int, type int, x int, y int, height int, width int, content_1 text, content_2 text, content_3 text)");
    query.exec();

    return true;
}

bool DBManager::openWall(QString name) {
    if (QFile::exists(name)) {
        qDebug() << "file exists";
        db.setDatabaseName(name);

        db.open();

        return true;
    }

    return false;
}

bool DBManager::completeQuery(QSqlQuery q) {
    return q.exec();
}

QSqlQuery DBManager::returnQuery(QSqlQuery q) {
    q.exec();
    return q;
}

QString DBManager::getName() {
    QString name = db.databaseName();

    std::string strName = name.toStdString();
    int pos = strName.find('/');
    while (strName.find('/', pos + 1) != std::string::npos) {
        pos = strName.find('/', pos + 1);
    }

    return (name.right(name.size() - pos - 1)).left(name.size() - pos - 6);
}


//PRAGMA schema.user_version = #;
