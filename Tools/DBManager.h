#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql>

//https://katecpp.github.io/sqlite-with-qt/
//interacts directly with the database file
class DBManager {
public:
    DBManager();
    bool addWall(QString name);
    bool openWall(QString name);
    bool completeQuery(QSqlQuery q);
    QSqlQuery returnQuery(QSqlQuery q);
    QString getName();

private:
    QSqlDatabase db;

};

#endif
