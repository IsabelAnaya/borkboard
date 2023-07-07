#include "Sidebar.h"
#include <iostream>

Sidebar::Sidebar(SidebarItem *bits) {
    layout = new QVBoxLayout;
    firstElem = bits;

    layout->addWidget(bits);
    setLayout(layout);
    //setStyleSheet("background-color:blue");

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
}

void Sidebar::replace(SidebarItem *bits) {
    QLayoutItem* item = layout->takeAt((0));
    item->widget()->hide();
    layout->removeItem(item);
    delete item;

    firstElem = bits;
    layout->addWidget(bits);
    //qDebug() << "sidebar replaced";
}

void remove(BoardSwitchButton *bits) {

}
