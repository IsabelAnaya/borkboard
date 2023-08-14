#include "ThemeManager.h"

ThemeManager::ThemeManager() {
    defaultTheme = QString("Cork {  background-color: white; border: 0; border-radius: 10px; }\n Sidebar { border: 0; border-radius: 10px }\n QScrollArea { background-color: white; border: 0;  border-radius: 10px }\n")
            + QString(".column { color: #d9d9d9 } \n")
            + QString(".color-1, .color-2, .color-3, .color-4, .color-5 { background-color: #d9d9d9; border: 0px; border-radius: 10px }\n");
    basicThemeBits = "QLabel { border: 0px; border-radius: 10px }\n QTextEdit { border: 0px; border-radius: 10px; background-color: palette(base) }\n";
    currentTheme = basicThemeBits + defaultTheme;
}

QString ThemeManager::applyTheme(QString path) {
    if (path == "") {
        currentTheme = basicThemeBits + defaultTheme;
        return currentTheme;
    }

    QFile themeFile(path);

    if (!themeFile.open(QIODevice::ReadOnly)) {
        qWarning("didnt work");
        currentTheme = basicThemeBits + defaultTheme;
        return currentTheme;
    }

    QByteArray themeData = themeFile.readAll();

    QJsonParseError err;
    QJsonDocument theme(QJsonDocument::fromJson(themeData, &err));
    // qDebug() << err.error;
    // qDebug() << err.errorString();
    // qDebug() << theme["name"];

    currentTheme = basicThemeBits + QString("MainWindow { background-color: " + (theme["side"]["background"]["color"]).toString() + "}\n"
            + "Cork { background-color: " + (theme["cork"]["background"]["color"]).toString() + "; border: 0;  border-radius: 10px; }\n"
            + "Sidebar { background-color: " + (theme["side"]["innerPanel"]["color"]).toString() + "; border: 0; border-radius: 10px }\n"
            + "QScrollArea { background-color: " + (theme["side"]["innerPanel"]["color"]).toString() + "; border: 0px; border-radius: 10px }\n"
            + "Note { background-color: " +  (theme["side"]["background"]["color"]).toString() + "; border: 0px; border-radius: 10px} \n"
            + ".column { color: " + (theme["side"]["innerPanel"]["column"]).toString() + " } \n"
            + ".color-1 { background-color: " +  (theme["notes"]["color1"]).toString() + "; border: 0px; border-radius: 10px } \n"
            + ".color-2 { background-color: " +  (theme["notes"]["color2"]).toString() + "; border: 0px; border-radius: 10px } \n"
            + ".color-3 { background-color: " +  (theme["notes"]["color3"]).toString() + "; border: 0px; border-radius: 10px} \n"
            + ".color-4 { background-color: " +  (theme["notes"]["color4"]).toString() + "; border: 0px; border-radius: 10px} \n"
            + ".color-5 { background-color: " +  (theme["notes"]["color5"]).toString() + "; border: 0px; border-radius: 10px} \n");

    return currentTheme;
}

QString ThemeManager::getCurrentTheme() {
    return currentTheme;
}

QString ThemeManager::getDefaultTheme() {
    return (basicThemeBits + defaultTheme);
}
