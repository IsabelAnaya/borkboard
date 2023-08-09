#include "ThemeManager.h"

ThemeManager::ThemeManager() {
    defaultTheme = "Cork {  background-color: white; border: 0 }\n Sidebar { border: 0 }\n QScrollArea { border: 0 }\n";
    currentTheme = defaultTheme;
}

QString ThemeManager::applyTheme(QString path) {
    if (path == "") {
        currentTheme = defaultTheme;
        return currentTheme;
    }

    QFile themeFile(path);

    if (!themeFile.open(QIODevice::ReadOnly)) {
        qWarning("didnt work");
        currentTheme = defaultTheme;
        return currentTheme;
    }

    QByteArray themeData = themeFile.readAll();

    QJsonParseError err;
    QJsonDocument theme(QJsonDocument::fromJson(themeData, &err));
    // qDebug() << err.error;
    // qDebug() << err.errorString();
    // qDebug() << theme["name"];

    currentTheme = basicThemeBits + QString("MainWindow { background-color: " + (theme["side"]["background"]["color"]).toString() + "}\n"
            + "Cork { background-color: " + (theme["cork"]["background"]["color"]).toString() + "; border: 0 }\n"
            + "Sidebar { background-color: " + (theme["side"]["innerPanel"]["color"]).toString() + "; border: 0 }\n"
            + "QScrollArea { border: 0 }\n"
            + "Note { background-color: " +  (theme["side"]["background"]["color"]).toString() + "} \n"
            + ".color-1 { background-color: " +  (theme["notes"]["color1"]).toString() + "} \n"
            + ".color-2 { background-color: " +  (theme["notes"]["color2"]).toString() + "} \n"
            + ".color-3 { background-color: " +  (theme["notes"]["color3"]).toString() + "} \n"
            + ".color-4 { background-color: " +  (theme["notes"]["color4"]).toString() + "} \n"
            + ".color-5 { background-color: " +  (theme["notes"]["color5"]).toString() + "} \n");

    return currentTheme;
}

QString ThemeManager::getCurrentTheme() {
    return currentTheme;
}
