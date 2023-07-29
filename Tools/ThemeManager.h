#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QColor>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

class ThemeManager
{
public:
    ThemeManager();

    QString applyTheme(QString path);

private:
    QColor corkColor;
    QColor sideColor;
    QColor sideInnerColor;
};

#endif // THEMEMANAGER_H
