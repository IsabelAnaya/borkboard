#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <vector>
#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include "UI-Components/BoardSwitchButton.h"

class Sidebar : public QFrame {
    Q_OBJECT

public:
    Sidebar(std::vector<BoardSwitchButton*> *bits);
    static Sidebar retrieveSidebar();
    void replace(std::vector<BoardSwitchButton*> *bits);

    std::vector<BoardSwitchButton*> *buttons;

private:
    QVBoxLayout *layout;
};

#endif // SIDEBAR_H
