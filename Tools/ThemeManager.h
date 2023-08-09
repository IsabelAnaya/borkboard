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
    QString getCurrentTheme();

private:
    QColor corkColor;
    QColor sideColor;
    QColor sideInnerColor;
    QString currentTheme;
    QString defaultTheme;
    QString basicThemeBits;
};

#endif // THEMEMANAGER_H
