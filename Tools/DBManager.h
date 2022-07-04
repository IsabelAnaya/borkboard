#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql>

//https://katecpp.github.io/sqlite-with-qt/
class DBManager {
public:
    DBManager();
    bool addWall(QString name);
    bool completeQuery(QSqlQuery q);

private:
    QSqlDatabase db;

};

#endif
