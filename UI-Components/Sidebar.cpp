#include "Sidebar.h"
#include <iostream>

Sidebar::Sidebar(SidebarItem *bits) {
    layout = new QVBoxLayout;
    firstElem = bits;

    layout->addWidget(bits);
    setLayout(layout);
    //setStyleSheet("background-color:blue");

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
    this->setFixedHeight(200);
}

void Sidebar::replace(SidebarItem *bits) {
    QLayoutItem* item = layout->takeAt((0));
    item->widget()->hide();
    layout->removeItem(item);
    delete item;
    //delete firstElem; // cascading delete hopefully

    firstElem = bits;
    //qDebug() << "pre addwidget (crash)?" << bits;
    layout->addWidget(bits);
    //delete buttons
//    while((item = layout->takeAt(0))) {
//        if (item->widget()) {
//            item->widget()->hide();
//            delete item->widget();
//        }
//    }

//    delete buttons;
//    buttons = bits;
//    for (unsigned int i = 0; i < bits->size(); i++) {
//        layout->addWidget(buttons->at(i));
//    }
//    this->setFixedHeight(bits->size() * 40);
    //qDebug() << "sidebar replaced";
}

//void Sidebar::update(std::vector<BoardSwitchButton*> *bits) {

//    //

//}

void remove(BoardSwitchButton *bits) {

}
