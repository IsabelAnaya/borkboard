#ifndef BOARDSWITCHBUTTON_H
#define BOARDSWITCHBUTTON_H

#include <QString>
#include <QPushButton>

class BoardSwitchButton : public QPushButton {
    Q_OBJECT

public:
    BoardSwitchButton(int board, QString name);
    ~BoardSwitchButton();
    void setName(QString name);
    void emitSignal();
    int boardID;

signals:
    void boardSwitch(int board);
};

#endif // BOARDSWITCHBUTTON_H
