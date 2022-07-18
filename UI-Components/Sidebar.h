#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <vector>
#include <QVBoxLayout>
#include <QPushButton>
#include "UI-Components/BoardSwitchButton.h"

class Sidebar : public QVBoxLayout {
    Q_OBJECT

public:
    Sidebar(std::vector<BoardSwitchButton*> bits);
    ~Sidebar();

    std::vector<BoardSwitchButton*> buttons;
};

#endif // SIDEBAR_H
