#include "ThemeManager.h"

ThemeManager::ThemeManager() {

}

QString ThemeManager::applyTheme(QString path) {
    if (path == "") {
        return "Cork {  background-color: white; border: 0 }\n Sidebar { border: 0 }\n QScrollArea { border: 0 }\n";
    }

    QFile themeFile(path);

    if (!themeFile.open(QIODevice::ReadOnly)) {
        qWarning("didnt work");
        return "Cork { background-color: white; border: 0 }\n Sidebar { border: 0 }\n QScrollArea { border: 0 }\n";
    }

    QByteArray themeData = themeFile.readAll();

    QJsonParseError err;
    QJsonDocument theme(QJsonDocument::fromJson(themeData, &err));
    // qDebug() << err.error;
    // qDebug() << err.errorString();
    // qDebug() << theme["name"];


    return QString("MainWindow { background-color: " + (theme["side"]["background"]["color"]).toString() + "}\n"
            + "Cork { background-color: " + (theme["cork"]["background"]["color"]).toString() + "; border: 0 }\n"
            + "Sidebar { background-color: " + (theme["side"]["innerPanel"]["color"]).toString() + "; border: 0 }\n"
            + "QScrollArea { border: 0 }\n"
            + "Note { background-color: " +  (theme["side"]["background"]["color"]).toString() + "} \n");
}
