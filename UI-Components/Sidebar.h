#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <vector>
#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>
#include "UI-Components/BoardSwitchButton.h"
#include "SidebarItem.h"

class Sidebar : public QFrame {
    Q_OBJECT

public:
    Sidebar(SidebarItem *bits);
    static Sidebar retrieveSidebar();
    void replace(SidebarItem *bits);

    //std::vector<BoardSwitchButton*> *buttons;
    SidebarItem *firstElem;

private:
    QVBoxLayout *layout;
};

#endif // SIDEBAR_H
