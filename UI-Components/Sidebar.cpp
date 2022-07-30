#include "Sidebar.h"
#include <iostream>

Sidebar::Sidebar(std::vector<BoardSwitchButton*> *bits) {
    buttons = bits;
    layout = new QVBoxLayout;

    for (unsigned int i = 0; i < bits->size(); i++) {
        layout->addWidget(buttons->at(i));
    }

    setLayout(layout);
}

void Sidebar::replace(std::vector<BoardSwitchButton*> *bits) {
    QLayoutItem *item;

    //delete buttons
    while((item = layout->takeAt(0))) {
        if (item->widget()) {
            item->widget()->hide();
            delete item->widget();
        }
    }

    delete buttons;
    buttons = bits;
    for (unsigned int i = 0; i < bits->size(); i++) {
        layout->addWidget(buttons->at(i));
    }
}

//void Sidebar::update(std::vector<BoardSwitchButton*> *bits) {

//    //

//}

void remove(BoardSwitchButton *bits) {

}
